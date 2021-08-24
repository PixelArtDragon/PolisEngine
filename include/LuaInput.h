#pragma once

#include "sol/sol.hpp"

#include "InputManager.h"

class LuaInput {
public:
	static void AddInputInterface(sol::state& lua, InputManager& input_manager);
};

