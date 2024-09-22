#include "Tools.h"

void CvGlTools::ProcessInputKeyPress(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
		pressEvent();
}

void CvGlTools::ProcessInputKeyUp(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_RELEASE)
		pressEvent();
}

void CvGlTools::ProcessInputMouseBtnPress(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		pressEvent();
}

void CvGlTools::ProcessInputMouseBtnUp(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_RELEASE)
		pressEvent();
}

void CvGlTools::ProcessInputEventMouse(GLFWwindow* window, int mouseBtn, TriggerManager* trigger)
{
	trigger->ChangeState(glfwGetMouseButton(window, mouseBtn) == GLFW_PRESS);
}

void CvGlTools::CallbackFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
