#pragma once

#include "UIElement.h"
#include "ResourceLoader.h"

class UIImage : public UIElement {
public:
	virtual void Draw(const glm::vec2& screen_size) override;
	entt::resource_handle<Texture> get_sprite() const;
	void set_sprite(const entt::resource_handle<Texture>& sprite);
	entt::resource_handle<ShaderProgram> shader_program;
	entt::resource_handle<Mesh> quad;
private:
	entt::resource_handle<Texture> sprite;
};

