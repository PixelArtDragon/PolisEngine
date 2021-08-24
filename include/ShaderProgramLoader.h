#pragma once

#include <string>
#include "entt/resource/loader.hpp"

#include "Shader.h"
#include "ShaderProgram.h"

struct ShaderProgramLoader : entt::resource_loader<ShaderProgramLoader, ShaderProgram> {
	std::shared_ptr<ShaderProgram> load(const std::string& name, const Shader & vertex_shader, const Shader & fragment_shader) const;
};

