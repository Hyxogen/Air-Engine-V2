#version 330 core

uniform vec3 viewPos;
uniform samplerCube skybox;

in vec3 Normal;
in vec3 Position;

out vec4 color;

void main() {
	vec3 I = normalize(Position - viewPos);
	//vec3 R = reflect(I, normalize(Normal));
	vec3 R = refract(I, normalize(Normal), 1.00 / 1.52);

	color = vec4(texture(skybox, R).rgb, 1.0);
	//color = vec4(1.0, 1.0, 0.0, 0.0);
}