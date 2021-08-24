#pragma once

#include "entt/resource/loader.hpp"

#include "Shader.h"

struct ShaderLoader : entt::resource_loader<ShaderLoader, Shader> {
	std::shared_ptr<Shader> load(const std::string& filename, ShaderType shader_type) const;
};