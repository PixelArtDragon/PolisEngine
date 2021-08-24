#include "InputManager.h"

#include <assert.h>

#include "Debug.h"

void InputManager::MouseMoved(glm::ivec2 screen_position) {
	if(mouse_moved_callback) {
		LuaCallback callback = mouse_moved_callback;
		callback.call(screen_position);
	}
	last_mouse_position = current_mouse_position;
	current_mouse_position = screen_position;
}

void InputManager::KeyPressed(KeyCode keycode) {
	auto callback_ref = key_pressed_callbacks.find(keycode);
	if (callback_ref != key_pressed_callbacks.end()) {
		LuaCallback callback = callback_ref->second;
		callback.call();
	}
	keys_pressed_this_frame.insert(keycode);
	down_keys.insert(keycode);
}

void InputManager::KeyReleased(KeyCode keycode) {
	auto callback_ref = key_released_callbacks.find(keycode);
	if (callback_ref != key_released_callbacks.end()) {
		LuaCallback callback = callback_ref->second;
		callback.call();
	}
	keys_released_this_frame.insert(keycode);
	down_keys.erase(keycode);
}

void InputManager::MousebuttonPressed(Mousebutton mousebutton) {
	auto callback_ref = mousebutton_pressed_callbacks.find(mousebutton);
	if (callback_ref != mousebutton_pressed_callbacks.end()) {
		LuaCallback callback = callback_ref->second;
		callback.call();
	}
	mousebuttons_pressed_this_frame.insert(mousebutton);
	down_mousebuttons.insert(mousebutton);
}

void InputManager::MousebuttonReleased(Mousebutton mousebutton) {
	auto callback_ref = mousebutton_released_callbacks.find(mousebutton);
	if (callback_ref != mousebutton_released_callbacks.end()) {
		LuaCallback callback = callback_ref->second;
		callback.call();
	}
	mousebuttons_released_this_frame.insert(mousebutton);
	down_mousebuttons.erase(mousebutton);
}

void InputManager::AddCallback(KeyCode keycode, const LuaCallback& callback_object, InputType input_type) {
	std::unordered_map<KeyCode, LuaCallback>* callbacks_table;
	switch (input_type) {
		case InputType::Down: callbacks_table = &key_down_callbacks; break;
		case InputType::Pressed: callbacks_table = &key_pressed_callbacks; break;
		case InputType::Released: callbacks_table = &key_released_callbacks; break;
		default: callbacks_table = nullptr; break;
	}
	if (callbacks_table->find(keycode) != callbacks_table->end()) {
		Debug::Log(LogSeverity::Information, "Overriding existing keycode: " + std::to_string((int)keycode));
		(*callbacks_table)[keycode] = callback_object;
	} else {
		callbacks_table->emplace(keycode, callback_object);
	}
}

void InputManager::AddCallback(Mousebutton button, const LuaCallback& callback_object, InputType input_type) {
	std::unordered_map<Mousebutton, LuaCallback>* callbacks_table;
		switch (input_type) {
		case InputType::Down: callbacks_table = &mousebutton_down_callbacks; break;
		case InputType::Pressed: callbacks_table = &mousebutton_pressed_callbacks; break;
		case InputType::Released: callbacks_table = &mousebutton_released_callbacks; break;
		default: callbacks_table = nullptr; break;
	}
	if (callbacks_table->find(button) != callbacks_table->end()) {
		Debug::Log(LogSeverity::Information, std::string("Overriding existing mousebutton: " + std::to_string((int)button)));
		(*callbacks_table)[button] = callback_object;
	} else {
		callbacks_table->emplace(button, callback_object);
	}
}

void InputManager::AddMouseMovedCallback(const LuaCallback& callback_object) {
	if (mouse_moved_callback) {
		Debug::Log(LogSeverity::Information, "Overriding existing mouse_moved callback.");
		mouse_moved_callback.abandon();
	}
	mouse_moved_callback = callback_object;
}

void InputManager::RemoveCallback(KeyCode keycode, InputType input_type) {
	std::unordered_map<KeyCode, LuaCallback>* callbacks_table;
	switch (input_type) {
		case InputType::Down: callbacks_table = &key_down_callbacks; break;
		case InputType::Pressed: callbacks_table = &key_pressed_callbacks; break;
		case InputType::Released: callbacks_table = &key_released_callbacks; break;
		default: callbacks_table = nullptr; break;
	}
	auto callback = callbacks_table->find(keycode);
	if (callback != callbacks_table->end()) {
		callback->second.abandon();
		callbacks_table->erase(keycode);
	}
}

void InputManager::RemoveCallback(Mousebutton button, InputType input_type) {
	std::unordered_map<Mousebutton, LuaCallback>* callbacks_table;
	switch (input_type) {
		case InputType::Down: callbacks_table = &mousebutton_down_callbacks; break;
		case InputType::Pressed: callbacks_table = &mousebutton_pressed_callbacks; break;
		case InputType::Released: callbacks_table = &mousebutton_released_callbacks; break;
		default: callbacks_table = nullptr; break;
	}
	auto callback = callbacks_table->find(button);
	if (callback != callbacks_table->end()) {
		callback->second.abandon();
		callbacks_table->erase(button);
	}
}

void InputManager::RemoveMouseMovedCallback() {
	mouse_moved_callback.abandon();
}

void InputManager::ClearAllCallbacks() {
	key_down_callbacks.clear();
	key_pressed_callbacks.clear();
	key_released_callbacks.clear();
	mousebutton_down_callbacks.clear();
	mousebutton_pressed_callbacks.clear();
	mousebutton_released_callbacks.clear();
	mouse_moved_callback.abandon();
}

void InputManager::UpdateDownCallbacks() {
	for (auto key : down_keys) {
		auto match = key_down_callbacks.find(key);
		if (match != key_down_callbacks.end()) {
			LuaCallback callback = match->second;
			callback.call();
		}
	}
	for (auto mousebutton : down_mousebuttons) {
		auto match = mousebutton_down_callbacks.find(mousebutton);
		if (match != mousebutton_down_callbacks.end()) {
			LuaCallback callback = match->second;
			callback.call();
		}
	}
	keys_pressed_this_frame.clear();
	keys_released_this_frame.clear();
	mousebuttons_pressed_this_frame.clear();
	mousebuttons_released_this_frame.clear();
}