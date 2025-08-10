#include "HelloTriangle.h"

#include "Perfabs.h"

int HelloTriangle::InitOther()
{
	RenderProgram::InitOther();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	//Gen and bind VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Gen and bind VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gen and bind EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Create vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Append source to vertex shader and compile
	glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertexShader);

#pragma region CheckCompileAvaibility
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//Print error log
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			<< infoLog
			<< '\n';
	}
#pragma endregion

	//Create fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Append source to fragment shader and compile
	glShaderSource(fragmentShader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragmentShader);

	shader_program = glCreateProgram();

	//Attach shaders
	glAttachShader(shader_program, vertexShader);
	glAttachShader(shader_program, fragmentShader);
	glLinkProgram(shader_program);

#pragma region CheckProgramAvaibility
	int success_pg;

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success_pg);
	if (!success_pg) {
		char info_log_pg[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log_pg);
		std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n"
			<< info_log_pg
			<< '\n';
	}
#pragma endregion

	//Release shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Apply vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	//Clear VAO VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

void HelloTriangle::LoopRender()
{
	RenderProgram::LoopRender();
	//Activate program
	glUseProgram(shader_program);
	glBindVertexArray(vao);
	//Draw
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	//Unbind
	glBindVertexArray(0);
}

void HelloTriangle::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shader_program);
	RenderProgram::Destroy();
}

int HelloTriangle::Start()
{
	HelloTriangle* base = new HelloTriangle();
	int result = base->Run();

	return result;
}


