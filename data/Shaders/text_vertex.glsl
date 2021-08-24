#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 glyph_position;

uniform vec2 screen_size;
uniform vec2 atlas_size;

void main() {
	vec2 position = vertex.xy;
	position.y = -position.y;
	position = (2.0 * position.xy / screen_size) - vec2(1, -1);
	glyph_position = vertex.zw / atlas_size;
	gl_Position = vec4(position, 0.0, 1.0);
}