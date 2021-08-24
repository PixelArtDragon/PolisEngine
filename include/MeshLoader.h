#pragma once

#include <string>
#include "entt/resource/loader.hpp"

#include "Mesh.h"

struct MeshLoader final : entt::resource_loader<MeshLoader, Mesh> {
	std::shared_ptr<Mesh> load(const std::string& filename) const;
	std::shared_ptr<Mesh> load(const std::string& name, const std::vector<Vertex> vertices, const std::vector<unsigned int> triangles) const;
};