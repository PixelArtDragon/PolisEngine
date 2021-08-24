#include "LuaComponents.h"
#include <entt/resource/handle.hpp>
#include "Renderable.h"
#include "Transform.h"
#include "Camera.h"
#include "AreaLight.h"
#include "Transform.h"
#include "DirectionalLight.h"
#include "ScriptRef.h"
#include "LuaEntity.h"

void LuaComponents::RegisterComponents(sol::state& lua) {
	lua.new_usertype<Vertex>("Vertex",
		"position", &Vertex::position,
		"normal", &Vertex::normal,
		"uv", &Vertex::uv);

	lua.new_usertype<LuaCallback>("Callback",
		sol::constructors<LuaCallback(sol::object, sol::function)>()
	);

	lua.new_usertype<Renderable>("Renderable",
		"mesh", &Renderable::mesh,
		"textures", &Renderable::textures,
		"shader_program", &Renderable::shader_program);

	lua.new_usertype<Camera>("Camera",
		"set_orthographic", &Camera::set_orthographic,
		"set_perspective", &Camera::set_perspective,
		"main", &Camera::main);

	lua.new_usertype<Transform>("Transform",
		"position", &Transform::position,
		"rotation", &Transform::rotation,
		"scale", &Transform::scale);

	lua.new_usertype<AreaLight>("PointLight",
		"intensity", &AreaLight::intensity,
		"color", &AreaLight::color,
		"shape", &AreaLight::shape);

	lua.new_usertype<DirectionalLight>("DirectionalLight",
		"intensity", &DirectionalLight::intensity,
		"color", &DirectionalLight::color,
		"direction", &DirectionalLight::direction);
	
	lua.new_usertype<ScriptRef>("ScriptRef",
		"object", &ScriptRef::callback);
}

void LuaComponents::AddComponentFunctions(sol::state& lua, entt::registry& registry) {
	auto components_table = lua.create_table();

	components_table["add_renderable"] = [&](LuaEntity entity) {
		registry.emplace<Renderable>(entity.entity);
	};
	components_table["add_transform"] = [&](LuaEntity entity) {
		registry.emplace<Transform>(entity.entity);
	};
	components_table["add_camera"] = [&](LuaEntity entity) {
		registry.emplace<Camera>(entity.entity);
	};
	components_table["add_area_light"] = [&](LuaEntity entity) {
		registry.emplace<AreaLight>(entity.entity);
	};

	components_table["add_directional_light"] = [&](LuaEntity entity) {
		registry.emplace<DirectionalLight>(entity.entity);
	};

	components_table["add_script_ref"] = [&](LuaEntity entity, const LuaCallback& callback) {
		ScriptRef& ref_component = registry.emplace<ScriptRef>(entity.entity);
		ref_component.callback = callback;
	};

	lua.new_usertype<LuaEntity>("Entity",
		"renderable", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<Renderable>(self.entity));
		}),
		"transform", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<Transform>(self.entity));
		}),
		"directional_light", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<DirectionalLight>(self.entity));
		}),
		"area_light", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<AreaLight>(self.entity));
		}),
		"script_ref", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<ScriptRef>(self.entity));
		}),
		"camera", sol::readonly_property([&](const LuaEntity self) {
			return std::ref(registry.get<Camera>(self.entity));
		})
	);

	components_table["create_entity"] = [&]() {
		LuaEntity entity;
		entity.entity = registry.create();
		return entity;
	};

	components_table["destroy_entity"] = [&](const LuaEntity& entity) {
		registry.destroy(entity.entity);
	};

	lua.set("Components", components_table);
}
