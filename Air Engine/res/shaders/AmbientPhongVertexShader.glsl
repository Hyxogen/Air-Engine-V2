#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 out_Color;
out vec2 out_TexCoord;
out vec3 out_Normal;
out vec3 out_FragPos;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);

	out_Color = vec4(0.0f, 0.0f, pos.z / 2.0, 1.0);
	out_FragPos = vec3(model * vec4(pos, 1.0));
	out_TexCoord = texCoord;
	out_Normal = mat3(model) * normal;
	//out_Normal = mat3(transpose(inverse(model)) * normal;
}
