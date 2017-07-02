#version 330 core

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

in vec4 out_Color;
in vec2 out_TexCoord;

out vec4 color;

void main() {
    //color = out_Color;
	color = texture(texture_diffuse1, out_TexCoord);
}
