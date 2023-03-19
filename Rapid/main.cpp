#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderProgram.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"


int main()
{
  int width = 800;
  int height = 800;

  glfwInit();

  // Set OpenGL version hint
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Set OpenGL core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] =
  { //     COORDINATES 
    -0.5f, 0.0f,  0.5f,
    -0.5f, 0.0f, -0.5f,
     0.5f, 0.0f, -0.5f,
     0.5f, 0.0f,  0.5f,
     0.0f, 0.8f,  0.0f
  };

  GLuint indices[] =
  {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
  };

  GLFWwindow* window = glfwCreateWindow(width, height, "Title", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to initialize the window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  gladLoadGL();
  
  glViewport(0, 0, width, height);

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
  EBO ebo(indices, sizeof(indices));

  vao.LinkVBO(vbo, 0);
  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
  
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glfwSwapBuffers(window);

  double prevTime = glfwGetTime();
  
  glEnable(GL_DEPTH_TEST);

  Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.use();

    // Camera functionality
    camera.Matrix(45.0f, 0.1f, 100.0f, program, "camMatrix");
    camera.Inputs(window);
   
    vao.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  vao.Delete();
  vbo.Delete();
  ebo.Delete();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
