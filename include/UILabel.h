#pragma once

#include "UIElement.h"
#include "InputManager.h"
#include <entt/resource/handle.hpp>
#include "Font.h"
#include "TextRender.h"

class UILabel : public UIElement {
public:
	UILabel(TextRender& text_render) : text_render(text_render) {}
	// Inherited via UIElement
	virtual void Draw(const glm::vec2& screen_size) override;
	std::string get_text() const;
	void set_text(const std::string& value);
	entt::resource_handle<Font> get_font() const;
	void set_font(entt::resource_handle<Font> value);
private:
	std::string text;
	entt::resource_handle<Font> font;
	TextRender& text_render;
};

