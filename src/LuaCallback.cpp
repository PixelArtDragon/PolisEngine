#include "LuaCallback.h"

LuaCallback::LuaCallback() {}

LuaCallback::LuaCallback(sol::object object, sol::function function) {
	this->object = sol::object(object);
	this->function = sol::function(function);
}

bool LuaCallback::valid() const {
	return object.valid() && function.valid();
}

LuaCallback::operator bool() const {
	return valid();
}

void LuaCallback::abandon() {
	function.abandon();
	object.abandon();
}

void LuaCallback::deref() {
	object = sol::object(sol::lua_nil);
	function = sol::function(sol::lua_nil);
}
