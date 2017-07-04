#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT{
	vec3 normal;
} gs_in[];

const float magnitude = 0.4;

void drawLine(int index) {
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * magnitude;
	EmitVertex();

	EndPrimitive();
}

void main() {
	drawLine(0);
	drawLine(1);
	drawLine(2);
}