#include "shader.h"

Shader::Shader(const char* path, GLuint type) {
  int success;
  char log[512];

  // Read shader file contents
  std::string cont = File::readFile(path);
  const char* source = cont.c_str();
  // Create shader object
  unsigned int shaderId = glCreateShader(type);
  // Load shader code
  glShaderSource(shaderId, 1, &source, NULL);
  // Compile shader
  glCompileShader(shaderId);

  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(shaderId, 512, NULL, log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
  };
  
  // Set shader id for public access
  ID = shaderId;
}

void Shader::deleteShader() {
  glDeleteShader(ID);
}