#pragma once

#include "sol/sol.hpp"

#include "Engine.h"

class LuaWorld {
public:
	static void AddWorld(sol::state& lua, Engine& engine);
};

