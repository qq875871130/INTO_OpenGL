#include "main.h"
#include "practice.h"

int helloTrangle_practice1() {
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
		0.0f,0.0f,0.0f,
		0.5f, 0.8f, 0.0f,
		-0.5f, 0.8f, 0.0f,
		0.0f,0.0f,0.0f,
		0.5f, -0.8f, 0.0f,
		-0.5f, -0.8f, 0.0f,
	};

	unsigned int VBO;
	unsigned int VAO;

	//Create shader program
	unsigned int shaderProgram;

	return helloWindow_test(true, [vertices, vertexShaderSource, fragmentShaderSource,
		&shaderProgram, &VBO, &VAO]()
	                        {
		                        //Gen and bind VAO
		                        glGenVertexArrays(1, &VAO);
		                        glBindVertexArray(VAO);

		                        //Gen and bind VBO
		                        glGenBuffers(1, &VBO);
		                        glBindBuffer(GL_ARRAY_BUFFER, VBO);
		                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
		                        if (!success_pg)
		                        {
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
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//Unbind
			glBindVertexArray(0);
		},
			[&shaderProgram, &VBO, &VAO]() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteProgram(shaderProgram);
		});
}

//int helloTrangle_practice2() {
//
//#pragma region Hard-encode GLSL
//	const char* vertexShaderSource = "#version 460 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//	const char* fragmentShaderSource = "#version 460 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//#pragma endregion
//
//	//Def vertices
//	float vertices[] = {
//		//Trangle
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		0.0f,  0.5f, 0.0f
//	};
//
//	unsigned int VBO;
//	unsigned int VAO;
//
//	//Create shader program
//	unsigned int shaderProgram;
//
//	return helloWindow_test(true, [vertices, vertexShaderSource, fragmentShaderSource, &shaderProgram, &VBO, &VAO]() {
//		//Gen and bind VAO
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//
//		//Gen and bind VBO
//		glGenBuffers(1, &VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		//Create vertex shader
//		unsigned int vertexShader;
//		vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//		//Append source to vertex shader and compile
//		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//		glCompileShader(vertexShader);
//
//#pragma region CheckCompileAvaibility
//		int success;
//		char infoLog[512];
//		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//		//Print error log
//		if (!success)
//		{
//			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
//				<< infoLog
//				<< std::endl;
//		}
//#pragma endregion
//
//		//Create fragment shader
//		unsigned int fragmentShader;
//		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//		//Append source to fragment shader and compile
//		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//		glCompileShader(fragmentShader);
//
//		shaderProgram = glCreateProgram();
//
//		//Attach shaders
//		glAttachShader(shaderProgram, vertexShader);
//		glAttachShader(shaderProgram, fragmentShader);
//		glLinkProgram(shaderProgram);
//
//#pragma region CheckProgramAvaibility
//		int success_pg;
//		char infoLog_pg[512];
//
//		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_pg);
//		if (!success_pg) {
//			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_pg);
//			std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n"
//				<< infoLog_pg
//				<< std::endl;
//		}
//#pragma endregion
//
//		//Release shaders
//		glDeleteShader(vertexShader);
//		glDeleteShader(fragmentShader);
//
//		//Apply vertices
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		//Clear VAO VBO
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//
//		},
//		[&shaderProgram, &VAO, &VBO]() {
//			//Activate program
//			glUseProgram(shaderProgram);
//			/*VAO or VBO*/
//			glBindVertexArray(VAO);
//			//glBindVertexArray(VBO);
//			//Draw
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//			//Unbind
//			glBindVertexArray(0);
//		},
//			[&shaderProgram, &VBO, &VAO]() {
//			glDeleteVertexArrays(1, &VAO);
//			glDeleteBuffers(1, &VBO);
//			glDeleteProgram(shaderProgram);
//		});
//}
//
//int helloTrangle_practice3() {
//
//#pragma region Hard-encode GLSL
//	const char* vertexShaderSource = "#version 460 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//	const char* fragmentShaderSource1 = "#version 460 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//	const char* fragmentShaderSource2 = "#version 460 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//		"}\0";
//#pragma endregion
//
//	//Def vertices
//	float vertices[] = {
//		//Trangle
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		0.0f,  0.5f, 0.0f
//	};
//
//	//Def indices
//	unsigned int indices[] = {
//		0,1,2
//	};
//
//	unsigned int VBO;
//	unsigned int VAO;
//	unsigned int EBO;
//
//	//Create flag switcher 
//	triggerManager* msBtnFlags = new triggerManager(false);
//
//	//Create shader program
//	unsigned int shaderProgram1;
//	unsigned int shaderProgram2;
//	unsigned int* pShaderProgram = &shaderProgram1;
//
//	return helloWindow_test(true, [vertices, indices, vertexShaderSource, &fragmentShaderSource1, &fragmentShaderSource2, &shaderProgram1, &shaderProgram2, &pShaderProgram, &VBO, &VAO, &EBO, &msBtnFlags]() {
//		//Gen and bind VAO
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//
//		//Gen and bind VBO
//		glGenBuffers(1, &VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		//Gen and bind EBO
//		glGenBuffers(1, &EBO);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		//Create vertex shader
//		unsigned int vertexShader;
//		vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//		//Append source to vertex shader and compile
//		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//		glCompileShader(vertexShader);
//
//#pragma region CheckCompileAvaibility
//		int success;
//		char infoLog[512];
//		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//		//Print error log
//		if (!success)
//		{
//			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
//				<< infoLog
//				<< std::endl;
//		}
//#pragma endregion
//
//		//Create fragment shader
//		unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
//		unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
//
//		//Append source to fragment shader and compile
//		glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
//		glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
//
//		glCompileShader(fragmentShader1);
//		glCompileShader(fragmentShader2);
//
//		shaderProgram1 = glCreateProgram();
//		shaderProgram2 = glCreateProgram();
//
//		//Attach shaders
//		glAttachShader(shaderProgram1, vertexShader);
//		glAttachShader(shaderProgram1, fragmentShader1);
//		glLinkProgram(shaderProgram1);
//
//		glAttachShader(shaderProgram2, vertexShader);
//		glAttachShader(shaderProgram2, fragmentShader2);
//		glLinkProgram(shaderProgram2);
//
//#pragma region CheckProgramAvaibility
//		int success_pg;
//		char infoLog_pg[512];
//
//		glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success_pg);
//		if (!success_pg) {
//			glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog_pg);
//			std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n"
//				<< infoLog_pg
//				<< std::endl;
//		}
//#pragma endregion
//
//		//Release shaders
//		glDeleteShader(vertexShader);
//		glDeleteShader(fragmentShader1);
//
//		//Apply vertices
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		//Clear VAO VBO
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//
//		//Bind flag event
//		unsigned int* shaderPrograms[2];
//		int index = 0;
//
//		msBtnFlags->setTrigger(
//			[&shaderProgram1, &shaderProgram2, &pShaderProgram, &shaderPrograms, index, &VAO](bool isUp) mutable {
//				shaderPrograms[0] = &shaderProgram1;
//				shaderPrograms[1] = &shaderProgram2;
//				if (isUp)
//				{
//					int fixInd = (++index) % 2;
//					//Console debug
//					system("cls");
//					std::cout << "Current shader program index = " << fixInd << std::endl;
//					//Pointer move
//					pShaderProgram = shaderPrograms[fixInd];
//				}
//			}
//		);
//
//		},
//		[&pShaderProgram, &VAO, &msBtnFlags]() {
//			//Check flag input
//			processInput_event_mouse(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT, msBtnFlags);
//			//Activate program
//			glUseProgram(*pShaderProgram);
//			glBindVertexArray(VAO);
//			//Draw
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//			//Unbind
//			glBindVertexArray(0);
//		},
//			[&shaderProgram1, &shaderProgram2, &pShaderProgram, &VBO, &VAO, &EBO]() {
//			glDeleteVertexArrays(1, &VAO);
//			glDeleteBuffers(1, &VBO);
//			glDeleteBuffers(1, &EBO);
//			glDeleteProgram(shaderProgram1);
//			glDeleteProgram(shaderProgram2);
//		});
//}