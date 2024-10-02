#include "main.h"

#include <vector>

#include "practice.h"

int main() {
	std::vector<float> vertices
	{
		/*2 connected triangle (EBO)*/
		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		
		/*2 connected triangle (VAO)*/
		// 0.0f, 0.0f, 0.0f,
		// -0.5f, 0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f,
		// 0.0f, 0.0f, 0.0f,
		// 0.5f, 0.5f, 0.0f,
		// 0.5f, -0.5f, 0.0f,
	};

	std::vector<unsigned int> indices
	{
		0, 1, 2,
		0, 3, 4,
		// 3, 4, 5
	};

	// return HelloTriangle::Start();
	return Practice::HelloTrianglePractice2::Start();
}


