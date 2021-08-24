#include "LuaDebug.h"

#include "Debug.h"

void LuaDebug::AddDebug(sol::state& lua) {
	auto debug_table = lua.create_table();
	debug_table["log"] = &Debug::Log;
	debug_table["error"] = LogSeverity::Error;
	debug_table["fatal_error"] = LogSeverity::FatalError;
	debug_table["warning"] = LogSeverity::Warning;
	debug_table["info"] = LogSeverity::Information;
	lua.set("Debug", debug_table);
}
