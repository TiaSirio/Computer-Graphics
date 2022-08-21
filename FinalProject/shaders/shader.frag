#version 450

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	mat4 view;
	mat4 proj;
	vec3 torchPos;
	vec3 eyePos;
} gubo;

layout(set = 1, binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 normal;
	bool isTaken;
	float roughness;
} ubo;

layout(set = 1, binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 point_light_dir(vec3 pos, vec3 lightPos) {
	// Point light direction
	return normalize(lightPos - pos);
}

vec3 point_light_color(vec3 pos, vec3 lightPos, vec3 lightColor, float g, float beta) {
	// Point light color
	return lightColor * pow((g/(length(lightPos - pos))), beta);
}

vec3 spot_light_dir(vec3 pos, vec3 lightPos) {
	// Spot light direction
	return normalize(lightPos - pos);
}

vec3 spot_light_color(vec3 pos, vec3 lightPos, vec3 lightColor, vec3 lightDir, float g, float beta, float cosOut, float cosIn) {
	// Spot light color
	return (lightColor * pow(g/(length(lightPos - pos)), beta)) * clamp((dot(normalize(lightPos - pos), lightDir) - cosOut)/(cosIn - cosOut), 0, 1);
}

vec3 specular_light(vec3 lightPos, vec3 normal, vec3 lightDir, vec3 eyeDir) {
      vec3 reflectDir = -reflect(lightDir, normal);
	return vec3(pow(max(dot(eyeDir, reflectDir), 0.0f), 150.0f));
}

vec3 blinn_specular(vec3 N, vec3 L, vec3 V, vec3 Cs, float gamma){
	vec3 h0 = normalize(L + V);
	return Cs * pow(clamp(dot(N, h0), 0.0f, 1.0f), gamma);
}

vec3 diffuse_nayar(vec3 N, vec3 V, vec3 Cd, float sigma, vec3 lightDir) {
	float tetai = acos(dot(lightDir, N));
	float tetar = acos(dot(V, N));
	float alpha = max(tetai, tetar);
	float beta = min(tetai, tetar);
	float a = 1 - (0.5 * ((pow(sigma, 2)) / (pow(sigma, 2) + 0.33)));
	float b = (0.45 * ((pow(sigma, 2)) / (pow(sigma, 2) + 0.09)));
	vec3 vi = normalize(lightDir - (dot(lightDir, N) * N));
	vec3 vr = normalize(V - (dot(V, N) * N));
	float g = max(0, dot(vi, vr));
	
	vec3 elementL = Cd * clamp(dot(lightDir, N), 0.0f, 1.0f);
	return (elementL * (a + b * g * sin(alpha) * tan(beta)));
}

//Not see the specular at the rear
vec3 getCorrectNorm(vec3 norm, vec3 lightDir) {
	if (dot(norm, lightDir) > 0) {
		return norm;
	}
	return -norm;
}

void main() {
	vec3 constNorm = normalize(fragNorm);
	vec3 norm = constNorm;
	vec3 diffColor = texture(texSampler, fragTexCoord).rgb;
	vec3 eyeDir = normalize(gubo.eyePos - fragViewDir);


	
	//vec3 topColor = vec3(0.1f, 0.15f, 0.3f);
	//vec3 botColor = vec3(0.3, 0.3f, 0.1f);

	/*vec3 topColor = vec3(0.005f, 0.015f, 0.015f);
	vec3 botColor = vec3(0.015f, 0.015f, 0.005f);
	vec3 HemiDir = vec3(0.0f, 1.0f, 0.0f);
	vec3 topValue = ((dot(norm, HemiDir) + 1)/2) * topColor;
	vec3 botValue = ((1 - dot(norm, HemiDir))/2) * botColor;*/



	//vec3 lightPos1 = (gubo.proj * mat4(1.0f) * ubo.model * vec4(gubo.torchPos, 1.0)).xyz;
	//vec3 lightPos1 = (ubo.model * vec4(gubo.torchPos, 1.0)).xyz;

	//vec4 lightPosTemp1 = ubo.model * vec4(gubo.torchPos.x, gubo.torchPos.y, gubo.torchPos.z, 1.0);
	//vec3 lightPos1 = vec3(lightPosTemp1.x, lightPosTemp1.y, lightPosTemp1.z);

	vec3 lightPos1 = vec3(gubo.torchPos.x, gubo.torchPos.y, gubo.torchPos.z);
	vec3 lightC1 = vec3(1.0f, 1.0f, 0.2f);
	vec3 lightDirection1 = point_light_dir(fragViewDir, lightPos1);
	//vec3 lightColor1 = point_light_color(fragViewDir, lightPos1, lightC1, 0.4f, 3.0f);
	vec3 lightColor1 = point_light_color(fragViewDir, lightPos1, lightC1, 0.5f, 3.0f);

	//vec3 lightColor1 = point_light_color(fragViewDir, lightPos1, lightC1, 0.3f, 1.5f);
	
	vec3 lightPos2 = vec3(490.0f, 200.0f, -490.0f);
	vec3 lightC2 = vec3(1.0f, 1.0f, 0.2f);
	vec3 lightDir2 = vec3(cos(radians(135.0f)), 0.0f, sin(radians(90.0f)));
	vec3 lightDirection2 = spot_light_dir(fragViewDir, lightPos2);
	vec3 lightColor2 = spot_light_color(fragViewDir, lightPos2, lightC2, lightDir2, 2.0f, 0.0f, 0.9f, 0.92f);
	
	
	
	//Ambient
	//vec3 ambient = vec3(0.1f, 0.1f, 0.1f) * diffColor;
	//vec3 ambient = vec3(0, 0, 0) * diffColor;
	vec3 ambient = vec3(0.02f, 0.02f, 0.02f) * diffColor;
	
	
	
	norm = getCorrectNorm(norm, lightDirection1);
	
	vec3 diffuse1 = diffuse_nayar(norm, eyeDir, diffColor, ubo.roughness, lightDirection1);
	vec3 specular1 = specular_light(lightPos1, norm, lightDirection1, eyeDir);
	//vec3 specular1 = blinn_specular(norm, lightDirection1, eyeDir, vec3(1.0f, 1.0f, 0.2f), 300.0f);

	//float lightDist = length(lightDirection1);
	//float attenuation = clamp(5.0 / lightDist, 0.0, 1.0);

	norm = constNorm;
	norm = getCorrectNorm(norm, lightDirection2);

	vec3 diffuse2 = diffuse_nayar(norm, eyeDir, diffColor, ubo.roughness, lightDirection2);
	vec3 specular2 = specular_light(lightPos2, norm, lightDirection2, eyeDir);
	//vec3 specular2 = blinn_specular(norm, lightDirection2, eyeDir, vec3(1.0f, 1.0f, 0.2f), 10.0f);




	/*diffuse1 = diffColor * (max(dot(norm, lightDirection1), 0.0f));
	specular1 = specular_light(lightPos1, norm, lightDirection1, eyeDir);

	diffuse2 = diffColor * (max(dot(norm, lightDirection2), 0.0f));
	specular2 = specular_light(lightPos2, norm, lightDirection2, eyeDir);*/

	/*diffuse1 = diffColor * (max(dot(norm, lightDirection1), 0.0f));
	specular1 = vec3(pow(max(dot(eyeDir, -reflect(lightDirection1, norm)),0.0f), 150.0f));

	diffuse2 = diffColor * (max(dot(norm, lightDirection2), 0.0f));
	specular2 = vec3(pow(max(dot(eyeDir, -reflect(lightDirection2, norm)),0.0f), 150.0f));*/




	outColor = vec4(
	((specular1 + diffuse1) * lightColor1) +
	((specular2 + diffuse2) * lightColor2) +
	ambient, 1.0f);
	//(topValue + botValue) * diffColor, 1.0f);
	//outColor = vec4(ambient, 1.0f);
}