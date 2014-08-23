#version 330 core

uniform sampler2D texture0;

in vec2 v_texcoord;

layout(location = 0) out vec4 frag_color;

void main() {
    frag_color = texture(texture0, v_texcoord);
}