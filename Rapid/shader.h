#ifndef SHADER_H
#define SHADER_H

#include "file.h"
#include <glad/glad.h>

class Shader {

public: 
  // Shader program handle
  unsigned int ID;
  
  /// <summary>
  /// Creates shader program from given vertex and fragment shader paths
  /// </summary>
  /// <param name="vPath">vertex shader file path</param>
  /// <param name="fPath">fragment shader file path</param>
  Shader(const char* path, GLuint type);
  /// <summary>
  /// Delete the shader
  /// </summary>
  void deleteShader();
};

#endif