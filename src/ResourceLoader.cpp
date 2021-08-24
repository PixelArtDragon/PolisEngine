#include "ResourceLoader.h"

#include "entt/core/hashed_string.hpp"

#include "TextureLoader.h"
#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "ShaderProgramLoader.h"
#include "FontLoader.h"

constexpr auto quad_identifier = entt::hashed_string("quad");
constexpr auto cube_identifier = entt::hashed_string("cube");
constexpr auto cylinder_identifier = entt::hashed_string("cylinder");
constexpr auto sphere_identifier = entt::hashed_string("sphere");

constexpr auto sphere_file = "Meshes/Sphere.obj";
constexpr auto cube_file = "Meshes/Cube.obj";
constexpr auto cylinder_file = "Meshes/Cylinder.obj";

void ResourceLoader::LoadDefaultResources() {
	auto quad_vertices = std::vector<Vertex>{
			Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec3(0,0,1), glm::vec2(0,0)),
			Vertex(glm::vec3(0.5, -0.5, 0), glm::vec3(0,0,1), glm::vec2(1,0)),
			Vertex(glm::vec3(-0.5,  0.5, 0), glm::vec3(0,0,1), glm::vec2(0,1)),
			Vertex(glm::vec3(0.5,  0.5, 0), glm::vec3(0,0,1), glm::vec2(1,1))
	};
	auto quad_triangles = std::vector<unsigned int>{
		0, 1, 2,
		2, 1, 3
	};
	loaded_meshes.load<MeshLoader>(quad_identifier, "quad", quad_vertices, quad_triangles);
	loaded_meshes.load<MeshLoader>(sphere_identifier, sphere_file)->name = "sphere";
	loaded_meshes.load<MeshLoader>(cylinder_identifier, cylinder_file)->name = "cylinder";
	loaded_meshes.load<MeshLoader>(cube_identifier, cube_file)->name = "cube";
}

entt::resource_handle<Mesh> ResourceLoader::LoadMesh(const std::string& name, const std::vector<Vertex> vertices, const std::vector<unsigned int> triangles) {
	return loaded_meshes.load<MeshLoader>(entt::hashed_string(name.c_str()), name, vertices, triangles);
}

entt::resource_handle<Texture> ResourceLoader::LoadTexture(const std::string& filename) {
    return loaded_textures.load<TextureLoader>(entt::hashed_string(filename.c_str()), filename);
}

entt::resource_handle<Mesh> ResourceLoader::LoadMesh(const std::string& filename) {
    return loaded_meshes.load<MeshLoader>(entt::hashed_string(filename.c_str()), filename);
}

entt::resource_handle<Mesh> ResourceLoader::Primitive(MeshPrimitive shape) {
	switch (shape) 	{
		case MeshPrimitive::Quad: return loaded_meshes.handle(quad_identifier);
		case MeshPrimitive::Cube: return loaded_meshes.handle(cube_identifier);
		case MeshPrimitive::Cylinder: return loaded_meshes.handle(cylinder_identifier);
		case MeshPrimitive::Sphere: return loaded_meshes.handle(sphere_identifier);
		default: return loaded_meshes.handle(quad_identifier);
	}
}

entt::resource_handle<Shader> ResourceLoader::LoadShader(const std::string& filename, ShaderType shader_type) {
    return loaded_shaders.load<ShaderLoader>(entt::hashed_string(filename.c_str()), filename, shader_type);
}

entt::resource_handle<ShaderProgram> ResourceLoader::LoadShaderProgram(const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader) {
    auto vert_shader = LoadShader(vertex_shader, VertexShader);
    auto frag_shader = LoadShader(fragment_shader, FragmentShader);
    return loaded_shader_programs.load<ShaderProgramLoader>(entt::hashed_string(name.c_str()), name, vert_shader.get(), frag_shader.get());
}

entt::resource_handle<Font> ResourceLoader::LoadFont(const std::string& file_name) {
	return loaded_fonts.load<FontLoader>(entt::hashed_string(file_name.c_str()), file_name);
}
