#pragma once


#include <yoga/Yoga.h>


#include "glm/vec2.hpp"
#include "entt/entt.hpp"
#include "ResourceLoader.h"

#include "InputManager.h"
#include "Timer.h"
#include "UIElement.h"
#include "TextRender.h"
#include "UILabel.h"
#include "UIImage.h"

class UI {
public:
	void Init(ResourceLoader& resource_loader, glm::tvec2<int> size);
	void End();
	bool IsOnUI(const glm::vec2& point);
	void RenderUI(entt::registry& registry, Timer& timer);
	void SetRenderSize(glm::tvec2<int> size);
	void SetInputManager(InputManager* input_manager);
	UIElement* GetRoot();
	UILabel* AddLabel(UIElement& parent);
	UIImage* AddImage(UIElement& parent);
	void DestroyElement(UIElement& element);
private:
	entt::resource_handle<Texture> default_sprite;
	//Gets children and recalculates positions
	std::vector<YGNodeRef> CollapseTree(YGNodeRef node, glm::vec2 position);
	//Gets children without recalculating positions
	std::vector<YGNodeRef> CollapseTree(YGNodeRef node);
	bool is_iterating_elements;
	std::vector<YGNodeRef> elements_to_destroy;
	InputManager* input_manager;
	glm::tvec2<int> screen_size;
	entt::resource_handle<ShaderProgram> ui_program;
	entt::resource_handle<Mesh> ui_quad;
	std::unordered_map<YGNodeRef, std::unique_ptr<UIElement>> elements;
	YGConfigRef config;
	YGNodeRef root;
	TextRender text_render;
};