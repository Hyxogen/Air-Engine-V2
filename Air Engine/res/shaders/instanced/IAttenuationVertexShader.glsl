#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in mat4 aInstanceMatrix;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 out_Color;
out vec2 out_TexCoord;

void main() {
	//vec3 newPos = vec3(pos.x, pos.y, pos.z + gl_InstanceID * 2);

	gl_Position = projection * view * aInstanceMatrix * vec4(pos, 1.0);

	out_Color = vec4(0.0f, 0.0f, pos.z / 2.0, 1.0);
	out_TexCoord = texCoord;
}
