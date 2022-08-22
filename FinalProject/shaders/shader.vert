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
	//bool isTaken;
	float roughness;
} ubo;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	//if (ubo.isTaken) {
	//	gl_Position = gubo.proj * mat4(1.0f) * ubo.model * vec4(pos, 1.0);
	//} else {
		gl_Position = gubo.proj * gubo.view * ubo.model * vec4(pos, 1.0);
	//}
	fragViewDir = (ubo.model * vec4(pos, 1.0)).xyz;
	//fragNorm = (ubo.normal * vec4(norm, 0.0)).xyz;
	//fragNorm = (ubo.model * vec4(norm, 0.0)).xyz;
	fragNorm = mat3(ubo.normal) * norm;
	fragTexCoord = texCoord;
}