#pragma once

#include <string>
#include "entt/resource/loader.hpp"

#include "Texture.h"

struct TextureLoader final : entt::resource_loader<TextureLoader, Texture> {
	std::shared_ptr<Texture> load(const std::string& filename) const;
};