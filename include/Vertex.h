#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct Vertex {
	Vertex(){}
	Vertex(glm::vec3 position) : position(position) {}
	Vertex(glm::vec3 position, glm::vec3 normal) : position(position), normal(normal) {}
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv) : position(position), normal(normal), uv(uv) {}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};