#pragma once
#include <memory>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>

#include "InputManager.h"
#include "Rendering.h"

class Window {
public:
	Window();
	~Window();
	void SetInputManager(InputManager* input_manager);
	void SetRendering(Rendering* rendering);
	void Init();
	void SwapBuffers();
	void PollEvents();
	void Close();

	void SetTitle(const std::string& new_title);
	std::string GetTitle() const;

	bool is_open();
	glm::tvec2<int> size() const;

private:
	static void KeypressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void WindowResizedCallback(GLFWwindow* window, int width, int height);
	static void MouseMovedCallback(GLFWwindow* window, double x_pos, double y_pos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ErrorCallback(int error, const char* message);
	InputManager* input_manager_;
	Rendering* rendering_;
	glm::tvec2<int> size_;
	std::string name_;
	GLFWwindow* window_;
};