#include "FullscreenRenderer.h"

GLuint FullscreenRenderer::quad_vao;
GLuint FullscreenRenderer::quad_vbo;
GLuint FullscreenRenderer::quad_ebo;

void FullscreenRenderer::Init() {
	glGenVertexArrays(1, &quad_vao);
	glBindVertexArray(quad_vao);
	glGenBuffers(1, &quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	float vertices[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		 1,  1
	};

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &quad_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ebo);
	char indices[] = {
		0, 1, 2,
		2, 1, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(char), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void FullscreenRenderer::Bind() {
	glUseProgram(shader_program->program_id);
	glBindVertexArray(quad_vao);
}

void FullscreenRenderer::Render() {
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}