#pragma once

#include <glm/vec3.hpp>

struct DirectionalLight {
	float intensity;
	glm::vec3 color;
	glm::vec3 direction;
};