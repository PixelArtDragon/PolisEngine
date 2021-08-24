#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"
#include <string>

//Forward declared to prevent circular includes
class Engine;

class LuaBridger {
public:
	void Init();
	void RunMainFile(std::string filename);
	void Bridge(Engine& engine);
	sol::state lua;
};

