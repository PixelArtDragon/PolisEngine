#pragma once

#include <string>
#include "GL/glew.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "Texture.h"

struct ShaderProgram {
	GLuint program_id;
	std::string name;
	void SetInt(const std::string& name, int value);
	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);
	void SetTexture(const std::string& name, int index, const Texture& value);
	void SetTexture(const std::string& name, int index, GLuint value);
	void SetVec2(const std::string& name, const glm::vec2& value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetVec4(const std::string& name, const glm::vec4& value);
	void SetMat3(const std::string& name, const glm::mat3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);
};