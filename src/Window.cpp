#include "Window.h"

Window::Window() {
	size_ = glm::tvec2<int>(1024, 768);
	window_ = NULL;
}

Window::~Window() {
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Window::SetInputManager(InputManager* input_manager) {
	this->input_manager_ = input_manager;
}

void Window::SetRendering(Rendering* rendering) {
	this->rendering_ = rendering;
}

void Window::Init() {
	glfwInit();

	glfwSetErrorCallback(ErrorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // NDEBUG

	window_ = glfwCreateWindow(size_.x, size_.y, name_.c_str(), NULL, NULL);

	if (!window_) {
		Debug::Log(LogSeverity::FatalError, "Window creation failed");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window_);
	glfwSetWindowUserPointer(window_, (void*)this);
	glfwSetKeyCallback(window_, KeypressCallback);
	glfwSetCursorPosCallback(window_, MouseMovedCallback);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window_);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::Close() {}

bool Window::is_open() {
	return !glfwWindowShouldClose(window_);
}

void Window::SetTitle(const std::string& new_title)
{
	glfwSetWindowTitle(window_, new_title.c_str());
	name_ = new_title;
}

std::string Window::GetTitle() const
{
	return name_;
}

glm::tvec2<int> Window::size() const {
	return size_;
}

void Window::KeypressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Window* window_obj = (Window*)glfwGetWindowUserPointer(window);
	switch (action) 	{
	case GLFW_PRESS: window_obj->input_manager_->KeyPressed((KeyCode)key); break;
	case GLFW_RELEASE: window_obj->input_manager_->KeyReleased((KeyCode)key); break;
	default:
		break;
	}
}

void Window::WindowResizedCallback(GLFWwindow* window, int width, int height) {
	Window* window_obj = (Window*)glfwGetWindowUserPointer(window);
	window_obj->size_ = glm::tvec2<int>(width, height);
	window_obj->rendering_->SetRenderSize(window_obj->size_);
}

void Window::MouseMovedCallback(GLFWwindow* window, double x_pos, double y_pos) {
	Window* window_obj = (Window*)glfwGetWindowUserPointer(window);
	window_obj->input_manager_->MouseMoved(glm::tvec2<int>(x_pos, y_pos));
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Window* window_obj = (Window*)glfwGetWindowUserPointer(window);
	switch (action) {
	case GLFW_PRESS: window_obj->input_manager_->MousebuttonPressed((Mousebutton)button); break;
	case GLFW_RELEASE: window_obj->input_manager_->MousebuttonReleased((Mousebutton)button); break;
	default:
		break;
	}
}

void Window::ErrorCallback(int error, const char* message) {

}