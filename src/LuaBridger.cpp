#include "LuaBridger.h"

#include <string>
#include <filesystem>

#include "LuaGLM.h"

#include "Debug.h"
#include "Engine.h"
#include "LuaInput.h"
#include "LuaComponents.h"
#include "LuaResource.h"
#include "LuaDebug.h"
#include "LuaTime.h"
#include "LuaWorld.h"
#include "LuaUI.h"
#include "LuaWindow.h"

void LuaBridger::Init() {
	lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
}

void LuaBridger::RunMainFile(std::string filename) {
	try {
		lua.script_file(filename);
	} catch (const std::exception& e) {
		//Debug::Log(LogSeverity::FatalError, e.what());
	}
}


void LuaBridger::Bridge(Engine& engine) {

	LuaGLM::RegisterTypes(lua);
	LuaComponents::RegisterComponents(lua);
	LuaUI::RegisterComponents(lua);
	LuaInput::AddInputInterface(lua, engine.input_manager);
	LuaResource::AddResources(lua, engine.resource_loader);
	LuaDebug::AddDebug(lua);
	LuaComponents::AddComponentFunctions(lua, engine.registry);
	LuaUI::AddComponentFunctions(lua, engine.registry, engine.ui);
	LuaTime::AddTime(lua, engine.timer);
	LuaWorld::AddWorld(lua, engine);
	LuaWindow::AddWindowInterface(lua, engine.window);
}
