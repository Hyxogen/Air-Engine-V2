#version 330 core

uniform sampler2D screenTexture;

in vec2 TexCoord;

out vec4 out_Color;

const float offset = 1.0 / 300.0;

void main() {
	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset),
		vec2(0.0,      offset),
		vec2(offset,   offset),
		vec2(-offset,     0.0),
		vec2(0.0,         0.0),
		vec2(offset,      0.0),
		vec2(-offset, -offset),
		vec2(0.0, -offset),
		vec2(offset, -offset)
	);

	/*float kernel[9] = float[](
		1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
		2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
		1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0
	);*/

	float kernel[9] = float[](
		1, 1, 1,
		1, -8, 1,
		1, 1, 1
	);

	vec3 sampleTex[9];
	for (int i = 0; i < 9; i++) {
		sampleTex[i] = vec3(texture(screenTexture, TexCoord.st + offsets[i]));
	}

	vec3 col = vec3(0.0);

	for (int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];
	vec4 result = texture(screenTexture, TexCoord);
	float average = 0.2126 * result.x + 0.7152 * result.y + 0.0722 * result.z;

	//out_Color = vec4(col, 1.0);
	out_Color = texture(screenTexture, TexCoord);
}