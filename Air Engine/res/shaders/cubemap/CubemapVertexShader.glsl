#version 330 core

layout(location = 0) in vec3 pos;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main() {
	TexCoord = pos;
	vec4 position = projection * view * vec4(pos, 1.0);
	gl_Position = position.xyww;
}