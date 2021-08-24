#pragma once

#include "entt/entt.hpp"
#include "sol/sol.hpp"

class ScriptUpdator {
public:
	static void Update(entt::registry& registry, float dt);
};

