// Rapid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"
#include "vao.h"
#include "vbo.h"

int main()
{
  glfwInit();

  // Set OpenGL version hint
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Set OpenGL core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
  };

  GLFWwindow* window = glfwCreateWindow(800, 800, "Title", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to initialize the window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  gladLoadGL();

  
  glViewport(0, 0, 800, 800);

  // Initialize shader program;
  ShaderProgram program;
  Shader frag("default.frag", GL_FRAGMENT_SHADER);
  Shader vert("default.vert", GL_VERTEX_SHADER);
  program.addShader(frag);
  program.addShader(vert);
  program.link();

  VAO vao;
  vao.Bind();

  VBO vbo(vertices, sizeof(vertices));
  vao.LinkVBO(vbo, 0);
  vao.Unbind();
  vbo.Unbind();
  
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    program.use();
    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  vao.Delete();
  vbo.Delete();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
