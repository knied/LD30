#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;

uniform mat4 model_view_projection;

out vec4 v_color;

void main() {
    v_color = color;
    gl_Position = model_view_projection * vec4(vertex, 1.0);
}