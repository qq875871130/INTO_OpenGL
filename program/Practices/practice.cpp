#include "main.h"
#include "practice.h"

#include <windows.h>

int Practice::HelloTrianglePractice1::InitOther()
{
	RenderProgram::InitOther();

	//Init rpo
	Context->GetRpo()->Gen(1);
	Context->SetDataBuffer(static_cast<long long>(sizeof(float) * Vertices.size()),
	                       Vertices.data(),
	                       static_cast<long long>(sizeof(unsigned int) * Indices.size()),
	                       Indices.data(),
	                       GL_STATIC_DRAW);
	Context->GetRpo()->Bind();

	//Config shader
	Context->InitShaderProgram(vertexShaderSource, fragmentShaderSource);
	
	RpoContext::ParseVertexes();
	
	//Unbind rpo
	Context->GetRpo()->Unbind();
	
	return 0;
}

void Practice::HelloTrianglePractice1::LoopRender()
{
	RenderProgram::LoopRender();

	//Active program
	Context->UseShaderProgram();
	
	//Draw
	Context->SetDataDraw(0, DrawCount, Indices_offset.data(), GL_UNSIGNED_INT, PrimType);
	Context->GetRpo()->Draw();
}

void Practice::HelloTrianglePractice1::Destroy()
{
	Context->GetRpo()->Destroy(1);
	Context->ReleaseShaderProgram();
	
	RenderProgram::Destroy();
}

int Practice::HelloTrianglePractice2::InitOther()
{
	RenderProgram::InitOther();

	//Init
	Context->GetRpo()->Gen(2);
	Context->InitShaderProgram(vertexShaderSource, fragmentShaderSource);

	//Parse
	Context->BindByIndex(0, static_cast<long long>(sizeof(float) * Vertices1.size()), Vertices1.data(),
	                     0, nullptr, GL_STATIC_DRAW);
	RpoContext::ParseVertexes();
	
	Context->BindByIndex(1, static_cast<long long>(sizeof(float) * Vertices2.size()), Vertices2.data(),
	                     0, nullptr, GL_STATIC_DRAW);
	RpoContext::ParseVertexes(0, 3, GL_FLOAT, GL_FALSE, 0);

	//Unbind
	Context->GetRpo()->Unbind();

	return 0;
}

void Practice::HelloTrianglePractice2::LoopRender()
{
	RenderProgram::LoopRender();

	Context->UseShaderProgram();
	Context->SetDataDraw(0, 3, nullptr, GL_UNSIGNED_INT, PrimType);
	Context->GetRpo()->Draw();
}

void Practice::HelloTrianglePractice2::Destroy()
{
	Context->GetRpo()->Destroy(2);
	Context->ReleaseShaderProgram();

	RenderProgram::Destroy();
}

int Practice::HelloTrianglePractice3::InitOther()
{
	RenderProgram::InitOther();

	auto vexShader = glCreateShader(GL_VERTEX_SHADER);
	auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Init
	Context->GetRpo()->Gen(1);
	shaderProgram1 = RpoContext::InitShaderProgram({vexShader, fragShader}, {vertexShaderSource, fragmentShaderSource1});
	shaderProgram2 = RpoContext::InitShaderProgram({vexShader, fragShader}, {vertexShaderSource, fragmentShaderSource2});

	//Parse
	Context->SetDataBuffer(static_cast<long long>(sizeof(float) * Vertices.size()),
						   Vertices.data(),
						   static_cast<long long>(sizeof(unsigned int) * Indices.size()),
						   Indices.data(),
						   GL_STATIC_DRAW);
	Context->GetRpo()->Bind();
	RpoContext::ParseVertexes();

	//Unbind
	Context->GetRpo()->Unbind();
	return 0;
}

void Practice::HelloTrianglePractice3::LoopRender()
{
	RenderProgram::LoopRender();

	Context->GetRpo()->Bind();
	
	RpoContext::UseShaderProgram(shaderProgram1);
	Context->SetDataDraw(0, 3, nullptr, GL_UNSIGNED_INT, PrimType);
	Context->GetRpo()->Draw();
	
	RpoContext::UseShaderProgram(shaderProgram2);
	Context->SetDataDraw(0, 3, reinterpret_cast<void*>(3 * sizeof(unsigned int)), GL_UNSIGNED_INT, PrimType);
	Context->GetRpo()->Draw();
	
	Context->GetRpo()->Unbind();
}

void Practice::HelloTrianglePractice3::Destroy()
{
	Context->GetRpo()->Destroy(1);
	RpoContext::ReleaseShaderProgram(shaderProgram1);
	RpoContext::ReleaseShaderProgram(shaderProgram2);
	
	RenderProgram::Destroy();
}