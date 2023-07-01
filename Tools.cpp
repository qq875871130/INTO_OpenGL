#include "Tools.h"
void cv_gl_tools::processInput_key_press(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
		pressEvent();
}

void cv_gl_tools::processInput_key_up(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_RELEASE)
		pressEvent();
}

void cv_gl_tools::processInput_mouseBtn_press(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		pressEvent();
}

void cv_gl_tools::processInput_mouseBtn_up(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_RELEASE)
		pressEvent();
}

void cv_gl_tools::processInput_event_mouse(GLFWwindow* window, int mouseBtn, TriggerManager* trigger)
{
	trigger->changeState(glfwGetMouseButton(window, mouseBtn) == GLFW_PRESS);
}

void cv_gl_tools::callback_framebuffer_size(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
