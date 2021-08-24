#include "UIElement.h"


void UIElement::Interact(const InputManager& input_manager) {
	bool was_on_element = calculated_position.contains_point(input_manager.last_mouse_position);
	bool is_on_element = calculated_position.contains_point(input_manager.current_mouse_position);
	if (is_on_element) {
		OnMouseOver(input_manager.current_mouse_position);
		if (!was_on_element) {
			OnMouseEnter(input_manager.current_mouse_position);
		}
		for (auto mousebutton_down : input_manager.down_mousebuttons) {
			OnMouseDown(input_manager.current_mouse_position, mousebutton_down);
		}
		for (auto pressed_mousebutton : input_manager.mousebuttons_pressed_this_frame) {
			OnMousePressed(input_manager.current_mouse_position, pressed_mousebutton);
		}
		for (auto released_mousebutton : input_manager.mousebuttons_released_this_frame) {
			OnMouseReleased(input_manager.current_mouse_position, released_mousebutton);
		}
	}
	if (!is_on_element && was_on_element) {
		OnMouseLeave(input_manager.current_mouse_position);
	}
}

void UIElement::OnMouseEnter(glm::vec2 mouse_position) {
	if (!callbacks.on_mouse_enter) {
		return;
	}
	callbacks.on_mouse_enter.call(mouse_position);
}

void UIElement::OnMouseLeave(glm::vec2 mouse_position) {
	if (!callbacks.on_mouse_leave) {
		return;
	}
	callbacks.on_mouse_leave.call(mouse_position);
}

void UIElement::OnMouseOver(glm::vec2 mouse_position) {
	if (!callbacks.on_mouse_over) {
		return;
	}
	callbacks.on_mouse_over.call(mouse_position);
}

void UIElement::OnMouseDown(glm::vec2 mouse_position, Mousebutton mouse_button) {
	auto callback_ref = callbacks.on_mousebutton_down.find(mouse_button);
	if (callback_ref != callbacks.on_mousebutton_down.end()) {
		if (!callback_ref->second) {
			return;
		}
		callback_ref->second.call(mouse_position);
	}
}

void UIElement::OnMousePressed(glm::vec2 mouse_position, Mousebutton mouse_button) {
	auto callback_ref = callbacks.on_mousebutton_pressed.find(mouse_button);
	if (callback_ref != callbacks.on_mousebutton_pressed.end()) {
		if (!callback_ref->second) {
			return;
		}
		callback_ref->second.call(mouse_position);
	}
}

void UIElement::OnMouseReleased(glm::vec2 mouse_position, Mousebutton mouse_button) {
	auto callback_ref = callbacks.on_mousebutton_released.find(mouse_button);
	if (callback_ref != callbacks.on_mousebutton_released.end()) {
		if (!callback_ref->second) {
			return;
		}
		callback_ref->second.call(mouse_position);
	}
}

UIRect UIElement::get_position_pixels() {
	return UIRect(node, RectType::PositionPixels);
}

UIRect UIElement::get_position_percent() {
	return UIRect(node, RectType::PositionPercent);
}

YGPositionType UIElement::get_position_type() {
	return YGNodeStyleGetPositionType(node);
}

void UIElement::set_position_type(YGPositionType position_type) {
	YGNodeStyleSetPositionType(node, position_type);
}

YGAlign UIElement::get_align_content() {
	return YGNodeStyleGetAlignContent(node);
}

void UIElement::set_align_content(YGAlign alignment) {
	YGNodeStyleSetAlignContent(node, alignment);
}

YGAlign UIElement::get_align_items() {
	return YGNodeStyleGetAlignItems(node);
}

void UIElement::set_align_items(YGAlign alignment) {
	YGNodeStyleSetAlignItems(node, alignment);
}

YGAlign UIElement::get_align_self() {
	return YGNodeStyleGetAlignSelf(node);
}

void UIElement::set_align_self(YGAlign alignment) {
	YGNodeStyleSetAlignSelf(node, alignment);
}

float UIElement::get_aspect_ratio() {
	return YGNodeStyleGetAspectRatio(node);
}

void UIElement::set_aspect_ratio(float aspect_ratio) {
	YGNodeStyleSetAspectRatio(node, aspect_ratio);
}

YGFlexDirection UIElement::get_flex_direction() {
	return YGNodeStyleGetFlexDirection(node);
}

void UIElement::set_flex_direction(YGFlexDirection flex_direction) {
	YGNodeStyleSetFlexDirection(node, flex_direction);
}

YGWrap UIElement::get_flex_wrap() {
	return YGNodeStyleGetFlexWrap(node);
}

void UIElement::set_flex_wrap(YGWrap flex_wrap) {
	YGNodeStyleSetFlexWrap(node, flex_wrap);
}

float UIElement::get_flex_grow() {
	return YGNodeStyleGetFlexGrow(node);
}

void UIElement::set_flex_grow(float flex_grow) {
	YGNodeStyleSetFlexGrow(node, flex_grow);
}

float UIElement::get_flex_shrink() {
	return YGNodeStyleGetFlexShrink(node);
}

void UIElement::set_flex_shrink(float flex_shrink) {
	YGNodeStyleSetFlexShrink(node, flex_shrink);
}

float UIElement::get_flex_basis() {
	return YGNodeStyleGetFlexBasis(node).value;
}

void UIElement::set_flex_basis(float flex_basis) {
	(flex_basis < 0 ?
		YGNodeStyleSetFlexBasisAuto(node) :
		YGNodeStyleSetFlexBasis(node, flex_basis)
	);
}

YGJustify UIElement::get_justify_content() {
	return YGNodeStyleGetJustifyContent(node);
}

void UIElement::set_justify_content(YGJustify justify_content) {
	YGNodeStyleSetJustifyContent(node, justify_content);
}

YGDirection UIElement::get_layout_direction() {
	return YGNodeStyleGetDirection(node);
}

void UIElement::set_layout_direction(YGDirection layout_direction) {
	YGNodeStyleSetDirection(node, layout_direction);
}

UIRect UIElement::get_margin_pixels() {
	return UIRect(node, RectType::MarginPixels);
}

UIRect UIElement::get_margin_percent() {
	return UIRect(node, RectType::MarginPercent);
}

UIRect UIElement::get_padding_pixels() {
	return UIRect(node, RectType::PaddingPixels);
}

UIRect UIElement::get_padding_percent() {
	return UIRect(node, RectType::PaddingPercent);
}

UIRect UIElement::get_border() {
	return UIRect(node, RectType::Border);
}

float UIElement::get_min_width() {
	return YGNodeStyleGetMinWidth(node).value;
}

void UIElement::set_min_width_pixels(float min_width) {
	YGNodeStyleSetMinWidth(node, min_width);
}

void UIElement::set_min_width_percent(float min_width) {
	YGNodeStyleSetMinWidthPercent(node, min_width);
}

float UIElement::get_max_width() {
	return YGNodeStyleGetMaxWidth(node).value;
}

void UIElement::set_max_width_pixels(float max_width) {
	YGNodeStyleSetMaxWidth(node, max_width);
}

void UIElement::set_max_width_percent(float max_width) {
	YGNodeStyleSetMaxWidthPercent(node, max_width);
}

float UIElement::get_min_height() {
	return YGNodeStyleGetMinHeight(node).value;
}

void UIElement::set_min_height_pixels(float min_height) {
	YGNodeStyleSetMinHeight(node, min_height);
}

void UIElement::set_min_height_percent(float min_height) {
	YGNodeStyleSetMinHeightPercent(node, min_height);
}

float UIElement::get_max_height() {
	return YGNodeStyleGetMaxHeight(node).value;
}

void UIElement::set_max_height_pixels(float max_height) {
	YGNodeStyleSetMaxHeight(node, max_height);
}

void UIElement::set_max_height_percent(float max_height) {
	YGNodeStyleSetMaxHeightPercent(node, max_height);
}

float UIElement::get_width() {
	return YGNodeStyleGetWidth(node).value;
}

void UIElement::set_width_pixels(float width) {
	YGNodeStyleSetWidth(node, width);
}

void UIElement::set_width_percent(float width) {
	YGNodeStyleSetWidthPercent(node, width);
}

float UIElement::get_height() {
	return YGNodeStyleGetHeight(node).value;
}

void UIElement::set_height_pixels(float height) {
	YGNodeStyleSetHeight(node, height);
}

void UIElement::set_height_percent(float height) {
	YGNodeStyleSetHeightPercent(node, height);
}
