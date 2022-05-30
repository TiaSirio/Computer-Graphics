#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	gl_Position = ubo.mvpMat * ubo.mMat * ubo.nMat * vec4(inPosition, 1.0);
	fragViewDir  = (ubo.mMat[3]).xyz - (ubo.mvpMat * vec4(inPosition,  1.0)).xyz;
	fragNorm     = (ubo.mvpMat * vec4(inNormal, 0.0)).xyz;
	fragTexCoord = inTexCoord;
}