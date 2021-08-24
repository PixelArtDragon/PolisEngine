#include "LuaResource.h"

#include <entt/resource/handle.hpp>
#include "Mesh.h"

void LuaResource::AddResources(sol::state& lua, ResourceLoader& resource_loader) {
	lua.new_usertype<entt::resource_handle<Mesh>>("Mesh",
		"vertices", sol::readonly_property([](entt::resource_handle<Mesh> handle) { return handle->vertices; }),
		"triangles", sol::readonly_property([](entt::resource_handle<Mesh> handle) { return handle->triangles; }));

	lua.set("Resources", sol::new_table());
	lua.globals()["Resources"]["load_texture"] = [&](const std::string& name) {
		return resource_loader.LoadTexture(name);
	};

	lua.globals()["Resources"]["load_mesh"] = [&](const std::string& name) {
		return resource_loader.LoadMesh(name);
	};

	lua.globals()["Resources"]["load_shader"] = [&](const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader) {
		return resource_loader.LoadShaderProgram(name, vertex_shader, fragment_shader);
	};

	lua.globals()["Resources"]["load_font"] = [&](const std::string& file_name) {
		return resource_loader.LoadFont(file_name);
	};

	lua.globals()["Resources"]["quad"] = resource_loader.Primitive(MeshPrimitive::Quad);
	lua.globals()["Resources"]["cube"] = resource_loader.Primitive(MeshPrimitive::Cube);
	lua.globals()["Resources"]["cylinder"] = resource_loader.Primitive(MeshPrimitive::Cylinder);
	lua.globals()["Resources"]["sphere"] = resource_loader.Primitive(MeshPrimitive::Sphere);
	lua.globals()["Resources"]["create_mesh"] = [&](const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
		return resource_loader.LoadMesh(name, vertices, indices);
	};
}
