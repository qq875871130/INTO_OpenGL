#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "Utils.h"

namespace CvGlTools {
	void ProcessInputKeyPress(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void ProcessInputKeyUp(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void ProcessInputMouseBtnPress(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void ProcessInputMouseBtnUp(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void ProcessInputEventMouse(GLFWwindow* window, int mouseBtn, TriggerManager* trigger);

	void CallbackFramebufferSize(GLFWwindow* window, int width, int height);
}

