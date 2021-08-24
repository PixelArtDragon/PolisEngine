#pragma once

#include <glm/vec2.hpp>
#include <string>

#include "Font.h"
#include "ResourceLoader.h"

class TextRender {
public:
	void Init(ResourceLoader& resource_loader);
	void RenderText(glm::vec2 start_location, const std::string& text, const Font& font, const glm::vec2& screen_size);
private:
	entt::resource_handle<ShaderProgram> shader_program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};