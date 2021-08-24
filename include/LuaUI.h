#pragma once

#include "sol/sol.hpp"
#include <entt/entt.hpp>

#include "UI.h"


class LuaUI {
public:
	static void RegisterComponents(sol::state& lua);
	static void AddComponentFunctions(sol::state& lua, entt::registry& registry, UI& ui);
};

