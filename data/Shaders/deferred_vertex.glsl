#version 330 core

layout (location = 0) in vec2 position;

out vec2 coordinate;

void main() {
	coordinate = (position + vec2(1.0, 1.0)) / 2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}