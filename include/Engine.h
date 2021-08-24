#pragma once
#include <memory>
#include "entt/entt.hpp"

#include "InputManager.h"
#include "ResourceLoader.h"
#include "Rendering.h"
#include "Window.h"
#include "LuaBridger.h"
#include "Timer.h"
#include "UI.h"

const std::string LUA_MAIN_FILE = "Main.lua";

class Engine {
public:
	entt::registry registry;

	Engine() {}
	~Engine();
	void Init();
	void StartGameLoop();

	ResourceLoader resource_loader{};
	Rendering rendering{};
	Window window;
	LuaBridger lua_bridger{};
	InputManager input_manager; //Order here is important, since we want the lua state destroyed after InputManager is destroyed
	Timer timer;
	UI ui;
};

