#include "Perfabs.h"

#pragma region VBO

VBO::VBO()
{
}

VBO::~VBO()
{
}

void VBO::SetDataBuffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	buffer_size_vertexes = size;
	buffer_vertexes = vertexes;
	draw_type = drawType;
}

void VBO::SetDataDraw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType = GL_TRIANGLES)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VBO::Gen(int num)
{
	glGenBuffers(num, &rpo);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, rpo);
	glBufferData(GL_ARRAY_BUFFER, buffer_size_vertexes, buffer_vertexes, draw_type);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Draw()
{
	Bind();
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	Unbind();
}

void VBO::Destroy(int n)
{
	glDeleteBuffers(n, &rpo);
}



#pragma endregion

#pragma region VAO
VAO::VAO()
{
	vbo = new VBO();
}

VAO::~VAO()
{
	delete(vbo);
}

void VAO::SetDataBuffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	vbo->SetDataBuffer(size, vertexes, drawType);
}

void VAO::SetDataDraw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VAO::Gen(int num)
{
	glGenVertexArrays(num, &rpo);
	vbo->Gen(num);
}

void VAO::Bind()
{
	glBindVertexArray(rpo);
	vbo->Bind();
}

void VAO::Unbind()
{
	glBindVertexArray(0);
	vbo->Unbind();
}

void VAO::Draw()
{
	glBindVertexArray(rpo);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	Unbind();
}

void VAO::Destroy(int n)
{
	glDeleteVertexArrays(n, &rpo);
	vbo->Destroy(n);
}
#pragma endregion

#pragma region EBO
EBO::EBO()
{
	vao = new VAO();
}

EBO::~EBO()
{
	delete(vao);
}

void EBO::SetDataBuffer(GLsizeiptr size_vertexes, const void* vertexes, GLsizeiptr size_indices, const void* indices, GLenum drawType)
{
	indices_buffer_size = size_indices;
	indices_buffer = indices;
	type_draw = drawType;
	vao->SetDataBuffer(size_vertexes, vertexes, drawType);
}

void EBO::SetDataDraw(const void* iOffset, GLsizei iCount, GLenum iType, GLenum primType)
{
	type_prim = primType;
	type_indices = iType;
	vertexes_offset = iOffset;
	vertexes_count = iCount;
}

void EBO::Gen(int num)
{
	glGenBuffers(num, &rpo);
	vao->Gen(num);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rpo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_buffer), indices_buffer, type_draw);
	vao->Bind();
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->Unbind();
}

void EBO::Draw()
{
	vao->Bind();
	glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
	vao->Unbind();
}

void EBO::Destroy(int n)
{
	glDeleteBuffers(n, &rpo);
	vao->Destroy(n);
}
#pragma endregion

