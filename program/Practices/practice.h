#pragma once
#include <iostream>
#include <vector>

#include "Perfabs.h"

namespace Practice
{
    class HelloTrianglePractice1 : RenderProgram
    {
    public:
        std::vector<float> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<unsigned int> Indices_offset;

        RpoContext* Context;
        GLsizei DrawCount = 3;
        GLenum PrimType = GL_TRIANGLES;

        HelloTrianglePractice1(ERpoType rpoStrategy, const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
            : Vertices(vertices),
              Indices(indices)
        {
            Context = new RpoContext(rpoStrategy);
        }

        ~HelloTrianglePractice1() override { delete Context; }

    private:
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

    protected:
        int InitOther() override;
        void LoopRender() override;
        void Destroy() override;

    public:
        static int Start(ERpoType rpoStrategy, const std::vector<float>& vertices, GLsizei DrawCount = 3, const std::vector<unsigned int>& indices = std::vector<unsigned int>())
        {
            const auto base = new HelloTrianglePractice1(rpoStrategy, vertices, indices);
            base->SetProfile(rpoStrategy != ERpoType::Vbo);
            base->DrawCount = DrawCount;
            return base->Run();
        }

        static int Start()
        {
            std::vector<float> vertices
            {
                /*2 connected triangle (EBO)*/
                // 0.0f, 0.0f, 0.0f,
                // -0.5f, 0.5f, 0.0f,
                // -0.5f, -0.5f, 0.0f,
                // 0.5f, 0.5f, 0.0f,
                // 0.5f, -0.5f, 0.0f,

                /*2 connected triangle (VAO)*/
                0.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
            };

            return Start(ERpoType::Vao, vertices, 6, std::vector<unsigned int>());
        }
    };

    class HelloTrianglePractice2 : RenderProgram
    {
    public:
        std::vector<float> Vertices1;
        std::vector<float> Vertices2;

    private:
        RpoContext* Context;
        GLenum PrimType = GL_TRIANGLES;

    public:
        HelloTrianglePractice2()
            : Context(new RpoContext(ERpoType::Vao))
        {
        }

        ~HelloTrianglePractice2() override { delete Context; }

    private:
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

    protected:
        int InitOther() override;
        void LoopRender() override;
        void Destroy() override;

    public:
        static int Start(const std::vector<float>& vertices1, const std::vector<float>& vertices2, GLenum primType)
        {
            const auto base = new HelloTrianglePractice2();
            base->Vertices1 = vertices1;
            base->Vertices2 = vertices2;
            base->PrimType = primType;
            return base->Run();
        }

        static int Start()
        {
            std::vector<float> vertices1
            {
                0.0f, 0.0f, 0.0f,
                -0.4f, 0.8f, 0.0f,
                -0.8f, 0.0f, 0.0f,
            };
            
            std::vector<float> vertices2
            {
                0.0f, 0.0f, 0.0f,
                0.8f, 0.0f, 0.0f,
                0.4f, -0.8f, 0.0f,
            };

            return Start(vertices1, vertices2, GL_TRIANGLES);
        }
    };

    class HelloTrianglePractice3 : RenderProgram
    {
    public:
        std::vector<float> Vertices;
        std::vector<unsigned int> Indices;

    private:
        RpoContext* Context;
        GLenum PrimType = GL_TRIANGLES;

    public:
        HelloTrianglePractice3()
            : Context(new RpoContext(ERpoType::Ebo))
        {
        }

        ~HelloTrianglePractice3() override { delete Context; }

    private:
        const char* vertexShaderSource = "#version 460 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource1 = "#version 460 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
            "}\0";
        const char* fragmentShaderSource2 = "#version 460 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
            "}\0";

        unsigned int shaderProgram1 = 0;
        unsigned int shaderProgram2 = 0;

    protected:
        int InitOther() override;
        void LoopRender() override;
        void Destroy() override;

    public:
        static int Start(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum primType)
        {
            const auto base = new HelloTrianglePractice3();
            base->Vertices = vertices;
            base->Indices = indices;
            base->PrimType = primType;
            return base->Run();
        }

        static int Start()
        {
            std::vector<float> vertexes
            {
                0.0f, 0.0f, 0.0f,
                -0.5f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f,
                0.0f, -0.5f, 0.0f,
                0.5f, 0.0f, 0.0f,
            };
            
            std::vector<unsigned int> indices
            {
                0, 1, 2,
                0, 3, 4,
            };

            return Start(vertexes, indices, GL_TRIANGLES);
        }
    };
};


