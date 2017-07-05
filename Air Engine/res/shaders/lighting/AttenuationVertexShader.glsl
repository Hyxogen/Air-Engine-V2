#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT{
	vec2 texCoords;
} vs_out;

out vec4 out_Color;
out vec2 out_TexCoord;
out vec3 out_Normal;
out vec3 out_FragPos;

void main() {
	vec3 newPos = vec3(pos.x, pos.y, pos.z + gl_InstanceID * 2);

	gl_Position = projection * view * model * vec4(newPos, 1.0);
	
	out_Color = vec4(0.0f, 0.0f, pos.z / 2.0, 1.0);
	out_FragPos = vec3(model * vec4(pos, 1.0));
	out_TexCoord = texCoord;
	//vs_out.texCoords = texCoord;

	//mat3 normalMatrix = mat3(view * model);
	out_Normal = mat3(model) * normal;
	//out_Normal = normalMatrix * normal;
	//out_Normal = mat3(transpose(inverse(model)) * normal;
}
