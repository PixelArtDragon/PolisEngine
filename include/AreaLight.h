#pragma once

#include "entt/resource/handle.hpp"
#include <glm/vec3.hpp>

#include "Mesh.h"

struct AreaLight {
	float intensity;
	glm::vec3 color;
	entt::resource_handle<Mesh> shape;
};