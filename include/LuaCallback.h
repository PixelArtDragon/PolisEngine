#pragma once

#include <sol/sol.hpp>

#include "Debug.h"

struct LuaCallback {
	LuaCallback();
	LuaCallback(sol::object object, sol::function function);
	sol::object object;
	sol::function function;
	template <typename ... Types>
	void call(Types ... args) {
		if (!valid()) {
			return;
		}
		try {
			auto result = function(object, args...);
			if (!result.valid()) {
				sol::error err = result;
				Debug::Log(LogSeverity::Error, err.what());
			}
		} catch (const std::exception& e) {
			Debug::Log(LogSeverity::Error, e.what());
		}
	}
	bool valid() const;
	operator bool() const;
	void abandon();
	void deref();
};