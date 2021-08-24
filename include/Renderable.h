#pragma once

#include <vector>
#include "entt/resource/handle.hpp"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Mesh.h"

struct Renderable {
	std::vector<entt::resource_handle<Texture>> textures;
	entt::resource_handle<ShaderProgram> shader_program;
	entt::resource_handle<Mesh> mesh;
};