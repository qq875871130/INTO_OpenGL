#include "Perfabs.h"

#include <vector>

#pragma region VBO

void VerticleBufferObject::SetDataBuffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	buffer_size_vertexes = size;
	buffer_vertexes = vertexes;
	draw_type = drawType;
}

void VerticleBufferObject::SetDataDraw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType = GL_TRIANGLES)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VerticleBufferObject::Gen(int num)
{
	rpo = std::vector<unsigned int>(num);
	glGenBuffers(num, rpo.data());
}

void VerticleBufferObject::Bind()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glBindBuffer(GL_ARRAY_BUFFER, o);
		glBufferData(GL_ARRAY_BUFFER, buffer_size_vertexes, buffer_vertexes, draw_type);
	}
}

void VerticleBufferObject::Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	glBindVertexArray(rpo[i]);
	glBindBuffer(GL_ARRAY_BUFFER, rpo[i]);
	glBufferData(GL_ARRAY_BUFFER, vSize, vertexes, drawType);
}

void VerticleBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VerticleBufferObject::Draw()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
		glBindVertexArray(0);
	}
}

void VerticleBufferObject::Draw(int i) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	glBindVertexArray(rpo[i]);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	glBindVertexArray(0);
}

void VerticleBufferObject::Destroy(int n)
{
	glDeleteBuffers(n, rpo.data());
}



#pragma endregion

#pragma region VAO
VerticleArrayObject::VerticleArrayObject()
{
	vbo = new VerticleBufferObject();
}

void VerticleArrayObject::SetDataBuffer(GLsizeiptr size, const void* vertexes, GLenum drawType)
{
	vbo->SetDataBuffer(size, vertexes, drawType);
}

void VerticleArrayObject::SetDataDraw(GLint vFirst = 0, GLsizei vCount = 3, GLenum primType)
{
	vertexes_index_first = vFirst;
	vertexes_count = vCount;
	prim_type = primType;
}

void VerticleArrayObject::Gen(int num)
{
	rpo = std::vector<unsigned int>(num);
	glGenVertexArrays(num, rpo.data());
	vbo->Gen(num);
}

void VerticleArrayObject::Bind()
{
	vbo->Bind();

	for (auto o : rpo)
	{
		glBindVertexArray(o);
	}
}

void VerticleArrayObject::Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}
	
	vbo->Bind(i, vSize, vertexes, drawType);
	glBindVertexArray(rpo[i]);
}

void VerticleArrayObject::Unbind()
{
	vbo->Unbind();
}

void VerticleArrayObject::Draw()
{
	for (auto o : rpo)
	{
		glBindVertexArray(o);
		glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
		glBindVertexArray(0);
	}
}

void VerticleArrayObject::Draw(int i) const
{
	if (i >= static_cast<int>(rpo.size()))
	{
		return;
	}

	glBindVertexArray(rpo[i]);
	glDrawArrays(prim_type, vertexes_index_first, vertexes_count);
	glBindVertexArray(0);
}

void VerticleArrayObject::Destroy(int n)
{
	glDeleteVertexArrays(n, rpo.data());
	vbo->Destroy(n);
}
#pragma endregion

#pragma region EBO
EBO::EBO()
{
	vao = new VerticleArrayObject();
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->Unbind();
}

void EBO::Draw()
{
	for (int i = 0; i < static_cast<int>(rpo.size()); i++)
	{
		unsigned int vaoId = 0;
		unsigned int vboId = 0;
		vao->Get(&vaoId, &vboId, i);
		
		glBindVertexArray(vaoId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rpo[i]);
		glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
		Unbind();
	}
}

void EBO::Draw(int i) const
{
	unsigned int vaoId = 0;
	unsigned int vboId = 0;
	vao->Get(&vaoId, &vboId, i);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rpo[i]);
	glDrawElements(type_prim, vertexes_count, type_indices, vertexes_offset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vao->Unbind();
}

void EBO::Destroy(int n)
{
	glDeleteBuffers(n, rpo.data());
	vao->Destroy(n);
}
#pragma endregion

