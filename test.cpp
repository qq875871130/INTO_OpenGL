#include "test.h"

int main() {
	return helloTrangle_practice3();
}

int helloTrangle_test() {

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

	//Def vertices
	float vertices[] = {
		//Trangle
		//-0.5f, -0.5f, 0.0f,
		//0.5f, -0.5f, 0.0f,
		//0.0f,  0.5f, 0.0f

		//Rectangle
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	//Def indices
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	//Create shader program
	unsigned int shaderProgram;

	return helloWindow_test(true, [vertices, indices, vertexShaderSource, fragmentShaderSource, &shaderProgram, &VBO, &VAO, &EBO]() {
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

		},
		[&shaderProgram, &VAO]() {
			//Activate program
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			//Draw
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//Unbind
			glBindVertexArray(0);
		},
			[&shaderProgram, &VBO, &VAO, &EBO]() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteProgram(shaderProgram);
		});
}

int helloWindow_test(bool isCore, std::function<void()> beforeLoop, std::function<void()> onLoop, std::function<void()> afterLoop) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	if (isCore)
	{
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	//Create Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Set Callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	beforeLoop();

	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Check Default Input Event
		processInput_key_press(window, GLFW_KEY_ESCAPE, [&window]() {glfwSetWindowShouldClose(window, true); });

		//Render Command
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render Operation
		onLoop();

		//Checking and Swap Buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	afterLoop();

	//Render Terminate
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput_key_press(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_PRESS)
		pressEvent();
}

void processInput_key_up(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetKey(window, key) == GLFW_RELEASE)
		pressEvent();
}

void processInput_mouseBtn_press(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_PRESS)
		pressEvent();
}

void processInput_mouseBtn_up(GLFWwindow* window, int key, std::function<void()> pressEvent)
{
	if (glfwGetMouseButton(window, key) == GLFW_RELEASE)
		pressEvent();
}

void processInput_event_mouse(GLFWwindow* window, int mouseBtn, triggerManager* trigger)
{
	trigger->changeState(glfwGetMouseButton(window, mouseBtn) == GLFW_PRESS);
}

