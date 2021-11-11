#include "Scene.h"

#include "SceneObject.h"

Scene::Scene(float cell_size) : p_cell_size(cell_size), p_must_recalculate_all_entities(false) { }

float Scene::get_cell_size() const
{
	return p_cell_size;
}

void Scene::set_cell_size(float new_cell_size)
{
	p_cell_size = new_cell_size;
	p_must_recalculate_all_entities = true;
	p_hashgrid.clear();
}

void Scene::update_graph(entt::registry& registry)
{
	auto view = registry.view<Transform, SceneObject>();
	for (auto entity : view)
	{
		auto [transform, scene_object] = view.get(entity);
		if (p_must_recalculate_all_entities || transform.get_requires_scene_update())
		{
			//Remove previous cells
			for (auto cell : scene_object.current_cells)
			{
				p_hashgrid[cell].erase(entity);
			}
			scene_object.current_cells = p_get_cells(scene_object.bounding_volume.transform(transform.get_world_matrix()));
			for (auto cell : scene_object.current_cells)
			{
				p_hashgrid[cell].emplace(entity);
			}
			transform.p_requires_scene_update = false;
		}
	}
	p_must_recalculate_all_entities = false;
}

std::unordered_set<entt::entity> Scene::get_entities(BoundingVolume query_volume) const
{
	std::unordered_set<entt::entity> entities;
	for (auto cell_coordinate : p_get_cells(query_volume))
	{
		auto cell = p_hashgrid.find(cell_coordinate);
		if (cell != p_hashgrid.end())
		{
			entities.insert(cell->second.begin(), cell->second.end());
		}
	}
	return entities;
}

std::unordered_set<entt::entity> Scene::get_entities(std::vector<BoundingVolume> query_volumes) const
{
	std::unordered_set<entt::entity> entities;
	//std::unordered_set<glm::ivec3> cells;
	std::vector<glm::ivec3> cells;

	for (const auto& volume : query_volumes)
	{
		auto cells_for_volume = p_get_cells(volume);
		//cells.insert(cells_for_volume.begin(), cells_for_volume.end());
		cells.insert(cells.end(), cells_for_volume.begin(), cells_for_volume.end());
	}

	for (auto cell_coordinate : cells)
	{
		auto cell = p_hashgrid.find(cell_coordinate);
		if (cell != p_hashgrid.end())
		{
			entities.insert(cell->second.begin(), cell->second.end());
		}
	}
	return entities;
}

glm::ivec3 Scene::p_get_cell(glm::vec3 position) const
{
	return glm::floor(position / p_cell_size);
}

std::vector<glm::ivec3> Scene::p_get_cells(BoundingVolume volume) const
{
	std::vector<glm::ivec3> cells;
	/*for (float x = volume.minimums.x; x < volume.maximums.x + p_cell_size; x += p_cell_size)
	{
		for (float y = volume.minimums.y; y < volume.maximums.y + p_cell_size; y += p_cell_size)
		{
			for (float z = volume.minimums.z; z < volume.maximums.z + p_cell_size; z += p_cell_size)
			{
				cells.push_back(p_get_cell(glm::vec3(x, y, z)));
			}
		}
	}*/
	for (int x = floor(volume.minimums.x / p_cell_size); x <= floor(volume.maximums.x / p_cell_size); x++)
	{
		for (int y = floor(volume.minimums.y / p_cell_size); y <= floor(volume.maximums.y / p_cell_size); y++)
		{
			for (int z = floor(volume.minimums.z / p_cell_size); z <= floor(volume.maximums.z / p_cell_size); z++)
			{
				cells.push_back(glm::ivec3(x, y, z));
			}
		}
	}
	return cells;
}