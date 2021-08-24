#pragma once

#include <string>
#include "GL/glew.h"

struct Texture {
	Texture(GLuint gl_texture, const std::string& name) {
		this->gl_texture = gl_texture;
		this->name = name;
	}
	GLuint gl_texture;
	std::string name;
};