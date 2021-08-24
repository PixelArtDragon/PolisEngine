#pragma once

#include "sol/sol.hpp"
#include "Timer.h"

class LuaTime {
public:
	static void AddTime(sol::state& lua, Timer& timer);
};

