#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

class Practice
{
    class HelloTrianglePractice1 : HelloTriangle
    {
    protected:
        int InitOther() override;
        void LoopRender() override;
        void Destroy() override;
    };
};

int helloTrangle_practice1();

int helloTrangle_practice2();

int helloTrangle_practice3();
