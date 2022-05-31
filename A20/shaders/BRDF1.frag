#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec4 lightParams;
	vec3 eyePos;
} gubo;

layout(set = 0, binding = 3) uniform sampler2D texel;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 spot_light_dir(vec3 pos) {
	// Spot light direction
	return normalize(gubo.lightPos - pos);
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	float g = gubo.lightParams.w;
	float beta = gubo.lightParams.z;
	float cosOut = gubo.lightParams.y;
	float cosIn = gubo.lightParams.x;

	return (gubo.lightColor * pow(g/(length(gubo.lightPos - pos)), beta)) *
	clamp((dot(normalize(gubo.lightPos - pos), gubo.lightDir) - cosOut)/(cosIn - cosOut), 0, 1);
}

vec3 lambert_diffuse(vec3 L, vec3 N, vec3 C) {
	return C * clamp(dot(L, N), 0, 1);
}

void main() {
	vec3 norm = normalize(fragNorm);
	vec3 eyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	const vec3 diffColor = texture(texSampler, fragTexCoord).rgb;
	const vec3 specColor = texture(texel, fragTexCoord).rgb;
	const float refExponent = texture(texel, fragTexCoord).a;
	
	vec3 lightDirection = spot_light_dir(fragPos);
	vec3 lightColor = spot_light_color(fragPos);
	
	vec3 lambert = lambert_diffuse(lightDirection, norm, diffColor);
	vec3 phong = specColor * pow(max(dot(eyeDir, -reflect(lightDirection, norm)),0.0f), 200.0f * refExponent);
		
	outColor = vec4((lambert + phong) * lightColor, 1.0f);
}