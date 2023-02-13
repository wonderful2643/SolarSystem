#pragma once
#include <glad/glad.h>

#include "VertexArray.h"
//#include "IndexBuffer.h"
//#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
  //void Clear()const;
  //void DrawTriangle(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;
  //void DrawSphere(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;
};