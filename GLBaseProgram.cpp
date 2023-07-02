#include "GLBaseProgram.h"
using namespace cv_gl_tools;

GLBaseProgram::GLBaseProgram()
{
}

GLBaseProgram::~GLBaseProgram()
{
	if (window_monitor != NULL)
	{
		delete(window_monitor);
	}
	if (window_share != NULL)
	{
		delete(window_share);
	}
}

int GLBaseProgram::run()
{
	init_profile();
	if (init_context() == 0)
	{
		init_other();
		while (!glfwWindowShouldClose(window)) {
			loop_input();
			loop_render();
			loop_apply();
		}
		destroy();
		return 0;
	}
	return -1;
}

int  GLBaseProgram::init_profile()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_version_max);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_version_min);

	if (profile_core)
	{
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	return 0;
}

int  GLBaseProgram::init_context()
{
	//Create Window
	window = glfwCreateWindow(window_width, window_heigth, window_title, window_monitor, window_share);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	return 0;
}

int  GLBaseProgram::init_other()
{
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Set Callback
	glfwSetFramebufferSizeCallback(window, cv_gl_tools::callback_framebuffer_size);
	return 0;
}

void  GLBaseProgram::loop_input()
{
	//Check Default Input Event
	processInput_key_press(window, GLFW_KEY_ESCAPE, [this]() {glfwSetWindowShouldClose(window, true); });

}

void  GLBaseProgram::loop_render()
{
	//Render Command
	glPolygonMode(render_polygon_face, render_polygon_mode);
	glClearColor(window_clear_color.x, window_clear_color.y, window_clear_color.z, window_clear_color.w);
	glClear(window_clear_field);
}

void GLBaseProgram::loop_apply()
{
	//Checking and Swap Buffer
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void  GLBaseProgram::destroy()
{
	//Render Terminate
	glfwTerminate();
}
