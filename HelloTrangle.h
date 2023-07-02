#pragma once
#include "Tools.h"
#define GL_VBO 0
#define GL_VAO 1
#define GL_EBO 2


class HelloTrangle :GLBaseProgram
{
private:
#pragma region Hard-encode GLSL
	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
#pragma endregion

	//Render data
	float* vertices;
	unsigned int* indices;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	unsigned int shaderProgram;

protected:
	int init_other() override;
	void loop_render() override;
	void destroy() override;

public:
	static int start();
};

