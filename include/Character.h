#pragma once

#include <entt/resource/handle.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>

struct Character {
	glm::ivec2 size;
	glm::ivec2 bearing;
	glm::vec2 position; //Within atlas
	glm::ivec2 advance;
};