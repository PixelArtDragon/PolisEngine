#pragma once

#include "entt/resource/handle.hpp"

#include "ShaderProgram.h"

struct FullscreenRenderer {
	entt::resource_handle<ShaderProgram> shader_program;
	static GLuint quad_vao;
	static GLuint quad_vbo;
	static GLuint quad_ebo;
	static void Init();
	void Bind();
	void Render();
};