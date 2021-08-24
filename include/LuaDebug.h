#pragma once

#include "sol/sol.hpp"

class LuaDebug {
public:
	static void AddDebug(sol::state& lua);
};
