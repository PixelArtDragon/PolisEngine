#version 330 core

in vec2 coordinate;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color;

void main() {
	vec3 position = texture(g_position, coordinate).xyz;
	vec3 normal = texture(g_normal, coordinate).xyz;
	vec3 color = texture(g_color, coordinate).rgb;
	vec3 albedo = color * 0.3;
	gl_FragColor = vec4(albedo, 1.0);
}