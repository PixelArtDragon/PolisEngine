#pragma once

#include "sol/sol.hpp"

#include "Window.h"

class LuaWindow
{
public:
	static void AddWindowInterface(sol::state& lua, Window& window);
};