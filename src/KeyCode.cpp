#include "KeyCode.h"

const std::unordered_map<std::string, KeyCode> KeyCodeConverter::stringToKeyCode{
	{"Unknown", KeyCode::Unknown},
	{"Space", KeyCode::Space},
	{"Apostrophe", KeyCode::Apostrophe},
	{"Comma", KeyCode::Comma},
	{"Minus", KeyCode::Minus},
	{"Period", KeyCode::Period},
	{"Slash", KeyCode::Slash},
	{"Num0", KeyCode::Num0},
	{"Num1", KeyCode::Num1},
	{"Num2", KeyCode::Num2},
	{"Num3", KeyCode::Num3},
	{"Num4", KeyCode::Num4},
	{"Num5", KeyCode::Num5},
	{"Num6", KeyCode::Num6},
	{"Num7", KeyCode::Num7},
	{"Num8", KeyCode::Num8},
	{"Num9", KeyCode::Num9},
	{"Semicolon", KeyCode::Semicolon},
	{"Equal", KeyCode::Equal},
	{"A", KeyCode::A},
	{"B", KeyCode::B},
	{"C", KeyCode::C},
	{"D", KeyCode::D},
	{"E", KeyCode::E},
	{"F", KeyCode::F},
	{"G", KeyCode::G},
	{"H", KeyCode::H},
	{"I", KeyCode::I},
	{"J", KeyCode::J},
	{"K", KeyCode::K},
	{"L", KeyCode::L},
	{"M", KeyCode::M},
	{"N", KeyCode::N},
	{"O", KeyCode::O},
	{"P", KeyCode::P},
	{"Q", KeyCode::Q},
	{"R", KeyCode::R},
	{"S", KeyCode::S},
	{"T", KeyCode::T},
	{"U", KeyCode::U},
	{"V", KeyCode::V},
	{"W", KeyCode::W},
	{"X", KeyCode::X},
	{"Y", KeyCode::Y},
	{"Z", KeyCode::Z},
	{"Left_Bracket", KeyCode::Left_Bracket},
	{"Backslash", KeyCode::Backslash},
	{"Right_Bracket", KeyCode::Right_Bracket},
	{"Grave_Accent", KeyCode::Grave_Accent},
	{"Escape", KeyCode::Escape},
	{"Enter", KeyCode::Enter},
	{"Tab", KeyCode::Tab},
	{"Backspace", KeyCode::Backspace},
	{"Insert", KeyCode::Insert},
	{"Delete", KeyCode::Delete},
	{"Right", KeyCode::Right},
	{"Left", KeyCode::Left},
	{"Down", KeyCode::Down},
	{"Up", KeyCode::Up},
	{"Page_Up", KeyCode::Page_Up},
	{"Page_Down", KeyCode::Page_Down},
	{"Home", KeyCode::Home},
	{"End", KeyCode::End},
	{"Caps_Lock", KeyCode::Caps_Lock},
	{"Scroll_Lock", KeyCode::Scroll_Lock},
	{"Num_Lock", KeyCode::Num_Lock},
	{"Print_Screen", KeyCode::Print_Screen},
	{"Pause", KeyCode::Pause},
	{"F1", KeyCode::F1},
	{"F2", KeyCode::F2},
	{"F3", KeyCode::F3},
	{"F4", KeyCode::F4},
	{"F5", KeyCode::F5},
	{"F6", KeyCode::F6},
	{"F7", KeyCode::F7},
	{"F8", KeyCode::F8},
	{"F9", KeyCode::F9},
	{"F10", KeyCode::F10},
	{"F11", KeyCode::F11},
	{"F12", KeyCode::F12},
	{"F13", KeyCode::F13},
	{"F14", KeyCode::F14},
	{"F15", KeyCode::F15},
	{"F16", KeyCode::F16},
	{"F17", KeyCode::F17},
	{"F18", KeyCode::F18},
	{"F19", KeyCode::F19},
	{"F20", KeyCode::F20},
	{"F21", KeyCode::F21},
	{"F22", KeyCode::F22},
	{"F23", KeyCode::F23},
	{"F24", KeyCode::F24},
	{"F25", KeyCode::F25},
	{"Left_Shift", KeyCode::Left_Shift},
	{"Left_Control", KeyCode::Left_Control},
	{"Left_Alt", KeyCode::Left_Alt},
	{"Right_Shift", KeyCode::Right_Shift},
	{"Right_Control", KeyCode::Right_Control},
	{"Right_Alt", KeyCode::Right_Alt},
	{"Numpad0", KeyCode::Numpad0},
	{"Numpad1", KeyCode::Numpad1},
	{"Numpad2", KeyCode::Numpad2},
	{"Numpad3", KeyCode::Numpad3},
	{"Numpad4", KeyCode::Numpad4},
	{"Numpad5", KeyCode::Numpad5},
	{"Numpad6", KeyCode::Numpad6},
	{"Numpad7", KeyCode::Numpad7},
	{"Numpad8", KeyCode::Numpad8},
	{"Numpad9", KeyCode::Numpad9},
	{"NumpadDecimal", KeyCode::NumpadDecimal},
	{"NumpadDivide", KeyCode::NumpadDivide},
	{"NumpadMultiply", KeyCode::NumpadMultiply},
	{"NumpadSubtract", KeyCode::NumpadSubtract},
	{"NumpadAdd", KeyCode::NumpadAdd},
	{"NumpadEnter", KeyCode::NumpadEnter},
	{"NumpadEqual", KeyCode::NumpadEqual}
};