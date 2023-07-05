#pragma once
#include "lib.h"
#include "dataStruct.h"
#include "Tools.h"

class Program
{
private:
	int context_version_min = 4;
	int context_version_max = 4;

	GLFWwindow* window;
	int window_width = 800;
	int window_heigth = 600;
	const char* window_title = "LearnOpenGL";
	GLFWmonitor* window_monitor = NULL;
	GLFWwindow* window_share = NULL;
	GLbitfield window_clear_field = GL_COLOR_BUFFER_BIT;
	vec4<float> window_clear_color = vec4<float>(0.2f, 0.3f, 0.3f, 1.0f);

	GLenum render_polygon_face = GL_FRONT_AND_BACK;
	GLenum render_polygon_mode = GL_FILL;


	bool profile_core = true;

protected:

	virtual int init_profile();
	virtual int init_context();
	virtual int init_other();
	virtual void loop_input();
	virtual void loop_render();
	virtual void loop_apply();
	virtual void destroy();

public:
	Program();
	~Program();
	void set_profile(bool coreMode);
	void set_contextVersion(int min, int max);
	void set_window(int width, int heigth, const char* title);
	void set_window(GLFWmonitor* monitor, GLFWwindow* share);
	void set_field(GLbitfield clearBit);
	void set_field_color(vec4<float> clearColor);
	virtual int run();
};

class RPObject
{
public:
	RPObject();
	virtual void gen(int) = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual void draw() = 0;
	virtual void destory(int) = 0;
protected:
	unsigned int rpo;
};

class RPContext
{
public:
	RPContext(int, RPObject*);

private:
	RPObject* strategy;
};
