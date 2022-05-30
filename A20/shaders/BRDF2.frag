#version 450

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightColor;
	vec3 eyePos;
} gubo;

layout(set = 0, binding = 3) uniform sampler2D texel;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

vec3 direct_light_dir(vec3 pos) {
	// Directional light direction
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos) {
	// Directional light color
	return gubo.lightColor;
}

vec3 blinn_specular(vec3 N, vec3 L, vec3 V, vec3 Cs, float gamma){
	vec3 h0 = normalize(L + V);
	return Cs * pow(clamp(dot(N, h0), 0, 1), gamma);
	//float value00 = dot(Cs[0], pow(clamp(dot(N, h0), 0, 1), gamma));
	//float value01 = dot(Cs[1], pow(clamp(dot(N, h0), 0, 1), gamma));
	//float value02 = dot(Cs[2], pow(clamp(dot(N, h0), 0, 1), gamma));
	//return vec3(value00, value01, value02);
}

void main() {
	vec3 norm = normalize(fragNorm);
	vec3 eyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	vec3 lightDirection = direct_light_dir(fragPos);
	vec3 lightColor = direct_light_color(fragPos);
	
	vec3 ambient = lightDirection * lightColor;
	vec3 blinn = blinn_specular(norm, lightDirection, eyeDir, texel.rgb, 200.0f * texel.a);
	
	//vec3 blinn = blinn_specular(norm, lightDirection, eyeDir, lightColor, 200.0f * texel.a);
	//vec3(pow(max(dot(eyeDir, -reflect(lightDirection, norm)),0.0f), 200.0f * texel.a));
	
	outColor = vec4((ambient + blinn), 1.0f);
}