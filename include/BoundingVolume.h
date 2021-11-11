#pragma once

#include <algorithm>
#include <array>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct BoundingVolume
{
	BoundingVolume() {}
	BoundingVolume(glm::vec3 minimums, glm::vec3 maximums) : minimums(minimums), maximums(maximums) {}
	glm::vec3 minimums;
	glm::vec3 maximums;
	BoundingVolume transform(glm::mat4 transformation)
	{
		std::array<glm::vec3, 8> points = {
			minimums,
			glm::vec3(minimums.x, minimums.y, maximums.z),
			glm::vec3(minimums.x, maximums.y, minimums.z),
			glm::vec3(minimums.x, maximums.y, maximums.z),
			glm::vec3(maximums.x, minimums.y, minimums.z),
			glm::vec3(maximums.x, minimums.y, maximums.z),
			glm::vec3(maximums.x, maximums.y, minimums.z),
			maximums
		};
		for (int i = 0; i < 8; i++)
		{
			glm::vec4 result = transformation * glm::vec4(points[i], 1.0f);
			points[i] = result / result.w;
		}
		BoundingVolume transformed_bounding_volume;
		auto x_extremes = std::minmax_element(points.begin(), points.end(), [](const glm::vec3& lhs, const glm::vec3& rhs)
		{
			return lhs.x < rhs.x;
		});
		auto y_extremes = std::minmax_element(points.begin(), points.end(), [](const glm::vec3& lhs, const glm::vec3& rhs)
		{
			return lhs.y < rhs.y;
		});
		auto z_extremes = std::minmax_element(points.begin(), points.end(), [](const glm::vec3& lhs, const glm::vec3& rhs)
		{
			return lhs.z < rhs.z;
		});
		transformed_bounding_volume.minimums = glm::vec3(x_extremes.first->x, y_extremes.first->y, z_extremes.first->z);
		transformed_bounding_volume.maximums = glm::vec3(x_extremes.second->x, y_extremes.second->y, z_extremes.second->z);
		return transformed_bounding_volume;
	}
};