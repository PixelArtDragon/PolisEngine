#include "Engine.h"

#include "Debug.h"

#include "CameraUpdator.h"
#include "ScriptUpdator.h"

Engine::~Engine() {
	input_manager.ClearAllCallbacks();
	ui.End();
	registry.clear();
}

void Engine::Init() {
	window.Init();
	window.SetInputManager(&input_manager);
	window.SetRendering(&rendering);
	rendering.Init(resource_loader, window.size());
	ui.Init(resource_loader, window.size());
	ui.SetInputManager(&input_manager);
	resource_loader.LoadDefaultResources();
	lua_bridger.Init();
	lua_bridger.Bridge(*this);
	lua_bridger.RunMainFile(LUA_MAIN_FILE);
}

void Engine::StartGameLoop() {
	timer.start();
	while (window.is_open()) 	{
		CameraUpdator::UpdateCameras(registry);
		rendering.RenderFrame(registry);
		ui.RenderUI(registry, timer);
		window.SwapBuffers();
		timer.tick();
		ScriptUpdator::Update(registry, timer.dt);
		input_manager.UpdateDownCallbacks();
		window.PollEvents();
	}
}