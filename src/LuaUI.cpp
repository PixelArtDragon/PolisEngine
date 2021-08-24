#include "LuaUI.h"

void LuaUI::RegisterComponents(sol::state& lua) {
	lua.new_usertype<UIRect>("UIRect",
		"left", sol::property(&UIRect::get_left, &UIRect::set_left),
		"top", sol::property(&UIRect::get_top, &UIRect::set_top),
		"right", sol::property(&UIRect::get_right, &UIRect::set_right),
		"bottom", sol::property(&UIRect::get_bottom, &UIRect::set_bottom),
		"unset_left", &UIRect::unset_left,
		"unset_top", &UIRect::unset_top,
		"unset_right", &UIRect::unset_right,
		"unset_bottom", &UIRect::unset_bottom
	);

	lua.new_usertype<UIInteractions>("UIInteractions",
		"on_mouse_enter", &UIInteractions::on_mouse_enter,
		"on_mouse_leave", &UIInteractions::on_mouse_leave,
		"on_mouse_over", &UIInteractions::on_mouse_over,
		"on_mousebutton_down", &UIInteractions::on_mousebutton_down,
		"on_mousebutton_pressed", &UIInteractions::on_mousebutton_pressed,
		"on_mousebutton_released", &UIInteractions::on_mousebutton_released
	);

	lua["UIPositionType"] = lua.create_table_with(
		"default", YGPositionType::YGPositionTypeRelative,
		"relative", YGPositionType::YGPositionTypeRelative,
		"absolute", YGPositionType::YGPositionTypeAbsolute
	);
	lua["UIAlignContent"] = lua.create_table_with(
		"flex_start", YGAlign::YGAlignFlexStart,
		"flex_end", YGAlign::YGAlignFlexEnd,
		"stretch", YGAlign::YGAlignStretch,
		"center", YGAlign::YGAlignCenter,
		"space_between", YGAlign::YGAlignSpaceBetween,
		"space_around", YGAlign::YGAlignSpaceAround,
		"default", YGAlign::YGAlignFlexStart
	);
	lua["UIAlignItems"] = lua.create_table_with(
		"stretch", YGAlign::YGAlignStretch,
		"flex_start", YGAlign::YGAlignFlexStart,
		"flex_end", YGAlign::YGAlignFlexEnd,
		"center", YGAlign::YGAlignCenter,
		"baseline", YGAlign::YGAlignBaseline,
		"default", YGAlign::YGAlignStretch
	);
	lua["UIAlignSelf"] = lua.create_table_with(
		"auto", YGAlign::YGAlignAuto,
		"stretch", YGAlign::YGAlignStretch,
		"flex_start", YGAlign::YGAlignFlexStart,
		"flex_end", YGAlign::YGAlignFlexEnd,
		"center", YGAlign::YGAlignCenter,
		"baseline", YGAlign::YGAlignBaseline,
		"default", YGAlign::YGAlignAuto
	);
	lua["UIFlexDirection"] = lua.create_table_with(
		"row", YGFlexDirection::YGFlexDirectionRow,
		"column", YGFlexDirection::YGFlexDirectionColumn,
		"row_reverse", YGFlexDirection::YGFlexDirectionRowReverse,
		"column_reverse", YGFlexDirection::YGFlexDirectionColumnReverse,
		"default", YGFlexDirection::YGFlexDirectionRow
	);
	lua["UIFlexWrap"] = lua.create_table_with(
		"no_wrap", YGWrap::YGWrapNoWrap,
		"wrap", YGWrap::YGWrapWrap,
		"wrap_reverse", YGWrap::YGWrapWrapReverse,
		"default", YGWrap::YGWrapNoWrap
	);
	lua["UIJustifyContent"] = lua.create_table_with(
		"flex_start", YGJustify::YGJustifyFlexStart,
		"flex_end", YGJustify::YGJustifyFlexEnd,
		"center", YGJustify::YGJustifyCenter,
		"space_between", YGJustify::YGJustifySpaceBetween,
		"space_around", YGJustify::YGJustifySpaceAround,
		"space_evenly", YGJustify::YGJustifySpaceEvenly,
		"default", YGJustify::YGJustifyFlexStart
	);
	lua["UILayoutDirection"] = lua.create_table_with(
		"ltr", YGDirection::YGDirectionLTR,
		"rtl", YGDirection::YGDirectionRTL,
		"default", YGDirection::YGDirectionLTR
	);
	lua.new_usertype<UIElement>("UIElement",
		"position_pixels", sol::property(&UIElement::get_position_pixels),
		"position_percent", sol::property(&UIElement::get_position_percent),
		"position_type", sol::property(&UIElement::get_position_type, &UIElement::set_position_type),
		"align_content", sol::property(&UIElement::get_align_content, &UIElement::set_align_content),
		"align_items", sol::property(&UIElement::get_align_items, &UIElement::set_align_items),
		"align_self", sol::property(&UIElement::get_align_self, &UIElement::set_align_self),
		"aspect_ratio", sol::property(&UIElement::get_aspect_ratio, &UIElement::set_aspect_ratio),
		"flex_direction", sol::property(&UIElement::get_flex_direction, &UIElement::set_flex_direction),
		"flex_wrap", sol::property(&UIElement::get_flex_wrap, &UIElement::set_flex_wrap),
		"flex_grow", sol::property(&UIElement::get_flex_grow, &UIElement::set_flex_grow),
		"flex_shrink", sol::property(&UIElement::get_flex_shrink, &UIElement::set_flex_shrink),
		"justify_content", sol::property(&UIElement::get_justify_content, &UIElement::set_justify_content),
		"layout_direction", sol::property(&UIElement::get_layout_direction, &UIElement::set_layout_direction),
		"margin_pixels", sol::property(&UIElement::get_margin_pixels),
		"margin_percent", sol::property(&UIElement::get_margin_percent),
		"padding_pixels", sol::property(&UIElement::get_padding_pixels),
		"padding_percent", sol::property(&UIElement::get_padding_percent),
		"border", sol::property(&UIElement::get_border),
		"min_width", sol::readonly_property(&UIElement::get_min_width),
		"min_width_pixels", sol::writeonly_property(&UIElement::set_min_width_pixels),
		"min_width_percent", sol::writeonly_property(&UIElement::set_min_width_percent),
		"max_width", sol::readonly_property(&UIElement::get_max_width),
		"max_width_pixels", sol::writeonly_property(&UIElement::set_max_width_pixels),
		"max_width_percent", sol::writeonly_property(&UIElement::set_max_width_percent),
		"min_height", sol::readonly_property(&UIElement::get_min_height),
		"min_height_pixels", sol::writeonly_property(&UIElement::set_min_height_pixels),
		"min_height_percent", sol::writeonly_property(&UIElement::set_min_height_percent),
		"max_height", sol::readonly_property(&UIElement::get_max_height),
		"max_height_pixels", sol::writeonly_property(&UIElement::set_max_height_pixels),
		"max_height_percent", sol::writeonly_property(&UIElement::set_max_height_percent),
		"width", sol::readonly_property(&UIElement::get_width),
		"width_pixels", sol::writeonly_property(&UIElement::set_width_pixels),
		"width_percent", sol::writeonly_property(&UIElement::set_width_percent),
		"height", sol::readonly_property(&UIElement::get_height),
		"height_pixels", sol::writeonly_property(&UIElement::set_height_pixels),
		"height_percent", sol::writeonly_property(&UIElement::set_height_percent),

		"callbacks", &UIElement::callbacks
	);
	lua.new_usertype<UILabel>("UILabel",
		"text", sol::property(&UILabel::get_text, &UILabel::set_text),
		"font", sol::property(&UILabel::get_font, &UILabel::set_font),
		sol::base_classes, sol::bases<UIElement>()
	);
	lua.new_usertype<UIImage>("UIImage",
		"sprite", sol::property(&UIImage::get_sprite, &UIImage::set_sprite),
		sol::base_classes, sol::bases<UIElement>()
	);
}

void LuaUI::AddComponentFunctions(sol::state& lua, entt::registry& registry, UI& ui) {
	auto ui_components_table = lua.create_table();


	lua.set("UIComponents", ui_components_table);

	auto ui_table = lua.create_table();

	ui_table["create_label"] = [&](UIElement& parent) {
		return ui.AddLabel(parent);
	};
	ui_table["create_image"] = [&](UIElement& parent) {
		return ui.AddImage(parent);
	};

	ui_table["destroy_element"] = [&](UIElement& element) {
		ui.DestroyElement(element);
	};

	ui_table["root"] = ui.GetRoot();
	ui_table["is_on_element"] = [&](const glm::ivec2 & position) {
		return ui.IsOnUI(position);
	};
	lua.set("UI", ui_table);
}
