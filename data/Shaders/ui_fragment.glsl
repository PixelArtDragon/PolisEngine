#version 330 core

uniform sampler2D texture_0;

in vec2 i_uv;

void main() {
	gl_FragColor = texture(texture_0, i_uv);
}