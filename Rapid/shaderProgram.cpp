#include "shaderProgram.h"

ShaderProgram::ShaderProgram() {
  ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(ID);
}

void ShaderProgram::addShader(Shader &shader) {
  shaders.push_back(shader);
}

void ShaderProgram::link() {
  int success;
  char log[512];

  // Attach all added shaders
  for (Shader shader : shaders) {
    glAttachShader(ID, shader.ID);
  }
    
  // Link shader program
  glLinkProgram(ID);

  // Get link logs 
  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, log);
    std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILURE\n" << log << std::endl;
  }

  // Delete shaders 
  for (Shader shader : shaders) {
    shader.deleteShader();
  }
}

void ShaderProgram::use() {
  glUseProgram(ID);
}

void ShaderProgram::setFloat(const std::string name, float f) {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), f);
}
