#pragma once

#include "entt/resource/cache.hpp"

#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Font.h"

enum class MeshPrimitive {
	Quad,
	Cube,
	Cylinder,
	Sphere
};

class ResourceLoader {
public:
	void LoadDefaultResources();
	entt::resource_handle<Texture> LoadTexture(const std::string& filename);
	entt::resource_handle<Mesh> LoadMesh(const std::string& filename);
	entt::resource_handle<Mesh> LoadMesh(const std::string& name, const std::vector<Vertex> vertices, const std::vector<unsigned int> triangles);
	entt::resource_handle<Mesh> Primitive(MeshPrimitive shape);
	entt::resource_handle<Shader> LoadShader(const std::string& filename, ShaderType shader_type);
	entt::resource_handle<ShaderProgram> LoadShaderProgram(const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader);
	entt::resource_handle<Font> LoadFont(const std::string& file_name);
private:
	entt::resource_cache<Texture> loaded_textures{};
	entt::resource_cache<Shader> loaded_shaders{};
	entt::resource_cache<ShaderProgram> loaded_shader_programs{};
	entt::resource_cache<Mesh> loaded_meshes{};
	entt::resource_cache<Font> loaded_fonts{};
};