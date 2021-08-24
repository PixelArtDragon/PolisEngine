#pragma once

#include "glm/mat4x4.hpp"

struct Camera {
	bool main;
	glm::mat4 projection;
	glm::mat4 view;
	void set_orthographic(float left, float right, float bottom, float top, float near, float far) {
		projection = glm::ortho(left, right, bottom, top, near, far);
	}
	void set_perspective(float fov, float aspect_ratio, float z_near, float z_far) {
		projection = glm::perspective(fov, aspect_ratio, z_near, z_far);
	}
};

