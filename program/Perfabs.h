#pragma once
#include "GLBase.h"

class VBO : RPObject
{
public:
	VBO();
	~VBO() override;
	void SetDataBuffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void SetDataDraw(GLint, GLsizei, GLenum);
	void Gen(int) override;
	void Bind() override;
	void Unbind() override;
	void Draw() override;
	void Destroy(int) override;
	void Get(unsigned int*& vboId) { vboId = &rpo; }
private:
	GLsizeiptr buffer_size_vertexes = 0;
	const void* buffer_vertexes;
	GLenum draw_type = GL_STATIC_DRAW;
	GLenum prim_type = GL_TRIANGLES;
	GLint vertexes_index_first = 0;
	GLsizei vertexes_count = 3;
};

class VAO : RPObject
{
public:
	VAO();
	~VAO() override;
	void SetDataBuffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void SetDataDraw(GLint, GLsizei, GLenum = GL_TRIANGLES);
	void Gen(int) override;
	void Bind() override;
	void Unbind() override;
	void Draw() override;
	void Destroy(int) override;

	void Get(unsigned int*& vaoId, unsigned int*& vboId)
	{
		vaoId = &rpo;
		vbo->Get(vboId);
	}
private:
	VBO* vbo;
	GLenum prim_type = GL_TRIANGLES;
	GLint vertexes_index_first = 0;
	GLsizei vertexes_count = 3;
};

class EBO : RPObject
{
public:
	EBO();
	~EBO() override;
	void SetDataBuffer(GLsizeiptr size_vertexes, const void* vertexes, GLsizeiptr size_indices, const void* indices, GLenum drawType = GL_STATIC_DRAW);
	void SetDataDraw(const void* iOffset, GLsizei iCount, GLenum iType = GL_UNSIGNED_INT, GLenum primType = GL_TRIANGLES);
	void Gen(int) override;
	void Bind() override;
	void Unbind() override;
	void Draw() override;
	void Destroy(int) override;
	void Get(unsigned int*& eboId, unsigned int*& vaoId, unsigned int*& vboId)
	{
		eboId = &rpo;
		vao->Get(vaoId, vboId);
	}
private:
	VAO* vao;
	GLsizeiptr indices_buffer_size = 0;
	const void* indices_buffer;
	GLenum type_draw = GL_STATIC_DRAW;
	GLenum type_prim = GL_TRIANGLES;
	GLenum type_indices = GL_UNSIGNED_INT;
	const void* vertexes_offset = nullptr;
	GLsizei vertexes_count = 3;
};

