#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include <glm/gtx/hash.hpp>
#include <entt/entt.hpp>

#include "BoundingVolume.h"
#include "Transform.h"

class Scene
{
public:
	Scene(float cell_size = 1.0f);
	float get_cell_size() const;
	void set_cell_size(float new_cell_size);
	void update_graph(entt::registry& registry);
	std::unordered_set<entt::entity> get_entities(BoundingVolume query_volume) const;
	std::unordered_set<entt::entity> get_entities(std::vector<BoundingVolume> query_volumes) const;
private:
	float p_cell_size;
	bool p_must_recalculate_all_entities;
	std::unordered_map<glm::ivec3, std::unordered_set<entt::entity>> p_hashgrid;
	glm::ivec3 p_get_cell(glm::vec3 position) const;

	std::vector<glm::ivec3> p_get_cells(BoundingVolume volume) const;
};