#include "TextRender.h"
#include "Debug.h"

#define TEXT_VERTEX "Shaders/text_vertex.glsl"
#define TEXT_FRAGMENT "Shaders/text_fragment.glsl"

void TextRender::Init(ResourceLoader& resource_loader) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindVertexArray(0);

	shader_program = resource_loader.LoadShaderProgram("text_shader", TEXT_VERTEX, TEXT_FRAGMENT);
}

void TextRender::RenderText(glm::vec2 location, const std::string& text, const Font& font, const glm::vec2& screen_size) {
	glUseProgram(shader_program->program_id);
	shader_program->SetTexture("font_atlas", 0, font.glyph_atlas);
	shader_program->SetVec2("atlas_size", font.atlas_size);
	shader_program->SetVec2("screen_size", screen_size);
	glBindVertexArray(vao);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (size_t i = 0; i < text.size(); i++) 		{
		const Character& character = font.characters.at(text[i]);
		if (character.size.x == 0) {
			continue;
		}
		float x = location.x + character.bearing.x;
		float y = location.y - (character.size.y - character.bearing.y);

		float w = character.size.x;
		float h = character.size.y;

		float vertices[6][4] = {
			{x,		y - h,		character.position.x - w + 1,	0.0f},
			{x,		y,			character.position.x - w + 1,	h},
			{x + w,	y,			character.position.x,			h},

			{x,		y - h,		character.position.x - w + 1,	0.0f},
			{x + w,	y,			character.position.x,			h},
			{x + w,	y - h,		character.position.x,			0.0f}
		};
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		location.x += character.advance.x >> 6;
	}
	glBindVertexArray(0);
	glUseProgram(0);
}
