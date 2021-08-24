#include "LuaTime.h"

void LuaTime::AddTime(sol::state& lua, Timer& timer) {
	lua.new_usertype<Timer>("Time",
		"dt", sol::readonly(&Timer::dt));
	lua.set("Time", std::ref(timer));
}
