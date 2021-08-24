#pragma once

#include <string>
#include "GL\glew.h"

using ShaderType = bool;

const ShaderType VertexShader = 0;
const ShaderType FragmentShader = 1;

struct Shader {
public:
	GLuint shader_id;
	std::string name;
};