#pragma once

#include <string>
#include <vector>
#include "GL/glew.h"

#include "Vertex.h"

struct Mesh {
	Mesh(Mesh& other) = delete;
	Mesh& operator=(Mesh& other) = delete;
	Mesh();
	~Mesh();
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> triangles;
	void Stream();
	void Bind();
	void Draw();
};