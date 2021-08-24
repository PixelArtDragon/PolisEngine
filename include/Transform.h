#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::quat rotation = glm::quat();
	glm::mat4 matrix() const {
		return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
	}
};

