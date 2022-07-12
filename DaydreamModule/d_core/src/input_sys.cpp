#include "input_sys.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool InputSys::isKeyPressed(void* window, KeyCode k) {
	auto state = glfwGetKey(static_cast<GLFWwindow*>(window), static_cast<int32_t>(k));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool InputSys::IsMouseButtonPressed(void* window, MouseCode button) {
	auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), static_cast<int32_t>(button));
	return state == GLFW_PRESS;
}

std::pair<float, float> InputSys::GetMousePosition(void* window) {
	double xpos, ypos;
	glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xpos, &ypos);
	return { float(xpos),float(ypos) };
}

float InputSys::GetMouseX(void* window) {
	auto tmp = GetMousePosition(static_cast<GLFWwindow*>(window));
	return (float)tmp.first;
}

float InputSys::GetMouseY(void* window) {
	auto tmp = GetMousePosition(static_cast<GLFWwindow*>(window));
	return (float)tmp.second;
}

void InputSys::SetCursorHidden(void* window, const bool enable) {
	if (enable) {
		glfwSetInputMode(static_cast<GLFWwindow*>(window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(static_cast<GLFWwindow*>(window), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
