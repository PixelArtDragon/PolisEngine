#pragma once
#include "entt/entt.hpp"
#include "GL/glew.h"
#include "glm/vec2.hpp"
#include "ResourceLoader.h"
#include "FullscreenRenderer.h"


class Rendering {
public:
	void Init(ResourceLoader& resource_loader, const glm::ivec2& screen_size);
	void RenderFrame(entt::registry& registry);
	void SetRenderSize(const glm::ivec2& size);
	glm::vec3 GetWorldPosition(const glm::vec2 screen_position);
private:
	void InitializeRendering();
	void LoadShaders(ResourceLoader& resource_loader);
	void RenderObjects(entt::registry& registry, const glm::mat4& camera_transform);
	void RenderLights(entt::registry& registry, const glm::mat4& camera_transform, const glm::vec3& view_pos);
	void RenderVolumetricLights(entt::registry& registry, const glm::mat4& camera_transform, const glm::vec3& view_pos);
	void RenderDirectionalLights(entt::registry& registry, const glm::vec3& view_pos);
	void PostProcessing();
	glm::tvec2<int> screen_size;
	void CreateGBuffer();
	void BindGBuffer();
	void RecreateGBuffer();
	GLuint g_buffer;
	GLuint g_position, g_normal, g_color;
	GLuint g_depth_buffer;
	void CreateLBuffer();
	void BindLBuffer();
	void RecreateLBuffer();
	GLuint l_buffer;
	GLuint l_diffuse;
	GLuint l_specular;
	void CreateSBuffer();
	void BindSBuffer();
	void RecreateSBuffer();
	//FullscreenRenderer deferred_lighting_renderer;
	FullscreenRenderer directional_lighting;
	FullscreenRenderer post_processing;
	entt::resource_handle<ShaderProgram> volumetric_light_shader;
	entt::resource_handle<ShaderProgram> smoother_shader;
};
