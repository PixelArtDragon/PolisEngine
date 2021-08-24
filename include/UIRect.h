#pragma once

#include <yoga/Yoga.h>

enum class RectType {
	PositionPercent,
	PositionPixels,
	MarginPercent,
	MarginPixels,
	PaddingPercent,
	PaddingPixels,
	Border
};

class UIRect {
public:
	UIRect(YGNodeRef node, RectType rect_type) : node(node), rect_type(rect_type) {}
	UIRect& operator=(const UIRect&) = delete;

	void set_left(float value);
	void unset_left();
	float get_left() const;
	void set_top(float value);
	void unset_top();
	float get_top() const;
	void set_right(float value);
	void unset_right();
	float get_right() const;
	void set_bottom(float value);
	void unset_bottom();
	float get_bottom() const;
private:
	YGNodeRef node;
	RectType rect_type;
};