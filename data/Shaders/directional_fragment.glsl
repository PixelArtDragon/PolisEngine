#version 330 core

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color;

uniform vec2 window_size;

uniform vec3 view_pos;
uniform vec3 light_direction;
uniform vec3 light_color;
uniform float light_intensity;

void main() {
	vec2 coordinate = gl_FragCoord.xy / window_size;
	vec3 position = texture(g_position, coordinate).xyz;
	vec3 normal = texture(g_normal, coordinate).xyz;
	vec3 color = texture(g_color, coordinate).rgb;
	float amount = light_intensity * max(dot(normal, -light_direction), 0.0);
	gl_FragColor = vec4((color + light_color) * amount, 1.0);
}