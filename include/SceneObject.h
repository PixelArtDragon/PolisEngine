#pragma once

#include <entt/entt.hpp>
#include <BoundingVolume.h>

struct SceneObject
{
	BoundingVolume bounding_volume;
	std::vector<glm::ivec3> current_cells;
};