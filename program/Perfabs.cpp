#include "Perfabs.h"

#include <vector>

#pragma region VBO

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
	rpo = std::vector<unsigned int>(num);
	glGenBuffers(num, rpo.data());
}

void VBO::Bind()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glBindBuffer(GL_ARRAY_BUFFER, o);
		glBufferData(GL_ARRAY_BUFFER, buffer_size_vertexes, buffer_vertexes, draw_type);
	}
}

void VBO::Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	glBindVertexArray(rpo[i]);
	glBindBuffer(GL_ARRAY_BUFFER, rpo[i]);
	glBufferData(GL_ARRAY_BUFFER, vSize, vertexes, drawType);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VBO::Draw()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
		glBindVertexArray(0);
	}
}

void VBO::Draw(int i) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	glBindVertexArray(rpo[i]);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	glBindVertexArray(0);
}

void VBO::Destroy(int n)
{
	glDeleteBuffers(n, rpo.data());
}



#pragma endregion

#pragma region VAO
VAO::VAO()
{
	vbo = new VBO();
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
	rpo = std::vector<unsigned int>(num);
	glGenVertexArrays(num, rpo.data());
	vbo->Gen(num);
}

void VAO::Bind()
{
	vbo->Bind();

	for (auto o : rpo)
	{
		glBindVertexArray(o);
	}
}

void VAO::Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	vbo->Bind(i, vSize, vertexes, drawType);
	glBindVertexArray(rpo[i]);
}

void VAO::Unbind()
{
	vbo->Unbind();
}

void VAO::Draw()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
		glBindVertexArray(0);
	}
}

void VAO::Draw(int i) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}

	glBindVertexArray(rpo[i]);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	glBindVertexArray(0);
}

void VAO::Destroy(int n)
{
	glDeleteVertexArrays(n, rpo.data());
	vbo->Destroy(n);
}
#pragma endregion

#pragma region EBO
EBO::EBO()
{
	vao = new VAO();
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
	rpo = std::vector<unsigned int>(num);
	
	vao->Gen(num);
	glGenBuffers(num, rpo.data());
}

void EBO::Bind()
{
	vao->Bind();

	for (auto o : rpo)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_buffer_size, indices_buffer, type_draw);
	}
}

void EBO::Bind(int i, GLsizeiptr vSize, const void* vertexes,
               GLsizeiptr iSize, const void* indices, GLenum drawType) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}

	vao->Bind(i, vSize, vertexes, drawType);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rpo[i]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, drawType);
}

void EBO::Unbind()
{
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->Unbind();
}

void EBO::Draw()
{
	unsigned int vaoId = 0;
	unsigned int vboId = 0;
	vao->Get(&vaoId, &vboId);

	glBindVertexArray(vaoId);
	glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
	glBindVertexArray(0);
}

void EBO::Draw(int i) const
{
	unsigned int vaoId = 0;
	unsigned int vboId = 0;
	vao->Get(&vaoId, &vboId, i);

	glBindVertexArray(vaoId);
	glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
	glBindVertexArray(0);
}

void EBO::Destroy(int n)
{
	glDeleteBuffers(n, rpo.data());
	vao->Destroy(n);
}
#pragma endregion

