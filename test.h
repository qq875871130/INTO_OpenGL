#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

int main();

int test_helloTrangle();

int test_helloWindow(std::function<void()> beforeLoop, std::function<void()> onLoop, std::function<void()> afterLoop);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);
