#pragma once

#include <unordered_map>

#include "Character.h"

struct Font {
	std::unordered_map<char, Character> characters;
	glm::ivec2 atlas_size;
	GLuint glyph_atlas;
};