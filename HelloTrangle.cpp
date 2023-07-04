#include "HelloTrangle.h"

int HelloTrangle::init_other()
{
	Program::init_other();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	//Gen and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Gen and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gen and bind EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Append source to vertex shader and compile
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

#pragma region CheckCompileAvaibility
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//Print error log
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			<< infoLog
			<< std::endl;
	}
#pragma endregion

	//Create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Append source to fragment shader and compile
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();

	//Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

#pragma region CheckProgramAvaibility
	int success_pg;
	char infoLog_pg[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_pg);
	if (!success_pg) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_pg);
		std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n"
			<< infoLog_pg
			<< std::endl;
	}
#pragma endregion

	//Release shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Apply vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Clear VAO VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

void HelloTrangle::loop_render()
{
	Program::loop_render();
	//Activate program
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	//Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//Unbind
	glBindVertexArray(0);

}

void HelloTrangle::destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	Program::destroy();
}

int HelloTrangle::start()
{
	HelloTrangle* base = new HelloTrangle();
	int result = base->run();

	delete(base);
	return result;
}


