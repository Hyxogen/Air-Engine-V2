#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 out_Color;

void main() {
    gl_Position = projection * model * vec4(pos, 1.0);
    out_Color = vec4(1.0, 0.0, 1.0, 0.0);
}
