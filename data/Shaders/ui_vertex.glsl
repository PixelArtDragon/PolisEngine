#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 2) in vec2 in_uv;

out vec2 i_uv;

uniform mat3 object_transform;
uniform vec2 screen_size;

void main() {
	vec3 position = object_transform * vec3(in_position.xy, 1.0);
	i_uv = in_uv;
	position.y = -position.y;
	position.xy = (2.0 * position.xy / screen_size) - vec2(1, -1); //Convert from (0,0 to screen_size) to (-1,-1 to 1,1)
	gl_Position = vec4(position.xy, in_position.z, 1.0);
}