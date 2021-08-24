#pragma once

#include <glm/mat3x3.hpp>

struct Rect {
	Rect() : left(0), top(0), right(0), bottom(0) {}
	Rect(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) {}
	float left;
	float top;
	float right;
	float bottom;
	bool contains_point(glm::vec2 point) const {
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}
	glm::mat3 get_transform() const {
		return glm::mat3(glm::vec3(right - left, 0, 0), glm::vec3(0, bottom - top, 0), glm::vec3(left, top, 1));
	}
};