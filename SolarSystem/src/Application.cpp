#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Sphere.h"
#include "Config.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// camera
Camera camera(glm::vec3(0.0f, 1.5f, 35.0f));
float lastX = WindowWidth / 2.0f;
float lastY = WindowHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

const float Scale = 2.0f;
const float ErothAxialAngle = 23.44;
const float SunEarthDistance = 10.0f;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Solar System", nullptr, nullptr);

  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  //注释该行，调试出bug键盘鼠标不会卡死
  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;
  
  //获得球体所有顶点坐标以及EBO数组
  Sphere mySphere(40);
  std::vector<float> sphereVertices = mySphere.getVertices();
  std::vector<unsigned int> sphereIndices = mySphere.getIndices();

  {
    VertexArray va;
    VertexBuffer vb(&sphereVertices[0], sphereVertices.size() * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(layout);

    IndexBuffer ib(&sphereIndices[0], sphereIndices.size());//放在最后

    glEnable(GL_DEPTH_TEST);

    Shader shader("res/shader/task3.vs", "res/shader/task3.fs");
    shader.Bind();
    shader.setInt("u_Texture", 0);

    Texture textureSun("res/textures/sun.jpg");
    Texture textureEarth("res/textures/earth.jpg");

    vb.Unbind();
    va.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer render;

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
      float currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(window);

      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glm::mat4 view = camera.GetViewMatrix();
      glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);

      va.Bind();
      {
        glm::mat4 model = glm::mat4(1.0f);
        // 公转
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(SunEarthDistance, .0f, .0f));
        // 抵消公转对自身倾斜方向的影响，保证公转后 仍然向右倾斜
        model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, -glm::radians(ErothAxialAngle), glm::vec3(0.0, 0.0, 1.0));
        // 自转
        model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp = proj * view * model;

        textureEarth.Bind();
        shader.Bind();
        shader.setMat4("u_MVP", mvp);

        render.Draw(mySphere.getNumIndices());
      }

      {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(glm::mat4(1.0f), -(float)glfwGetTime() / 10, glm::vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, glm::vec3(Scale, Scale, Scale));
        glm::mat4 mvp = proj * view * model;

        textureSun.Bind();
        shader.Bind();
        shader.setMat4("u_MVP", mvp);

        render.Draw(mySphere.getNumIndices());
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}