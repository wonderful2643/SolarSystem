#include "Renderer.h"

#include <iostream>

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
  while (GLenum error = glGetError())
  {
    std::cout << "[OpenGL Error] (" << error << "): function:" << function
      << "\nfile: " << file << "\nline: " << line << std::endl;
    return false;
  }
  return true;
}

//void Renderer::Clear()const
//{
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}

//void Renderer::DrawTriangle(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
//{
//  shader.Bind();
//  va.Bind();
//  ib.Bind();
//  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
//}
//
//void Renderer::DrawSphere(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
//{
//  //GLCall(glEnable(GL_CULL_FACE));
//  //GLCall(glCullFace(GL_BACK));
//  GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
//
//  DrawTriangle(va, ib, shader);
//}
