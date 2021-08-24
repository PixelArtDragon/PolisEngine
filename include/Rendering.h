#pragma once
#include "entt/entt.hpp"
#include "GL/glew.h"
#include "glm/vec2.hpp"
#include "ResourceLoader.h"
#include "FullscreenRenderer.h"


class Rendering {
public:
	void Init(ResourceLoader& resource_loader, glm::tvec2<int> screen_size);
	void RenderFrame(entt::registry& registry);
	void SetRenderSize(glm::tvec2<int> size);
	glm::vec3 GetWorldPosition(glm::vec2 screen_position);
private:
	glm::tvec2<int> screen_size;
	void CreateGBuffer();
	void BindGBuffer();
	void RecreateGBuffer();
	GLuint g_buffer;
	GLuint g_position, g_normal, g_color;
	GLuint g_depth_buffer;
	FullscreenRenderer deferred_lighting_renderer;
	FullscreenRenderer deferred_directional_lighting;
	entt::resource_handle<ShaderProgram> volumetric_light_shader;
};
