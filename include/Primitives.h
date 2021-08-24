#pragma once

#include <memory>

#include "Mesh.h"

class Primitives {
public:
	static void Init() {
		quad = std::make_shared<Mesh>();
		quad->vertices = std::vector<Vertex>{
			Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec3(0,1,0), glm::vec2(0,0)),
			Vertex(glm::vec3( 0.5, -0.5, 0), glm::vec3(0,1,0), glm::vec2(1,0)),
			Vertex(glm::vec3(-0.5,  0.5, 0), glm::vec3(0,1,0), glm::vec2(0,1)),
			Vertex(glm::vec3( 0.5,  0.5, 0), glm::vec3(0,1,0), glm::vec2(1,1))
		};
		quad->triangles = std::vector<unsigned int>{
			0, 1, 2,
			2, 1, 3
		};
	}
	static std::shared_ptr<Mesh> quad;
	static std::shared_ptr<Mesh> cube;
	static std::shared_ptr<Mesh> cylinder;
	static std::shared_ptr<Mesh> sphere;
};

