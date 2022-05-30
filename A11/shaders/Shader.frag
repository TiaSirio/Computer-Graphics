#version 450
layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {	/*outColor = vec4((float(16 % 5) + sin(gubo.time * 6.28)) / 5.0,					float(16 % 10) / 10.0,					float(16) / 15.0,					1.0);*/	outColor = vec4(float(sin(gubo.time * 2 * 3.14) / 5.0), float(cos(gubo.time * 6.28) / 10.0), float(tan(gubo.time * 2 * 3.14) / 15.0), 1.0);
}