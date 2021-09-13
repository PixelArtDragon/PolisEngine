#version 330 core

in vec2 coordinate;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color;

uniform sampler2D l_diffuse;
uniform sampler2D l_specular;

void main() {
	vec3 albedo = texture(g_color, coordinate).rgb * 0.1;
	vec3 diffuse = texture(l_diffuse, coordinate).rgb;
	vec3 specular = texture(l_specular, coordinate).rgb;

	gl_FragColor = vec4(albedo + diffuse + specular, 1.0);
}