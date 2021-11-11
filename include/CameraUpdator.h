#pragma once
#include <entt/entt.hpp>

#include "Transform.h"
#include "Scene.h"
#include "Camera.h"

struct CameraUpdator {
	static void UpdateCameras(const Scene& scene, entt::registry& registry) {
		//Clear visible flag
		//auto visible_view = registry.view<Visible>();
		//registry.erase<Visible>(visible_view.begin(), visible_view.end());

		auto view = registry.view<Transform, Camera>();
		for (auto entity : view) {
			Transform& transform = registry.get<Transform>(entity);
			Camera& camera = registry.get<Camera>(entity);
			camera.view = glm::inverse(transform.get_world_matrix());
			std::vector<BoundingVolume> query_volumes = {
				BoundingVolume(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, 0.0f, 0.0f)),
				BoundingVolume(glm::vec3( 0.0f, -1.0f, -1.0f), glm::vec3( 1.0f, 0.0f, 0.0f)),
				BoundingVolume(glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3( 0.0f, 1.0f, 0.0f)),
				BoundingVolume(glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3( 1.0f, 1.0f, 0.0f)),
				
				BoundingVolume(glm::vec3(-1.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
				BoundingVolume(glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(1.0f, 0.0f, 1.0f)),
				BoundingVolume(glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 1.0f, 1.0f)),
				BoundingVolume(glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
			};
			for (int i = 0; i < 8; i++)
			{
				query_volumes[i] = query_volumes[i].transform(glm::inverse(camera.projection * camera.view));
			}
			//std::unordered_set<entt::entity> visible_entities = scene.get_entities(query_volumes);
			//Debug::LogInfo("Number of visible entities: " + std::to_string(visible_entities.size()) + " / " + std::to_string(registry.size<Transform>()));
			/*for (auto entity : visible_entities)
			{
				registry.emplace<Visible>(entity);
			}*/
		}
		auto transforms_view = registry.view<Transform>();
		for (auto entity : transforms_view)
		{
			registry.emplace_or_replace<Visible>(entity);
		}
	}
};