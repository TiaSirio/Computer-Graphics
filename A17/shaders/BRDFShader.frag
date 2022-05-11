#version 450#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor;	// also Bottom color for Hemispheric light,
					//      Constant term for Spherical Harmonics light
	vec3 TopColor;	// also DyColor for Spherical Harmonics light
	vec3 DzColor;
	vec3 DxColor;
	
	// Other parameters (not relevant for the exercise)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

/*vec2 fragTexCoord;
vec3 fragNorm;
vec3 fragPos;

vec4 outColor;*/layout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec2 fragTexCoord;layout(location = 0) out vec4 outColor;

vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {
	// Oren Nayar Diffuse + Ambient
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color
	// float sigma : roughness of the material
	float tetai = acos(dot(gubo.lightDir0, N));	float tetar = acos(dot(V, N));	float alpha = max(tetai, tetar);	float beta = min(tetai, tetar);	float a = 1 - (0.5 * ((pow(sigma, 2)) / (pow(sigma, 2) + 0.33)));	float b = (0.45 * ((pow(sigma, 2)) / (pow(sigma, 2) + 0.09)));	vec3 vi = normalize(gubo.lightDir0 - (dot(gubo.lightDir0, N) * N));	vec3 vr = normalize(V - (dot(V, N) * N));	float g = max(0, dot(vi, vr));	float elementL0 = dot(Cd[0], clamp(dot(gubo.lightDir0, N), 0, 1));	float elementL1 = dot(Cd[1], clamp(dot(gubo.lightDir0, N), 0, 1));	float elementL2 = dot(Cd[2], clamp(dot(gubo.lightDir0, N), 0, 1));	vec3 elementL = vec3(elementL0, elementL1, elementL2);	return (gubo.lightColor0 * (elementL * (a + b * g * sin(alpha) * tan(beta)))) + (gubo.AmbColor * Ca);
}

vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {
	// Lambert Diffuse + Hemispheric
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	// Hemispheric light oriented along the y-axis
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color

	vec3 HemiDir = vec3(0.0f, 1.0f, 0.0f);
	float value0 = gubo.lightColor0[0] * dot(Cd[0], clamp(dot(gubo.lightDir0, N), 0, 1));	float value1 = gubo.lightColor0[1] * dot(Cd[1], clamp(dot(gubo.lightDir0, N), 0, 1));	float value2 = gubo.lightColor0[2] * dot(Cd[2], clamp(dot(gubo.lightDir0, N), 0, 1));	vec3 topValue = ((dot(N, HemiDir) + 1)/2) * gubo.TopColor;	vec3 botValue = ((1 - dot(N, HemiDir))/2) * gubo.AmbColor;	return (gubo.lightColor0 * vec3(value0, value1, value2)) + (topValue + botValue) * Ca;
}

vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {
	// Spherical Harmonics
	// Blinn Specular
	// Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cs : specular color
	// vec3 Ca : ambient color
	// float gamma : Blinn exponent
		vec3 h0 = normalize(gubo.lightDir0 + V);	float value00 = dot(Cs[0], pow(clamp(dot(N, h0), 0, 1), gamma));	float value01 = dot(Cs[1], pow(clamp(dot(N, h0), 0, 1), gamma));	float value02 = dot(Cs[2], pow(clamp(dot(N, h0), 0, 1), gamma));	vec3 valueBlinn0 = vec3(value00, value01, value02);	vec3 h1 = normalize(gubo.lightDir1 + V);	float value10 = dot(Cs[0], pow(clamp(dot(N, h1), 0, 1), gamma));	float value11 = dot(Cs[1], pow(clamp(dot(N, h1), 0, 1), gamma));	float value12 = dot(Cs[2], pow(clamp(dot(N, h1), 0, 1), gamma));	vec3 valueBlinn1 = vec3(value10, value11, value12);	vec3 h2 = normalize(gubo.lightDir2 + V);	float value20 = dot(Cs[0], pow(clamp(dot(N, h2), 0, 1), gamma));	float value21 = dot(Cs[1], pow(clamp(dot(N, h2), 0, 1), gamma));	float value22 = dot(Cs[2], pow(clamp(dot(N, h2), 0, 1), gamma));	vec3 valueBlinn2 = vec3(value20, value21, value22);	vec3 h3 = normalize(gubo.lightDir3 + V);	float value30 = dot(Cs[0], pow(clamp(dot(N, h3), 0, 1), gamma));	float value31 = dot(Cs[1], pow(clamp(dot(N, h3), 0, 1), gamma));	float value32 = dot(Cs[2], pow(clamp(dot(N, h3), 0, 1), gamma));	vec3 valueBlinn3 = vec3(value30, value31, value32);	vec3 lightValueCase3 = gubo.AmbColor + (N[0] * gubo.DxColor) + (N[1] * gubo.TopColor) + (N[2] * gubo.DzColor);	//return (gubo.lightColor0 * gubo.lightColor1 * gubo.lightColor2 * gubo.lightColor3 * (valueBlinn0 + valueBlinn1 + valueBlinn2 + valueBlinn3)) + (lightValueCase3 * Ca);	return ((gubo.lightColor0 * valueBlinn0) + (gubo.lightColor1 * valueBlinn1) + (gubo.lightColor2 * valueBlinn2) + (gubo.lightColor3 * valueBlinn3)) + (lightValueCase3 * Ca);
}



/**** To here *****/




void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}