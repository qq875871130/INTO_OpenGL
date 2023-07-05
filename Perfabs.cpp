#include "Perfabs.h"

#pragma region VBO

VBO::VBO()
{
}

VBO::~VBO()
{
}

void VBO::set_data_buffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	buffer_size_vertexes = size;
	buffer_vertexes = vertexes;
	draw_type = drawType;
}

void VBO::set_data_draw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType = GL_TRIANGLES)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VBO::gen(int num)
{
	glGenBuffers(num, &rpo);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, rpo);
	glBufferData(GL_ARRAY_BUFFER, buffer_size_vertexes, buffer_vertexes, draw_type);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::draw()
{
	bind();
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	unbind();
}

void VBO::destory(int n)
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

void VAO::set_data_buffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	vbo->set_data_buffer(size, vertexes, drawType);
}

void VAO::set_data_draw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType = GL_TRIANGLES)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VAO::gen(int num)
{
	glGenVertexArrays(num, &rpo);
	vbo->gen(num);
}

void VAO::bind()
{
	glBindVertexArray(rpo);
	vbo->bind();
}

void VAO::unbind()
{
	glBindVertexArray(0);
	vbo->unbind();
}

void VAO::draw()
{
	glBindVertexArray(rpo);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	unbind();
}

void VAO::destory(int n)
{
	glDeleteVertexArrays(n, &rpo);
	vbo->destory(n);
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

void EBO::set_data_buffer(GLsizeiptr size_vertexes, const void* vertexes, GLsizeiptr size_indices, const void* indices, GLenum drawType = GL_STATIC_DRAW)
{
	indices_buffer_size = size_indices;
	indices_buffer = indices;
	type_draw = drawType;
	vao->set_data_buffer(size_vertexes, vertexes, drawType);
}

void EBO::set_data_draw(const void* iOffset, GLsizei iCount, GLenum iType = GL_UNSIGNED_INT, GLenum primType = GL_TRIANGLES)
{
	type_prim = primType;
	type_indices = iType;
	vertexes_offset = iOffset;
	vertexes_count = iCount;
}

void EBO::gen(int num)
{
	glGenBuffers(num, &rpo);
	vao->gen(num);
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rpo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_buffer), indices_buffer, type_draw);
	vao->bind();
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->unbind();
}

void EBO::draw()
{
	vao->bind();
	glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
	vao->unbind();
}

void EBO::destory(int n)
{
	glDeleteBuffers(n, &rpo);
	vao->destory(n);
}
#pragma endregion

