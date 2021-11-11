#include "LuaWindow.h"

void LuaWindow::AddWindowInterface(sol::state& lua, Window& window)
{
	auto window_table = lua.create_table();
	window_table["set_window_title"] = [&](const std::string& new_title)
	{
		window.SetTitle(new_title);
	};
	lua.set("Window", window_table);
}