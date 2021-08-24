#version 330 core

in vec2 glyph_position;

uniform sampler2D font_atlas;

void main()
{    
    gl_FragColor = vec4(1.0, 1.0, 1.0, texture(font_atlas, glyph_position).r);
}  