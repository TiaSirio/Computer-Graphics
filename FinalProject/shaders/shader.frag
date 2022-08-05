#version 450

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	mat4 view;
	mat4 proj;
	vec3 torchPos;
	vec3 eyePos;
} gubo;

layout(set = 1, binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 point_light_dir(vec3 pos, vec3 lightPos) {
	// Point light direction
	return normalize(lightPos - pos);
	//return normalize(pos);
}

vec3 point_light_color(vec3 pos, vec3 lightPos, vec3 lightColor, float g, float beta) {
	// Point light color
	return lightColor * pow((g/(length(lightPos - pos))), beta);
	//return lightColor * pow((g/(length(pos))), beta);
}

vec3 spot_light_dir(vec3 pos, vec3 lightPos) {
	// Spot light direction
	return normalize(lightPos - pos);
}

vec3 spot_light_color(vec3 pos, vec3 lightPos, vec3 lightColor, vec3 lightDir, float g, float beta, float cosOut, float cosIn) {
	// Spot light color
	return (lightColor * pow(g/(length(lightPos - pos)), beta)) * clamp((dot(normalize(lightPos - pos), lightDir) - cosOut)/(cosIn - cosOut), 0, 1);
}

void main() {
	vec3 norm = normalize(fragNorm);
	const vec3 diffColor = texture(texSampler, fragTexCoord).rgb;
	vec3 eyeDir = normalize(gubo.eyePos.xyz - fragViewDir);
	
	//vec3 lightPos1 = vec3(0.0f, 0.5f, 0.0f);
	//vec3 lightPos1 = vec3(-0.45f, 0.5f, 0.0f);
	vec3 lightPos1 = vec3(gubo.torchPos.x, 0.5f, gubo.torchPos.z);
	vec3 lightC1 = vec3(1.0f, 1.0f, 0.2f);
	vec3 lightDirection1 = point_light_dir(fragViewDir, lightPos1);
	vec3 lightColor1 = point_light_color(fragViewDir, lightPos1, lightC1, 0.3f, 1.5f);
	vec3 lightPos2 = vec3(490.0f, 200.0f, -490.0f);
	vec3 lightC2 = vec3(1.0f, 1.0f, 0.2f);
	vec3 lightDir2 = vec3(cos(radians(135.0f)), 0.0f, sin(radians(90.0f)));
	vec3 lightDirection2 = spot_light_dir(fragViewDir, lightPos2);
	vec3 lightColor2 = spot_light_color(fragViewDir, lightPos2, lightC2, lightDir2, 2.0f, 0.0f, 0.9f, 0.92f);
	//vec3 lightPos2 = vec3(500.0f, 200.0f, -499.0f);
	//vec3 lightC2 = vec3(1.0f, 1.0f, 1.0f);
	//vec3 lightDirection2 = point_light_dir(fragViewDir, lightPos2);
	//vec3 lightColor2 = point_light_color(fragViewDir, lightPos2, lightC2, 1.0f, 1.0f);
	
	
	// Hemispheric ambient
	//vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + norm.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - norm.y)) * diffColor;
	//vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + norm.y) + vec3(0.0f, 0.1f, 0.0f) * (1.0f - norm.y)) * diffColor;
	//vec3 ambient = vec3(0.3f,0.3f, 0.3f) * diffColor;
	vec3 ambient = vec3(0.01f,0.01f, 0.01f) * diffColor;
	
	vec3 diffuse1 = diffColor * (max(dot(norm, lightDirection1), 0.0f));
	vec3 specular1 = vec3(pow(max(dot(eyeDir, -reflect(lightDirection1, norm)),0.0f), 150.0f));
	
	vec3 diffuse2 = diffColor * (max(dot(norm, lightDirection2), 0.0f));
	vec3 specular2 = vec3(pow(max(dot(eyeDir, -reflect(lightDirection2, norm)),0.0f), 150.0f));
	
	outColor = vec4(
	((specular1 + diffuse1) * lightColor1) +
	((specular2 + diffuse2) * lightColor2) +
	ambient, 1.0f);
	//outColor = vec4(ambient, 1.0f);
}


/*

vec2 BRDFLut(float ndotv, float rough) {
	float x = 1 - rough;
    float y = ndotv;
 
    float b1 = -0.1688;
    float b2 = 1.895;
    float b3 = 0.9903;
    float b4 = -4.853;
    float b5 = 8.404;
    float b6 = -5.069;
    float bias = clamp(min( b1 * x + b2 * x * x, b3 + b4 * y + b5 * y * y + b6 * y * y * y ), 0.0, 1.0);
 
    float d0 = 0.6045;
    float d1 = 1.699;
    float d2 = -0.5228;
    float d3 = -3.603;
    float d4 = 1.404;
    float d5 = 0.1939;
    float d6 = 2.661;
    float delta = clamp( d0 + d1 * x + d2 * y + d3 * x * x + d4 * x * y + d5 * y * y + d6 * x * x * x, 0.0, 1.0);
    float scale = delta - bias;
    
    return vec2(scale, bias);
}
// ----------------------------------------------------------------------------
const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 Tan = normalize(fragTan.xyz - Norm * dot(fragTan.xyz, Norm));
	vec3 Bitan = cross(Norm, Tan) * fragTan.w;
	vec3 V = normalize(gubo.eyePos - fragPos);
	mat3 tbn = mat3(Tan, Bitan, Norm);
	vec4 nMap = texture(normSampler, fragTexCoord);
	vec3 N = normalize(tbn * (nMap.rgb * 2.0 - 1.0));
//	vec3 N = Norm;
	
	vec3 R = reflect(-V, N);
	vec4 MRAO = texture(matSampler, fragTexCoord);
	vec3 albedo = texture(texSampler, fragTexCoord).rgb;
//	vec3 albedo = vec3(1.0);
	float ao = MRAO.b;
	float roughness = MRAO.g;
	float metallic = MRAO.r;

	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);
	{
        // calculate per-light radiance
        vec3 L = gubo.lightDir;
        vec3 H = normalize(V + L);
        vec3 radiance = gubo.lightColor.rgb;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);    
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);        
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
         // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	                
            
        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo = (kD * albedo / PI + specular) * radiance * NdotL; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }  








    const float MAX_REFLECTION_LOD = 8.0;

    vec3 prefilteredColor = textureLod(skybox, R,  roughness * MAX_REFLECTION_LOD).rgb;    
	vec3 F = F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - max(dot(N, V), 0.0), 0.0, 1.0), 5.0);
	vec2 envBRDF = BRDFLut(max(dot(N, V), 0.0), roughness);
	vec3 specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);	
	vec3 kS = F;
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;	  
	  
	vec3 irradiance = textureLod(skybox, N,  MAX_REFLECTION_LOD - 1.0).rgb;
	vec3 diffuse    = irradiance * albedo;
	  	  
	vec3 ambient = (kD * diffuse + specular) * ao;
	vec3 color = ambient + Lo;
	color = color / (color + vec3(1.0));
//	color = pow(color, vec3(1.0/2.2));
 	
	outColor = vec4(clamp(color, 0.0, 1.0), 1.0);
}

*/