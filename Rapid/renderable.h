#ifndef RENDERABLE_STRUCT_H
#define RENDERABLE_STRUCT_H

#include <vector>

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lightComposition.h"

class Renderable {
public:
  std::vector<GLfloat> Vertices;
  std::vector<GLuint> Indices;
  ShaderProgram* Shader;
  glm::vec3 Position;
  
  void Setup();
  void Update();

  void Delete();
  void UpdateLights(LightComposition lights);

private:
  VAO* _vao;
  VBO* _vbo;
  EBO* _ebo;
};

#endif