#include "LuaGLM.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/quaternion.hpp"

void LuaGLM::RegisterTypes(sol::state& lua) {
	lua.new_usertype<glm::vec2>("Vec2",
		sol::constructors<glm::vec2(), glm::vec2(float, float)>(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y,
		"length", &glm::vec2::length,
		sol::meta_function::addition, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(&glm::operator+),
		sol::meta_function::unary_minus, sol::resolve<glm::vec2(const glm::vec2&)>(&glm::operator-),
		"scale", [](const glm::vec2& self, float scale) { return scale * self; },
		"normalized", [](const glm::vec2& self) { return glm::normalize(self); });

	lua.new_usertype<glm::ivec2>("Vec2Int",
		sol::constructors<glm::ivec2(), glm::ivec2(int, int), glm::ivec2(float, float)>(),
		"x", &glm::ivec2::x,
		"y", &glm::ivec2::y,
		"length", &glm::ivec2::length,
		sol::meta_function::addition, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(&glm::operator+),
		sol::meta_function::unary_minus, sol::resolve<glm::ivec2(const glm::ivec2&)>(&glm::operator-)
	);

	lua.new_usertype<glm::vec3>("Vec3",
		sol::constructors<glm::vec3(), glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		"length", &glm::vec3::length,
		sol::meta_function::addition, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(&glm::operator+),
		sol::meta_function::unary_minus, sol::resolve<glm::vec3(const glm::vec3&)>(&glm::operator-),
		sol::meta_function::subtraction, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(&glm::operator-),
		"scale", [](const glm::vec3& self, float scale) { return scale * self; },
		"normalized", [](const glm::vec3& self) { return glm::normalize(self); });

	lua.new_usertype<glm::quat>("Quat",
		sol::constructors<glm::quat(), glm::quat(float, float, float, float)>(),
		"w", &glm::quat::w,
		"x", &glm::quat::x,
		"y", &glm::quat::y,
		"z", &glm::quat::z);

	lua["Quat"]["angle_axis"] = [](float rotation, const glm::vec3 axis) {
		return glm::angleAxis(rotation, axis);
	};
}
