#include "UIImage.h"

void UIImage::Draw(const glm::vec2& screen_size) {
	glUseProgram(shader_program->program_id);
	glDisable(GL_BLEND);
	shader_program->SetVec2("screen_size", screen_size);
	shader_program->SetTexture("texture_0", 0, sprite->gl_texture);
	shader_program->SetMat3("object_transform", calculated_position.get_transform());
	quad->Bind();
	quad->Draw();
}

entt::resource_handle<Texture> UIImage::get_sprite() const {
	return sprite;
}

void UIImage::set_sprite(const entt::resource_handle<Texture>& sprite) {
	this->sprite = sprite;
}