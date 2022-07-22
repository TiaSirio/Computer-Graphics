#version 450

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	mat4 view;
	mat4 proj;
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

void main() {
	/*const vec3  diffColor = texture(texSampler, fragTexCoord).rgb;
	const vec3  specColor = vec3(1.0f, 1.0f, 1.0f);
	const float specPower = 150.0f;
	//const vec3  L = vec3(-0.4830f, 0.8365f, -0.2588f);
	const vec3  L = vec3(-0.4830f, -0.365f, -0.2588f);
	
	vec3 N = normalize(fragNorm);
	vec3 R = -reflect(L, N);
	//vec3 V = normalize(fragViewDir);
	vec3 V = normalize(gubo.eyePos.xyz - fragViewDir);
	
	// Lambert diffuse
	vec3 diffuse  = diffColor * max(dot(N,L), 0.0f);
	// Phong specular
	vec3 specular = specColor * pow(max(dot(R,V), 0.0f), specPower);
	// Hemispheric ambient
	vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + N.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - N.y)) * diffColor;
	
	//vec3 toonSpecular = Toon_Specular(L, N, V, vec3(1,1,1), 0.97f);
	//vec3 toonDiffuse = Toon_Diffuse(L, N, V, vec3(1,1,1), 0.2f * vec3(1,1,1), 0.5);
	
	//outColor = vec4(clamp(ambient + toonDiffuse + toonSpecular, vec3(0.0f), vec3(1.0f)), 1.0f);
	outColor = vec4(clamp(ambient + diffuse + specular, vec3(0.0f), vec3(1.0f)), 1.0f);
	//outColor = vec4(clamp(ambient + diffuse, vec3(0.0f), vec3(1.0f)), 1.0f);
	*/
	
	vec3 norm = normalize(fragNorm);
	const vec3 diffColor = texture(texSampler, fragTexCoord).rgb;
	vec3 eyeDir = normalize(gubo.eyePos.xyz - fragViewDir);
	
	//vec3 lightPos1 = vec3(0.0f, 0.5f, 0.0f);
	vec3 lightPos1 = vec3(-0.45f, 0.5f, 0.0f);
	vec3 lightC1 = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightDirection1 = point_light_dir(fragViewDir, lightPos1);
	vec3 lightColor1 = point_light_color(fragViewDir, lightPos1, lightC1, 2.0f, 2.0f);
	
	
	// Hemispheric ambient
	//vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + norm.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - norm.y)) * diffColor;
	//vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + norm.y) + vec3(0.0f, 0.1f, 0.0f) * (1.0f - norm.y)) * diffColor;
	vec3 ambient = vec3(0.3f,0.3f, 0.3f) * diffColor;
	//vec3 ambient = vec3(0.01f,0.01f, 0.01f) * diffColor;
	
	vec3 diffuse = diffColor * (max(dot(norm, lightDirection1), 0.0f));
	vec3 specular = vec3(pow(max(dot(eyeDir, -reflect(lightDirection1, norm)),0.0f), 150.0f));
	
	//outColor = vec4(((specular + diffuse) * lightColor1) + ambient, 1.0f);
	outColor = vec4(ambient, 1.0f);
}