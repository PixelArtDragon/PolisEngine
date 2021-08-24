#include "LuaWorld.h"

void LuaWorld::AddWorld(sol::state& lua, Engine& engine) {
	auto world_table = lua.create_table();
	world_table["get_world_position"] = [&](const glm::tvec2<int>& screen_position) {
		return engine.rendering.GetWorldPosition(screen_position);
	};

	lua.set("World", world_table);
}
