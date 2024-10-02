#pragma once
#include <iostream>
#include <vector>

#include "Perfabs.h"

namespace Practice
{
    class HelloTrianglePractice1 : Program
    {
    public:
        std::vector<float> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<unsigned int> Indices_offset;

        RpoContext* Context;
        GLsizei DrawCount = 3;
        GLenum PrimType = GL_TRIANGLES;

        unsigned int shaderProgram = 0;
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int ebo = 0;

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
    };
};

int helloTrangle_practice1();

int helloTrangle_practice2();

int helloTrangle_practice3();
