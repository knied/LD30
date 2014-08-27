//#version 330 core
#version 120

uniform sampler2D texture0;
uniform float fade;

//in vec2 v_texcoord;
varying vec2 v_texcoord;

//layout(location = 0) out vec4 frag_color;

void main() {
    vec4 color = texture2D(texture0, v_texcoord);
    //frag_color = vec4((1.0 - fade) * color.rgb + fade * vec3(1.0, 1.0, 1.0), color.a);
    gl_FragColor = vec4((1.0 - fade) * color.rgb + fade * vec3(1.0, 1.0, 1.0), color.a);
}