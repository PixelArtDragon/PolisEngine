#include "LuaInput.h"

void LuaInput::AddInputInterface(sol::state& lua, InputManager& input_manager) {
	auto input_table = lua.create_table();
	
	auto type_table = lua.create_table();
	type_table["pressed"] = InputType::Pressed;
	type_table["down"] = InputType::Down;
	type_table["released"] = InputType::Released;
	input_table["input_type"] = type_table;
	
	auto mouse_table = lua.create_table();
	mouse_table["left_mousebutton"] = Mousebutton::Left;
	mouse_table["right_mousebutton"] = Mousebutton::Right;
	mouse_table["middle_mousebutton"] = Mousebutton::Middle;
	input_table["mousebuttons"] = mouse_table;

	input_table["register_key_callback"] = [&](const std::string& name, sol::object callback, sol::function function, InputType input_type) {
		input_manager.AddCallback(KeyCodeConverter::Convert(name), LuaCallback(callback, function), input_type);
	};
	input_table["register_mousebutton_callback"] = [&](int mouse_button, sol::object callback, sol::function function, InputType input_type) {
		input_manager.AddCallback((Mousebutton)mouse_button, LuaCallback(callback, function), input_type);
	};
	input_table["register_mouse_motion_callback"] = [&](sol::object callback, sol::function function) {
		input_manager.AddMouseMovedCallback(LuaCallback(callback, function));
	};

	input_table["deregister_key_callback"] = [&](const std::string& name, InputType input_type) {
		input_manager.RemoveCallback(KeyCodeConverter::Convert(name), input_type);
	};
	input_table["deregister_mousebutton_callback"] = [&](int mouse_button, InputType input_type) {
		input_manager.RemoveCallback((Mousebutton)mouse_button, input_type);
	};
	input_table["deregister_mouse_motion_callback"] = [&]() {
		input_manager.RemoveMouseMovedCallback();
	};

	input_table["get_mouse_position"] = [&]() {
		return input_manager.current_mouse_position;
	};

	lua.set("Input", input_table);
}
