#include <memory>
#include <iostream>

#include "Engine.h"

Engine engine;

int main(int argc, char* argv[]) {
	engine.Init();

	engine.StartGameLoop();

	return 0;
}