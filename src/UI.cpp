#include "UI.h"

#include "Debug.h"

#define UI_VERTEX "Shaders/ui_vertex.glsl"
#define UI_FRAGMENT "Shaders/ui_fragment.glsl"

void UI::Init(ResourceLoader& resource_loader, glm::tvec2<int> size) {
    screen_size = size;

    text_render.Init(resource_loader);

    ui_program = resource_loader.LoadShaderProgram("ui_shader_program", UI_VERTEX, UI_FRAGMENT);
    ui_quad = resource_loader.LoadMesh("Meshes/UIQuad.obj");
    default_sprite = resource_loader.LoadTexture("Textures/DefaultTexture.png");

    
    config = YGConfigNew();
    root = YGNodeNewWithConfig(config);

    std::unique_ptr<UIElement> root_element = std::make_unique<UIElement>();
    root_element->node = root;
    elements.insert(std::pair<YGNodeRef, std::unique_ptr<UIElement>>(root, std::move(root_element)));
}

void UI::End() {
    YGNodeFreeRecursive(root);
    YGConfigFree(config);
    elements.clear();
}

bool UI::IsOnUI(const glm::vec2& point) {
    for (const auto& element : elements) {
        if (element.first == root) {
            continue;
        }
        if (element.second->calculated_position.contains_point(point)) {
            return true;
        }
    }
    return false;
}

void UI::RenderUI(entt::registry& registry, Timer& timer) {
    
    YGNodeCalculateLayout(root, screen_size.x, screen_size.y, YGDirectionLTR);

    std::vector<YGNodeRef> all_nodes = CollapseTree(root, glm::vec2(0, 0));

    is_iterating_elements = true;

    for (auto node : all_nodes) {
        auto& element = elements.at(node);
        
        element->Interact(*input_manager);
        element->Draw(screen_size);
    }

    is_iterating_elements = false;
    for (auto node : elements_to_destroy) {
        elements.erase(node);
        YGNodeFree(node);
    }
    elements_to_destroy.clear();
}

void UI::SetRenderSize(glm::tvec2<int> size) {
    screen_size = size;
}

void UI::SetInputManager(InputManager* input_manager) {
    this->input_manager = input_manager;
}

UIElement* UI::GetRoot() {
    return elements.at(root).get();
}

UILabel* UI::AddLabel(UIElement& parent) {
    std::unique_ptr<UILabel> label = std::make_unique<UILabel>(text_render);
    YGNodeRef node = YGNodeNewWithConfig(config);
    label->node = node;
    YGNodeInsertChild(parent.node, node, YGNodeGetChildCount(parent.node));
    UILabel* label_ptr = label.get();
    elements.insert(std::pair<YGNodeRef, std::unique_ptr<UIElement>>(node, std::move(label)));
    return label_ptr;
}

UIImage* UI::AddImage(UIElement& parent) {
    std::unique_ptr<UIImage> image = std::make_unique<UIImage>();
    image->quad = ui_quad;
    image->shader_program = ui_program;
    image->set_sprite(default_sprite);
    YGNodeRef node = YGNodeNewWithConfig(config);
    image->node = node;
    YGNodeInsertChild(parent.node, node, YGNodeGetChildCount(parent.node));
    UIImage* image_ptr = image.get();
    elements.insert(std::pair<YGNodeRef, std::unique_ptr<UIElement>>(node, std::move(image)));
    return image_ptr;
}

void UI::DestroyElement(UIElement& element) {
    std::vector<YGNodeRef> tree = CollapseTree(element.node);
    if (is_iterating_elements) {
        elements_to_destroy.insert(elements_to_destroy.end(), tree.begin(), tree.end());
    } else 	{
        for (auto node : tree) {
            elements.erase(node);
            YGNodeFree(node);
        }
    }
}

std::vector<YGNodeRef> UI::CollapseTree(YGNodeRef node, glm::vec2 position) {
    std::vector<YGNodeRef> nodes;
    glm::vec2 node_position = position + glm::vec2(YGNodeLayoutGetLeft(node), YGNodeLayoutGetTop(node));
    Rect calculated_position;
    calculated_position.left = node_position.x;
    calculated_position.top = node_position.y;
    calculated_position.right = node_position.x + YGNodeLayoutGetWidth(node);
    calculated_position.bottom = node_position.y + YGNodeLayoutGetHeight(node);
    elements.at(node)->calculated_position = calculated_position;
    nodes.push_back(node);
    int n = YGNodeGetChildCount(node);
    for (size_t i = 0; i < n; i++) {
        std::vector<YGNodeRef> child_nodes = CollapseTree(YGNodeGetChild(node, i), node_position);
        nodes.insert(nodes.end(), child_nodes.begin(), child_nodes.end());
    }
    return nodes;
}

std::vector<YGNodeRef> UI::CollapseTree(YGNodeRef node) {
    std::vector<YGNodeRef> nodes;
    nodes.push_back(node);
    int n = YGNodeGetChildCount(node);
    for (size_t i = 0; i < n; i++) {
        std::vector<YGNodeRef> child_nodes = CollapseTree(YGNodeGetChild(node, i));
        nodes.insert(nodes.end(), child_nodes.begin(), child_nodes.end());
    }
    return nodes;
}
