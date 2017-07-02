#version 330 core

in vec4 out_Color;
in vec2 out_TexCoord;

out vec4 color;

float far = 100.0;
float near = 0.1;

float LinearizeDepth(float depth) {
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
	//color = out_Color;
	float depth = LinearizeDepth(gl_FragCoord.z);
	color = vec4(vec3(depth), 1.0);
}
