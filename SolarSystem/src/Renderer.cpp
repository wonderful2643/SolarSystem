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

void Renderer::Draw(int numIndices) const
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

//void Renderer::setCircleVertex(const float radius)
//{
//  for (int i = 0; i < 360;)
//  {
//    circleVertex[i++] = radius * cos(i * PI / 180.0f);
//    circleVertex[i++] = 0.0f;
//    circleVertex[i++] = radius * sin(i * PI / 180.0f);
//  }
//}


