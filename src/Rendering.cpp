#include "Rendering.h"

#include "Transform.h"
#include "Renderable.h"
#include "AreaLight.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "Debug.h"
#include "GLDebug.h"

void Rendering::Init(ResourceLoader& resource_loader, const glm::ivec2& screen_size) {
	this->screen_size = screen_size;
	InitializeRendering();
	CreateGBuffer();
	CreateLBuffer();
	LoadShaders(resource_loader);
}

void Rendering::SetRenderSize(const glm::ivec2& size) {
	screen_size = size;
	RecreateGBuffer();
	RecreateLBuffer();
}

void Rendering::RenderFrame(entt::registry& registry) {
	BindGBuffer();

	//Calculate camera position
	auto camera_view = registry.view<Camera>();
	glm::mat4 camera_transform;
	glm::vec3 view_pos;
	if (camera_view.empty()) {
		Debug::Log(LogSeverity::Warning, "No entities with cameras found");
		camera_transform = glm::mat4();
		view_pos = glm::vec3(0.0);
	} else {
		auto camera = registry.get<Camera>(camera_view.front());
		camera_transform = camera.projection * camera.view;
		view_pos = registry.get<Transform>(camera_view.front()).position;
	}

	RenderObjects(registry, camera_transform);
	BindLBuffer();
	RenderLights(registry, camera_transform, view_pos);
	PostProcessing();
}

glm::vec3 Rendering::GetWorldPosition(const glm::vec2 screen_position) {
	glm::vec2 normalized_position = glm::vec2(screen_position.x, screen_size.y - screen_position.y);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, g_buffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	float pixel[4];
	glReadPixels(normalized_position.x, normalized_position.y, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	return glm::vec3(pixel[0], pixel[1], pixel[2]);
}

void Rendering::InitializeRendering() {
	glewExperimental = true;
	glewInit();
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebug::glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	FullscreenRenderer::Init();
}

void Rendering::CreateGBuffer() {
	glGenFramebuffers(1, &g_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, g_buffer);

	glGenTextures(1, &g_position);
	glGenTextures(1, &g_normal);
	glGenTextures(1, &g_color);

	glBindTexture(GL_TEXTURE_2D, g_position);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16F, screen_size.x, screen_size.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_position, 0);

	glBindTexture(GL_TEXTURE_2D, g_normal);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16F, screen_size.x, screen_size.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, g_normal, 0);

	glBindTexture(GL_TEXTURE_2D, g_color);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, screen_size.x, screen_size.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, g_color, 0);

	GLuint attachements[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachements);

	glGenRenderbuffers(1, &g_depth_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, g_depth_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screen_size.x, screen_size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_depth_buffer);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		Debug::Log(LogSeverity::FatalError, "GBuffer not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Rendering::RecreateGBuffer() {
	glDeleteBuffers(1, &g_position);
	glDeleteBuffers(1, &g_normal);
	glDeleteBuffers(1, &g_color);
	glDeleteRenderbuffers(1, &g_depth_buffer);
	glDeleteFramebuffers(1, &g_buffer);
	CreateGBuffer();
}

void Rendering::CreateLBuffer() {
	glGenFramebuffers(1, &l_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, l_buffer);
	glGenTextures(1, &l_diffuse);
	glGenTextures(1, &l_specular);

	glBindTexture(GL_TEXTURE_2D, l_diffuse);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, screen_size.x, screen_size.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, l_diffuse, 0);

	glBindTexture(GL_TEXTURE_2D, l_specular);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, screen_size.x, screen_size.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, l_specular, 0);

	GLuint attachements[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachements);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		Debug::Log(LogSeverity::FatalError, "LBuffer not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Rendering::RecreateLBuffer() {
	glDeleteBuffers(1, &l_diffuse);
	glDeleteBuffers(1, &l_specular);
	glDeleteFramebuffers(1, &l_buffer);
	CreateLBuffer();
}

void Rendering::LoadShaders(ResourceLoader& resource_loader) {
	directional_lighting.shader_program = resource_loader.LoadShaderProgram("directional_lighting", "Shaders/fullscreen_vertex.glsl", "Shaders/directional_fragment.glsl");
	volumetric_light_shader = resource_loader.LoadShaderProgram("volumetric_lighting", "Shaders/forward_vertex_only_position.glsl", "Shaders/area_light_fragment.glsl");
	post_processing.shader_program = resource_loader.LoadShaderProgram("post_processing", "Shaders/fullscreen_vertex.glsl", "Shaders/post_processing.glsl");
}

void Rendering::BindGBuffer() {
	glViewport(0, 0, screen_size.x, screen_size.y);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_buffer);
	glDepthMask(true);
	glClearDepth(1.0f);
	glClearColor(0, 0, 0, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Rendering::RenderObjects(entt::registry& registry, const glm::mat4& camera_transform) {
	auto view = registry.view<Renderable, Transform>();
	for (auto entity : view) {
		auto& renderable = view.get<Renderable>(entity);
		auto& transform = view.get<Transform>(entity);
		glUseProgram(renderable.shader_program->program_id);
		renderable.shader_program->SetMat4("camera_transform", camera_transform);
		renderable.shader_program->SetMat4("object_transform", transform.matrix());
		int i = 0;
		for (; i < renderable.textures.size(); i++) {
			renderable.shader_program->SetTexture("texture_" + std::to_string(i), i, renderable.textures[i]);
		}
		for (; i < 10; i++) {
			renderable.shader_program->SetTexture("texture_" + std::to_string(i), i, 0);
		}
		renderable.mesh->Bind();
		renderable.mesh->Draw();
	}
}

void Rendering::BindLBuffer() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, l_buffer);

	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0.0, 0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Rendering::RenderLights(entt::registry& registry, const glm::mat4& camera_transform, const glm::vec3& view_pos) {
	RenderDirectionalLights(registry, view_pos);
	RenderVolumetricLights(registry, camera_transform, view_pos);
}

void Rendering::RenderDirectionalLights(entt::registry& registry, const glm::vec3& view_pos) {
	glCullFace(GL_BACK);
	auto directional_lights = registry.view<DirectionalLight>();
	directional_lighting.Bind();
	directional_lighting.shader_program->SetVec3("view_pos", view_pos);
	directional_lighting.shader_program->SetVec2("window_size", screen_size);
	directional_lighting.shader_program->SetTexture("g_position", 0, g_position);
	directional_lighting.shader_program->SetTexture("g_normal", 1, g_normal);
	directional_lighting.shader_program->SetTexture("g_color", 2, g_color);
	for (auto entity : directional_lights) {
		auto& light = registry.get<DirectionalLight>(entity);
		directional_lighting.shader_program->SetVec3("light_direction", light.direction);
		directional_lighting.shader_program->SetVec3("light_color", light.color);
		directional_lighting.shader_program->SetFloat("light_intensity", light.intensity);
		directional_lighting.Render();
	}
}

void Rendering::RenderVolumetricLights(entt::registry& registry, const glm::mat4& camera_transform, const glm::vec3& view_pos) {
	auto area_lights = registry.view<AreaLight, Transform>();
	glUseProgram(volumetric_light_shader->program_id);
	volumetric_light_shader->SetMat4("camera_transform", camera_transform);
	volumetric_light_shader->SetVec3("view_pos", view_pos);
	volumetric_light_shader->SetVec2("window_size", screen_size);
	volumetric_light_shader->SetTexture("g_position", 0, g_position);
	volumetric_light_shader->SetTexture("g_normal", 1, g_normal);
	volumetric_light_shader->SetTexture("g_color", 2, g_color);
	for (auto entity : area_lights) {
		auto& light = registry.get<AreaLight>(entity);
		auto& transform = registry.get<Transform>(entity);
		volumetric_light_shader->SetMat4("object_transform", transform.matrix());
		volumetric_light_shader->SetVec3("light_color", light.color);
		volumetric_light_shader->SetVec3("light_position", transform.position);
		volumetric_light_shader->SetFloat("light_intensity", light.intensity);
		light.shape->Bind();
		glDrawElements(GL_TRIANGLES, light.shape->triangles.size(), GL_UNSIGNED_INT, (void*)0);
	}
}

void Rendering::PostProcessing() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //draw to the output buffer
	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0.0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	post_processing.Bind();

	post_processing.shader_program->SetTexture("g_position", 0, g_position);
	post_processing.shader_program->SetTexture("g_normal", 1, g_position);
	post_processing.shader_program->SetTexture("g_color", 2, g_color);
	post_processing.shader_program->SetTexture("l_diffuse", 3, l_diffuse);
	post_processing.shader_program->SetTexture("l_specular", 4, l_specular);

	post_processing.Render();
}