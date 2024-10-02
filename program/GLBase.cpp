#include "GLBase.h"

using namespace CvGlTools;

#pragma region Program

Program::Program()
{
}


int Program::Run()
{
    InitProfile();
    if (InitContext() == 0)
    {
        InitOther();
        while (!glfwWindowShouldClose(window))
        {
            LoopInput();
            LoopRender();
            LoopApply();
        }
        Destroy();
        return 0;
    }
    return -1;
}


#pragma region Configurable
void Program::SetProfile(bool coreMode)
{
    profile_core = coreMode;
}

void Program::SetContextVersion(int min, int max)
{
    context_version_min = min;
    context_version_max = max;
}

void Program::SetWindow(int width, int height, const char* title = "LearnOpenGL")
{
    window_width = width;
    window_height = height;
    window_title = title;
}

void Program::SetWindow(GLFWmonitor* monitor, GLFWwindow* share)
{
    window_monitor = monitor;
    window_share = share;
}

void Program::SetField(GLbitfield clearBit)
{
    window_clear_field = clearBit;
}

void Program::SetFieldColor(Vec4<float> clearColor)
{
    window_clear_color = clearColor;
}
#pragma endregion


#pragma region Virtualizable
int Program::InitProfile()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_version_max);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_version_min);

    if (profile_core)
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    else
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    }
    return 0;
}

int Program::InitContext()
{
    //Create Window
    window = glfwCreateWindow(window_width, window_height, window_title, window_monitor, window_share);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}

int Program::InitOther()
{
    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    //Set Callback
    glfwSetFramebufferSizeCallback(window, CvGlTools::CallbackFramebufferSize);
    return 0;
}

void Program::LoopInput()
{
    //Check Default Input Event
    ProcessInputKeyPress(window, GLFW_KEY_ESCAPE, [this]() { glfwSetWindowShouldClose(window, true); });
}

void Program::LoopRender()
{
    //Render Command
    glPolygonMode(render_polygon_face, render_polygon_mode);
    glClearColor(window_clear_color.X, window_clear_color.Y, window_clear_color.Z, window_clear_color.W);
    glClear(window_clear_field);
}

void Program::LoopApply()
{
    //Checking and Swap Buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Program::Destroy()
{
    //Render Terminate
    glfwTerminate();
}

#pragma endregion


#pragma endregion
