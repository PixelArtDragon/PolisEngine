#version 330 core

layout (location = 0) out vec3 l_diffuse;
layout (location = 1) out vec3 l_specular;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color;

uniform vec2 window_size;

uniform vec3 light_position;
uniform vec3 view_pos;
uniform float light_intensity;
uniform vec3 light_color;

void main(){
	vec2 coordinate = gl_FragCoord.xy / window_size;
	vec3 position = texture(g_position, coordinate).xyz;
	vec3 normal = texture(g_normal, coordinate).xyz;
	vec3 color = texture(g_color, coordinate).rgb;
	vec3 light_direction = normalize(light_position - position);
	vec3 position_difference = light_position - position;
	float falloff = 1.0 / dot(position_difference, position_difference);
	float diffuse = falloff * light_intensity * max(dot(normal, light_direction), 0.0);

	l_diffuse = diffuse * light_color * color;

	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = falloff * light_intensity * pow(max(dot(light_direction, reflect_direction), 0.0), 32.0);

	l_specular = spec * light_color;

	//gl_FragColor = vec4((color + light_color) * amount, 1.0);
}