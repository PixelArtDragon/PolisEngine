#include "Rendering.h"

#include "GL/glew.h"
#include "Transform.h"
#include "Renderable.h"
#include "Camera.h"
#include "Debug.h"
#include "GLDebug.h"
#include "AreaLight.h"
#include "DirectionalLight.h"

#ifndef NDEBUG
#define DEFERRED_VERTEX "Shaders/deferred_vertex.glsl"
#define DEFERRED_FRAGMENT "Shaders/deferred_fragment.glsl"
#define LIGHT_VERTEX "Shaders/forward_vertex_only_position.glsl"
#define LIGHT_FRAGMENT "Shaders/area_light_fragment.glsl"
#define DIRECTIONAL_FRAGMENT "Shaders/directional_fragment.glsl"
#endif // DEBUG


void Rendering::Init(ResourceLoader& resource_loader, glm::tvec2<int> screen_size) {
	this->screen_size = screen_size;
	glewExperimental = true;
	glewInit();
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebug::glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	FullscreenRenderer::Init();
	deferred_lighting_renderer.shader_program = resource_loader.LoadShaderProgram("deferred_shader", DEFERRED_VERTEX, DEFERRED_FRAGMENT);
	glUseProgram(deferred_lighting_renderer.shader_program->program_id);
	deferred_lighting_renderer.shader_program->SetInt("g_position", 0);
	deferred_lighting_renderer.shader_program->SetInt("g_normal", 1);
	deferred_lighting_renderer.shader_program->SetInt("g_color", 2);
	glUseProgram(0);
	deferred_directional_lighting.shader_program = resource_loader.LoadShaderProgram("deferred_directional_lighting", DEFERRED_VERTEX, DIRECTIONAL_FRAGMENT);
	CreateGBuffer();

	volumetric_light_shader = resource_loader.LoadShaderProgram("volumetric_lighting", LIGHT_VERTEX, LIGHT_FRAGMENT);
}

void Rendering::RenderFrame(entt::registry& registry) {
	//Rendering pass
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

	auto view = registry.view<Renderable, Transform>();
	for (auto entity : view) {
		auto & renderable = view.get<Renderable>(entity);
		auto& transform = view.get<Transform>(entity);
		glUseProgram(renderable.shader_program->program_id);
		renderable.shader_program->SetMat4("camera_transform", camera_transform);
		renderable.shader_program->SetMat4("object_transform", transform.matrix());
		if (renderable.textures.size() > 0) {
			renderable.shader_program->SetTexture("texture_0", 0, renderable.textures[0]);
		} else {
			renderable.shader_program->SetTexture("texture_0", 0, 0);
		}
		renderable.mesh->Bind();
		renderable.mesh->Draw();
	}
	//Lighting pass
	BindGBuffer();
	deferred_lighting_renderer.Render();

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
	glCullFace(GL_BACK);
	auto directional_lights = registry.view<DirectionalLight>();
	deferred_directional_lighting.Bind();
	deferred_directional_lighting.shader_program->SetVec3("view_pos", view_pos);
	deferred_directional_lighting.shader_program->SetVec2("window_size", screen_size);
	deferred_directional_lighting.shader_program->SetTexture("g_position", 0, g_position);
	deferred_directional_lighting.shader_program->SetTexture("g_normal", 1, g_normal);
	deferred_directional_lighting.shader_program->SetTexture("g_color", 2, g_color);
	for (auto entity : directional_lights) {
		auto& light = registry.get<DirectionalLight>(entity);
		deferred_directional_lighting.shader_program->SetVec3("light_direction", light.direction);
		deferred_directional_lighting.shader_program->SetVec3("light_color", light.color);
		deferred_directional_lighting.shader_program->SetFloat("light_intensity", light.intensity);
		deferred_directional_lighting.Render();
	}
	glBindVertexArray(0);
}

void Rendering::SetRenderSize(glm::tvec2<int> size) {
	screen_size = size;
	RecreateGBuffer();
}

glm::vec3 Rendering::GetWorldPosition(glm::vec2 screen_position) {
	glm::vec2 normalized_position = glm::vec2(screen_position.x, screen_size.y - screen_position.y);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, g_buffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	float pixel[4];
	glReadPixels(normalized_position.x, normalized_position.y, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	return glm::vec3(pixel[0], pixel[1], pixel[2]);
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
		Debug::Log(LogSeverity::FatalError, "Framebuffer not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Rendering::BindGBuffer() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0.0, 0, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	deferred_lighting_renderer.Bind();
	deferred_lighting_renderer.shader_program->SetTexture("g_position", 0, g_position);
	deferred_lighting_renderer.shader_program->SetTexture("g_normal", 1, g_normal);
	deferred_lighting_renderer.shader_program->SetTexture("g_color", 2, g_color);
}

void Rendering::RecreateGBuffer() {
	glDeleteBuffers(1, &g_position);
	glDeleteBuffers(1, &g_normal);
	glDeleteBuffers(1, &g_color);
	glDeleteRenderbuffers(1, &g_depth_buffer);
	glDeleteFramebuffers(1, &g_buffer);
	CreateGBuffer();
}
