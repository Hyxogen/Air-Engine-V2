#version 330 core

uniform samplerCube skybox;

in vec3 TexCoord;

out vec4 color;

void main() {
	//color = texture(skybox, TexCoord);
	color = vec4(1.0, 1.0, 0.0, 0.0);
}