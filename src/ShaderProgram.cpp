#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

void ShaderProgram::SetInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void ShaderProgram::SetBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void ShaderProgram::SetTexture(const std::string& name, int index, const Texture& value) {
	SetInt(name, index);
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, value.gl_texture);
}

void ShaderProgram::SetTexture(const std::string& name, int index, GLuint value) {
	SetInt(name, index);
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, value);
}

void ShaderProgram::SetVec2(const std::string& name, const glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(program_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(program_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetMat3(const std::string& name, const glm::mat3& value) {
	glUniformMatrix3fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
