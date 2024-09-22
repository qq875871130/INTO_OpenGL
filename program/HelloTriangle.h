#pragma once
#include "lib.h"
#include "GLBase.h"


class HelloTriangle : Program
{
private:
#pragma region Hard-encode GLSL
	const char* vertex_shader_source = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragment_shader_source = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
#pragma endregion

	unsigned int vbo = 0;
	unsigned int vao = 0;
	unsigned int ebo = 0;

	unsigned int shader_program = 0;

protected:
	int InitOther() override;
	void LoopRender() override;
	void Destroy() override;

public:
	static int Start();
};

