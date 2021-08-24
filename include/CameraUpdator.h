#pragma once
#include <entt/entt.hpp>

#include "Transform.h"
#include "Camera.h"

struct CameraUpdator {
	static void UpdateCameras(entt::registry& registry) {
		auto view = registry.view<Transform, Camera>();
		for (auto entity : view) {
			Transform& transform = registry.get<Transform>(entity);
			Camera& camera = registry.get<Camera>(entity);
			camera.view = glm::inverse(transform.matrix());
		}
	}
};