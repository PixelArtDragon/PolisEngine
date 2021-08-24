#pragma once

#include "sol/sol.hpp"
#include "ResourceLoader.h"

class LuaResource {
public:
	static void AddResources(sol::state& lua, ResourceLoader& resource_loader);
};

