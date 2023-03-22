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
  { //     COORDINATES      // COLORS             // TEXCOORD       // NORMALS 
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
    0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
    0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

    0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
    0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
    0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

    0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side  
  };

  GLuint indices[] =
  {
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
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

  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
  vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();

  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glfwSwapBuffers(window);

  double prevTime = glfwGetTime();

  glEnable(GL_DEPTH_TEST);

  // Setup camera config
  CameraConfig cameraConfig;
  cameraConfig.position = glm::vec3(0.0f, 0.0f, 2.0f);
  cameraConfig.fov = 45.0f;
  cameraConfig.nearPlane = 0.1f;
  cameraConfig.farPlane = 100.0f;
  cameraConfig.uniformName = "camMatrix";
  cameraConfig.width = width;
  cameraConfig.height = height;

  // Initialize camera with config
  Camera camera(&cameraConfig);

  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);


  // Use shader program and set variables
  program.use();

  // Set light properties
  glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, pyramidPos);
  glUniformMatrix4fv(program.getUniformID("model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
  glUniform4f(program.getUniformID("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniform3f(program.getUniformID("lightPos"), lightPos.x, lightPos.y, lightPos.z);


  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update camera
    vector<ShaderProgram> shaders = { program };
    camera.Update(shaders);
    camera.Inputs(window);

    vao.Bind();

    // Set camera position for the shader
    program.use();
    glUniform3f(glGetUniformLocation(program.ID, "camPos"), cameraConfig.position.x, cameraConfig.position.y, cameraConfig.position.z);

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
