#pragma once
#include "GLBase.h"

enum class ERpoType : unsigned int
{
	Vbo,
	Vao,
	Ebo
};

class VerticleBufferObject : public RenderPipelineObject
{
public:
	VerticleBufferObject() = default;
	void SetDataBuffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void SetDataDraw(GLint, GLsizei, GLenum);
	void Gen(int) override;
	void Bind() override;
	void Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType = GL_STATIC_DRAW) const;
	void Unbind() override;
	void Draw() override;
	void Draw(int) const;
	void Destroy(int) override;
	void Get(unsigned int* vboId, int i = 0) const { *vboId = rpo[i]; }
private:
	GLsizeiptr buffer_size_vertexes = 0;
	const void* buffer_vertexes;
	GLenum draw_type = GL_STATIC_DRAW;
	GLenum prim_type = GL_TRIANGLES;
	GLint vertexes_index_first = 0;
	GLsizei vertexes_count = 3;
};

class VerticleArrayObject : public RenderPipelineObject
{
public:
	VerticleArrayObject();
	~VerticleArrayObject() override { delete vbo; }
	void SetDataBuffer(GLsizeiptr, const void*, GLenum = GL_STATIC_DRAW);
	void SetDataDraw(GLint, GLsizei, GLenum = GL_TRIANGLES);
	void Gen(int) override;
	void Bind() override;
	void Bind(int i, GLsizeiptr vSize, const void* vertexes, GLenum drawType = GL_STATIC_DRAW) const;
	void Unbind() override;
	void Draw() override;
	void Draw(int) const;
	void Destroy(int) override;

	void Get(unsigned int* vaoId, unsigned int* vboId, int i = 0) const
	{
		*vaoId = rpo[i];
		vbo->Get(vboId);
	}
private:
	VerticleBufferObject* vbo;
	GLenum prim_type = GL_TRIANGLES;
	GLint vertexes_index_first = 0;
	GLsizei vertexes_count = 3;
};

class EBO : public RenderPipelineObject
{
public:
	EBO();
	~EBO() override { delete vao; }
	void SetDataBuffer(GLsizeiptr size_vertexes, const void* vertexes, GLsizeiptr size_indices, const void* indices, GLenum drawType = GL_STATIC_DRAW);
	void SetDataDraw(const void* iOffset, GLsizei iCount, GLenum iType = GL_UNSIGNED_INT, GLenum primType = GL_TRIANGLES);
	void Gen(int) override;
	void Bind() override;
	void Bind(int i, GLsizeiptr vSize, const void* vertexes, GLsizeiptr iSize, const void* indices, GLenum drawType = GL_STATIC_DRAW) const;
	void Unbind() override;
	void Draw() override;
	void Draw(int) const;
	void Destroy(int) override;
	void Get(unsigned int* eboId, unsigned int* vaoId, unsigned int* vboId, int i = 0) const
	{
		*eboId = rpo[i];
		vao->Get(vaoId, vboId);
	}
private:
	VerticleArrayObject* vao;
	GLsizeiptr indices_buffer_size = 0;
	const void* indices_buffer = nullptr;
	GLenum type_draw = GL_STATIC_DRAW;
	GLenum type_prim = GL_TRIANGLES;
	GLenum type_indices = GL_UNSIGNED_INT;
	const void* vertexes_offset = nullptr;
	GLsizei vertexes_count = 3;
};

struct RpoContext
{
private:
	RenderPipelineObject* rpo;
	unsigned int shaderProgram = 0;
	
public:
	ERpoType RpoStrategy;

	RpoContext(const ERpoType strategy) : RpoStrategy(strategy)
	{
		switch (strategy)
		{
		case ERpoType::Vbo:
			rpo = new VerticleBufferObject();
			break;
		case ERpoType::Vao:
			rpo = new VerticleArrayObject();
			break;
		case ERpoType::Ebo:
			rpo = new EBO();
			break;
		}
	}

	RpoContext() :
		rpo(new VerticleBufferObject()),
		RpoStrategy(ERpoType::Vbo)
	{
	}

	~RpoContext() { delete rpo; }
	
	static void ParseVertexes(GLuint index = 0, GLint size = 3, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 3 * sizeof(float), const void *pointer = nullptr, GLuint startInd = 0)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(startInd);
	}


	template<typename T>
	T* GetRpo() const
	{
		return dynamic_cast<T*>(rpo);
	}

	RenderPipelineObject* GetRpo() const
	{
		return rpo;
	}

	void GetRpoId(unsigned int* eboId, unsigned int* vaoId, unsigned int* vboId) const
	{
		switch (RpoStrategy)
		{
		case ERpoType::Vbo:
			GetRpo<VerticleBufferObject>()->Get(vboId);
			break;
		case ERpoType::Vao:
			GetRpo<VerticleArrayObject>()->Get(vaoId, vboId);
			break;
		case ERpoType::Ebo:
			GetRpo<EBO>()->Get(eboId,vaoId, vboId);
			break;
		}
	}

	void SetDataBuffer(GLsizeiptr size_vertexes, const void* vertexes, GLsizeiptr size_indices,const void* indices, GLenum drawType = GL_STATIC_DRAW) const
	{
		if (RpoStrategy == ERpoType::Ebo) GetRpo<EBO>()->SetDataBuffer(size_vertexes, vertexes, size_indices, indices, drawType);
		else if (RpoStrategy == ERpoType::Vao) GetRpo<VerticleArrayObject>()->SetDataBuffer(size_vertexes, vertexes, drawType);
		else GetRpo<VerticleBufferObject>()->SetDataBuffer(size_vertexes, vertexes, drawType);
	}

	void SetDataDraw(GLint first, GLsizei count, const void* iOffset, GLenum iType, GLenum primType = GL_TRIANGLES) const
	{
		if (RpoStrategy == ERpoType::Ebo) GetRpo<EBO>()->SetDataDraw(iOffset, count, iType, primType);
		else if (RpoStrategy == ERpoType::Vao) GetRpo<VerticleArrayObject>()->SetDataDraw(first, count, primType);
		else GetRpo<VerticleBufferObject>()->SetDataDraw(first, count, primType);
	}

	void BindByIndex(int i, GLsizeiptr vSize, const void* vertexes, GLsizeiptr iSize, const void* indices, GLenum drawType) const
	{
		if (RpoStrategy == ERpoType::Ebo) GetRpo<EBO>()->Bind(i, vSize, vertexes, iSize, indices, drawType);
		else if (RpoStrategy == ERpoType::Vao) GetRpo<VerticleArrayObject>()->Bind(i, vSize, vertexes, drawType);
		else GetRpo<VerticleBufferObject>()->Bind(i, vSize, vertexes, drawType);
	}

	void DrawByIndex(int i) const
	{
		if (RpoStrategy == ERpoType::Ebo) GetRpo<EBO>()->Draw(i);
		else if (RpoStrategy == ERpoType::Vao) GetRpo<VerticleArrayObject>()->Draw(i);
		else GetRpo<VerticleBufferObject>()->Draw(i);
	}
	
	//Create, compile and attach shader to program
	void InitShaderProgram(const char* vShaderSource, const char* fShaderSource)
	{
		//Create
		unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		
		//Compile
		glShaderSource(vertex_shader, 1, &vShaderSource, nullptr);
		glCompileShader(vertex_shader);
		glShaderSource(fragment_shader, 1, &fShaderSource, nullptr);
		glCompileShader(fragment_shader);

		shaderProgram = glCreateProgram();

		//Attach/Link
		glAttachShader(shaderProgram, vertex_shader);
		glAttachShader(shaderProgram, fragment_shader);
		glLinkProgram(shaderProgram);

		//Release
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	void UseShaderProgram() const
	{
		glUseProgram(shaderProgram);
	}
	
	void ReleaseShaderProgram() const
	{
		glDeleteProgram(shaderProgram);
	}

	static unsigned int InitShaderProgram(const std::vector<unsigned int>& shaderIDs, const std::vector<const char*>& shaderSources)
	{
		unsigned int program = glCreateProgram();
		
		for (int i = 0; i < static_cast<int>(shaderIDs.size()); ++i)
		{
			glShaderSource(shaderIDs[i], 1, &(shaderSources[i]), nullptr);
			glCompileShader(shaderIDs[i]);
			glAttachShader(program, shaderIDs[i]);
		}

		glLinkProgram(program);
		for (const auto id : shaderIDs)
		{
			glDeleteShader(id);
		}
		return program;
	}

	static void UseShaderProgram(const unsigned int programId)
	{
		glUseProgram(programId);
	}

	static void ReleaseShaderProgram(const unsigned int programId)
	{
		glDeleteProgram(programId);
	}
};
