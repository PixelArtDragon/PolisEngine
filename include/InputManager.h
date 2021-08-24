#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <sol/sol.hpp>
#include "glm/vec2.hpp"

#include "KeyCode.h"
#include "LuaCallback.h"

enum class InputType {
	Pressed,
	Down,
	Released
};

enum class Mousebutton {
	Left = 0,
	Right = 1,
	Middle = 2,
	Button1 = 0,
	Button2 = 1,
	Button3 = 2,
	Button4 = 3,
	Button5 = 4,
	Button6 = 5,
	Button7 = 6,
	Button8 = 7
};

class InputManager {
public:
	void MouseMoved(glm::ivec2 screen_position);
	void KeyPressed(KeyCode keycode);
	void KeyReleased(KeyCode keycode);
	void MousebuttonPressed(Mousebutton mousebutton);
	void MousebuttonReleased(Mousebutton mousebutton);
	void AddCallback(KeyCode keycode, const LuaCallback& callback_object, InputType input_type);
	void AddCallback(Mousebutton button, const LuaCallback& callback_object, InputType input_type);
	void AddMouseMovedCallback(const LuaCallback& callback_object);
	void RemoveCallback(KeyCode button, InputType input_type);
	void RemoveCallback(Mousebutton keycode, InputType input_type);
	void RemoveMouseMovedCallback();
	void ClearAllCallbacks();
	void UpdateDownCallbacks();

	std::unordered_set<KeyCode> down_keys;
	std::unordered_set<KeyCode> keys_pressed_this_frame;
	std::unordered_set<KeyCode> keys_released_this_frame;

	std::unordered_set<Mousebutton> down_mousebuttons;
	std::unordered_set<Mousebutton> mousebuttons_pressed_this_frame;
	std::unordered_set<Mousebutton> mousebuttons_released_this_frame;

	glm::ivec2 current_mouse_position;
	glm::ivec2 last_mouse_position;
private:
	std::unordered_map<KeyCode, LuaCallback> key_down_callbacks{};
	std::unordered_map<KeyCode, LuaCallback> key_pressed_callbacks{};
	std::unordered_map<KeyCode, LuaCallback> key_released_callbacks{};
	std::unordered_map<Mousebutton, LuaCallback> mousebutton_down_callbacks{};
	std::unordered_map<Mousebutton, LuaCallback> mousebutton_pressed_callbacks{};
	std::unordered_map<Mousebutton, LuaCallback> mousebutton_released_callbacks{};
	LuaCallback mouse_moved_callback;
};

