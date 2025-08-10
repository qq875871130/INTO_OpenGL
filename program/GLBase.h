#pragma once
#include <vector>

#include "Data/DataStruct.h"
#include "CVGl/Tools.h"

class RenderProgram
{
private:
	int context_version_min = 4;
	int context_version_max = 4;

	GLFWwindow* window;
	int window_width = 800;
	int window_height = 600;
	const char* window_title = "LearnOpenGL";
	GLFWmonitor* window_monitor = nullptr;
	GLFWwindow* window_share = nullptr;
	GLbitfield window_clear_field = GL_COLOR_BUFFER_BIT;
	Vec4<float> window_clear_color = Vec4<float>(0.2f, 0.3f, 0.3f, 1.0f);

	GLenum render_polygon_face = GL_FRONT_AND_BACK;
	GLenum render_polygon_mode = GL_FILL;

	bool profile_core = true;

protected:

	virtual int InitProfile();
	virtual int InitContext();
	virtual int InitOther();
	virtual void LoopInput();
	virtual void LoopRender();
	virtual void LoopApply();
	virtual void Destroy();

public:
	RenderProgram();
	virtual ~RenderProgram() = default;
	void SetProfile(bool coreMode);
	void SetContextVersion(int min, int max);
	void SetWindow(int width, int height, const char* title);
	void SetWindow(GLFWmonitor* monitor, GLFWwindow* share);
	void SetField(GLbitfield clearBit);
	void SetFieldColor(Vec4<float> clearColor);
	virtual int Run();
};

class RenderPipelineObject
{
public:
	RenderPipelineObject() = default;
	virtual ~RenderPipelineObject() = default;

	virtual void Gen(int) = 0;
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Draw() = 0;
	virtual void Destroy(int) = 0;
protected:
	std::vector<unsigned int> rpo;
};
