#version 330 core

in vec4 v_color;

layout(location = 0) out vec4 frag_color;

void main() {
    frag_color = v_color;
}