#pragma once

#include <string>
#include "entt/resource/loader.hpp"

#include "Font.h"
#include "TextRender.h"

struct FontLoader final : entt::resource_loader<FontLoader, Font> {
	std::shared_ptr<Font> load(const std::string& font_file) const;
};

