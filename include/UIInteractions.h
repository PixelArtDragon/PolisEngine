#pragma once

#include <glm/vec2.hpp>

#include "LuaCallback.h"

struct UIInteractions {
	LuaCallback on_mouse_enter;
	LuaCallback on_mouse_leave;
	LuaCallback on_mouse_over;
	std::unordered_map<Mousebutton, LuaCallback> on_mousebutton_down;
	std::unordered_map<Mousebutton, LuaCallback> on_mousebutton_pressed;
	std::unordered_map<Mousebutton, LuaCallback> on_mousebutton_released;
};