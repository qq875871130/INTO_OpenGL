#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "dataStruct.h"
#include "TriggerManager.h"
#include "GLBaseProgram.h"

namespace cv_gl_tools {
	void processInput_key_press(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void processInput_key_up(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void processInput_mouseBtn_press(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void processInput_mouseBtn_up(GLFWwindow* window, int key, std::function<void()> pressEvent);
	void processInput_event_mouse(GLFWwindow* window, int mouseBtn, TriggerManager* trigger);

	void callback_framebuffer_size(GLFWwindow* window, int width, int height);
}

