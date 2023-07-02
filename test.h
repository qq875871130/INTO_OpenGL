#pragma once
<<<<<<< HEAD
#include "HelloWindow.h"
#include "HelloTrangle.h"
=======
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "practice.h"
<<<<<<< HEAD
#include "Tools.h"
>>>>>>> e49752da7bc786b0cb381c50a45ff614fcbe40b9
=======
#include "triggerManager.h"
>>>>>>> parent of e49752d (Initially complete window and trangle glProgram base class test)

int main();

int helloTrangle_test();

int helloWindow_test(bool isCore, std::function<void()> beforeLoop, std::function<void()> onLoop, std::function<void()> afterLoop);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput_key_press(GLFWwindow* window, int key, std::function<void()> pressEvent);

void processInput_key_up(GLFWwindow* window, int key, std::function<void()> pressEvent);

void processInput_mouseBtn_press(GLFWwindow* window, int key, std::function<void()> pressEvent);

void processInput_mouseBtn_up(GLFWwindow* window, int key, std::function<void()> pressEvent);

void processInput_event_mouse(GLFWwindow* window, int mouseBtn, triggerManager* trigger);
