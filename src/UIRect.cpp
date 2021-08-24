#include "UIRect.h"

#include <yoga/YGFloatOptional.h>

constexpr float unset_value = YGFloatOptional().unwrap();

void UIRect::set_left(float value) {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeLeft, value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

void UIRect::unset_left() {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeLeft, unset_value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

float UIRect::get_left() const {
	switch (rect_type) {
	case RectType::PositionPixels:
	case RectType::PositionPercent:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeLeft).value;
		break;
	case RectType::MarginPixels:
	case RectType::MarginPercent:
		return YGNodeStyleGetMargin(node, YGEdge::YGEdgeLeft).value;
		break;
	case RectType::PaddingPixels:
	case RectType::PaddingPercent:
		return YGNodeStyleGetPadding(node, YGEdge::YGEdgeLeft).value;
		break;
	case RectType::Border:
		return YGNodeStyleGetBorder(node, YGEdge::YGEdgeLeft);
		break;
	default:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeLeft).value;
		break;
	}
}

void UIRect::set_top(float value) {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeTop, value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

void UIRect::unset_top() {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeTop, unset_value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

float UIRect::get_top() const {
	switch (rect_type) {
	case RectType::PositionPixels:
	case RectType::PositionPercent:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeTop).value;
		break;
	case RectType::MarginPixels:
	case RectType::MarginPercent:
		return YGNodeStyleGetMargin(node, YGEdge::YGEdgeTop).value;
		break;
	case RectType::PaddingPixels:
	case RectType::PaddingPercent:
		return YGNodeStyleGetPadding(node, YGEdge::YGEdgeTop).value;
		break;
	case RectType::Border:
		return YGNodeStyleGetBorder(node, YGEdge::YGEdgeTop);
		break;
	default:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeTop).value;
		break;
	}
}

void UIRect::set_right(float value) {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeRight, value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

void UIRect::unset_right() {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeRight, unset_value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

float UIRect::get_right() const {
	switch (rect_type) {
	case RectType::PositionPixels:
	case RectType::PositionPercent:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeRight).value;
		break;
	case RectType::MarginPixels:
	case RectType::MarginPercent:
		return YGNodeStyleGetMargin(node, YGEdge::YGEdgeRight).value;
		break;
	case RectType::PaddingPixels:
	case RectType::PaddingPercent:
		return YGNodeStyleGetPadding(node, YGEdge::YGEdgeRight).value;
		break;
	case RectType::Border:
		return YGNodeStyleGetBorder(node, YGEdge::YGEdgeRight);
		break;
	default:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeRight).value;
		break;
	}
}

void UIRect::set_bottom(float value) {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeBottom, value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

void UIRect::unset_bottom() {
	switch (rect_type) {
	case RectType::PositionPixels:
		YGNodeStyleSetPosition(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::PositionPercent:
		YGNodeStyleSetPositionPercent(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::MarginPixels:
		YGNodeStyleSetMargin(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::MarginPercent:
		YGNodeStyleSetMarginPercent(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::PaddingPixels:
		YGNodeStyleSetPadding(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::PaddingPercent:
		YGNodeStyleSetPaddingPercent(node, YGEdge::YGEdgeBottom, unset_value);
		break;
	case RectType::Border:
		break;
	default:
		break;
	}
}

float UIRect::get_bottom() const {
	switch (rect_type) {
	case RectType::PositionPixels:
	case RectType::PositionPercent:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeBottom).value;
		break;
	case RectType::MarginPixels:
	case RectType::MarginPercent:
		return YGNodeStyleGetMargin(node, YGEdge::YGEdgeBottom).value;
		break;
	case RectType::PaddingPixels:
	case RectType::PaddingPercent:
		return YGNodeStyleGetPadding(node, YGEdge::YGEdgeBottom).value;
		break;
	case RectType::Border:
		return YGNodeStyleGetBorder(node, YGEdge::YGEdgeBottom);
		break;
	default:
		return YGNodeStyleGetPosition(node, YGEdge::YGEdgeBottom).value;
		break;
	}
}
