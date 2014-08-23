#version 330 core

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texcoord;

uniform mat3 model_view;

out vec2 v_texcoord;

void main() {
    v_texcoord = texcoord;
    gl_Position = vec4(((model_view) * vec3(vertex, 1.0)).xy, 0.0, 1.0);
}