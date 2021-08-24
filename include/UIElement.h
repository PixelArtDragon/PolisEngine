#pragma once

#include <yoga/Yoga.h>

#include "InputManager.h"
#include "Rect.h"
#include "UIRect.h"
#include "UIInteractions.h"

class UIElement {
public:
	YGNodeRef node;
	UIInteractions callbacks;
	virtual void Draw(const glm::vec2& screen_size) {};


	void Interact(const InputManager& input_manager);
	void OnMouseEnter(glm::vec2 mouse_position);
	void OnMouseLeave(glm::vec2 mouse_position);
	void OnMouseOver(glm::vec2 mouse_position);
	void OnMouseDown(glm::vec2 mouse_position, Mousebutton mouse_button);
	void OnMousePressed(glm::vec2 mouse_position, Mousebutton mouse_button);
	void OnMouseReleased(glm::vec2 mouse_position, Mousebutton mouse_button);

	Rect calculated_position;

	UIRect get_position_pixels();
	UIRect get_position_percent();
	YGPositionType get_position_type();
	void set_position_type(YGPositionType position_type);
	YGAlign get_align_content();
	void set_align_content(YGAlign alignment);
	YGAlign get_align_items();
	void set_align_items(YGAlign alignment);
	YGAlign get_align_self();
	void set_align_self(YGAlign alignment);
	float get_aspect_ratio();
	void set_aspect_ratio(float aspect_ratio);
	YGFlexDirection get_flex_direction();
	void set_flex_direction(YGFlexDirection flex_direction);
	YGWrap get_flex_wrap();
	void set_flex_wrap(YGWrap flex_wrap);
	float get_flex_grow();
	void set_flex_grow(float flex_grow);
	float get_flex_shrink();
	void set_flex_shrink(float flex_shrink);
	float get_flex_basis();
	void set_flex_basis(float flex_basis);
	YGJustify get_justify_content();
	void set_justify_content(YGJustify justify_content);
	YGDirection get_layout_direction();
	void set_layout_direction(YGDirection layout_direction);
	UIRect get_margin_pixels();
	UIRect get_margin_percent();
	UIRect get_padding_pixels();
	UIRect get_padding_percent();
	UIRect get_border();
	float get_min_width();
	void set_min_width_pixels(float min_width);
	void set_min_width_percent(float min_width);
	float get_max_width();
	void set_max_width_pixels(float max_width);
	void set_max_width_percent(float max_width);
	float get_min_height();
	void set_min_height_pixels(float min_height);
	void set_min_height_percent(float min_height);
	float get_max_height();
	void set_max_height_pixels(float max_height);
	void set_max_height_percent(float max_height);
	float get_width();
	void set_width_pixels(float width);
	void set_width_percent(float width);
	float get_height();
	void set_height_pixels(float height);
	void set_height_percent(float height);
};

