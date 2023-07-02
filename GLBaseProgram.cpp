#include "GLBaseProgram.h"


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
<<<<<<< HEAD
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
<<<<<<< HEAD
}


#pragma region Configurable
void GLBaseProgram::set_profile(bool coreMode)
{
	profile_core = coreMode;
}

void GLBaseProgram::set_contextVersion(int min, int max)
{
	context_version_min = min;
	context_version_max = max;
}

void GLBaseProgram::set_window(int width, int heigth, const char* title = "LearnOpenGL")
{
	window_width = width;
	window_heigth = heigth;
	window_title = title;
=======
>>>>>>> e49752da7bc786b0cb381c50a45ff614fcbe40b9
=======
	glfwInit();
>>>>>>> parent of e49752d (Initially complete window and trangle glProgram base class test)
}

void GLBaseProgram::set_window(GLFWmonitor* monitor, GLFWwindow* share)
{
	window_monitor = monitor;
	window_share = share;
}

void GLBaseProgram::set_field(GLbitfield clearBit)
{
	window_clear_field = clearBit;
}

void GLBaseProgram::set_field_color(vec4<float> clearColor)
{
	window_clear_color = clearColor;
}
#pragma endregion


#pragma region Virtualizable
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

void  GLBaseProgram::destroy()
{
	//Render Terminate
	glfwTerminate();
}

#pragma endregion

