#include "UILabel.h"

void UILabel::Draw(const glm::vec2& screen_size) {
	glm::vec2 location = glm::vec2(calculated_position.left, calculated_position.bottom);
	text_render.RenderText(location, text, font, screen_size);
}

std::string UILabel::get_text() const {
	return text;
}

void UILabel::set_text(const std::string& value) {
	text = value;
}

entt::resource_handle<Font> UILabel::get_font() const {
	return font;
}

void UILabel::set_font(entt::resource_handle<Font> value) {
	font = value;
}
