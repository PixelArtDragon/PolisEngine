#version 330 core

layout (location = 0) in vec3 in_position;

uniform mat4 camera_transform;
uniform mat4 object_transform;

void main() {
	gl_Position = camera_transform * object_transform * vec4(in_position, 1.0);
}