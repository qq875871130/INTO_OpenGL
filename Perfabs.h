#pragma once
#include "GLBase.h"

class VBO : RPObject
{
public:
	VBO();
	~VBO();
	void set_data_buffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void set_data_draw(GLint, GLsizei, GLenum);
	void gen(int) override;
	void bind() override;
	void unbind() override;
	void draw() override;
	void destory(int) override;
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
	~VAO();
	void set_data_buffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void set_data_draw(GLint, GLsizei, GLenum);
	void gen(int) override;
	void bind() override;
	void unbind() override;
	void draw() override;
	void destory(int) override;
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
	~EBO();
	void set_data_buffer(GLsizeiptr, const void*, GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void set_data_draw(const void*, GLsizei, GLenum = GL_UNSIGNED_INT, GLenum = GL_TRIANGLES);
	void gen(int) override;
	void bind() override;
	void unbind() override;
	void draw() override;
	void destory(int) override;
private:
	VAO* vao;
	GLsizeiptr indices_buffer_size = 0;
	const void* indices_buffer;
	GLenum type_draw = GL_STATIC_DRAW;
	GLenum type_prim = GL_TRIANGLES;
	GLenum type_indices = GL_UNSIGNED_INT;
	const void* vertexes_offset = 0;
	GLsizei vertexes_count = 3;
};

