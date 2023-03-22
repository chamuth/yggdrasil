#include "renderable.h"

/// <summary>
/// Setup the renderable before the main render loop
/// Vertices, indices, shader must be set
/// </summary>
void Renderable::Setup() {
  VAO vao;
  vao.Bind();

  GLfloat* vertices = &Vertices[0];
  GLuint* indices = &Indices[0];

  VBO vbo(vertices, sizeof(vertices));
  EBO ebo(indices, sizeof(indices));

  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
  vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();

  // Set model matrix
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, Position);
  glUniformMatrix4fv(Shader->getUniformID("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Renderable::Update() {
  _vao->Bind();
  glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

/// <summary>
/// Update lights after setting up the shader
/// </summary>
/// <param name="lights">Light composition</param>
void Renderable::UpdateLights(LightComposition lights) {
  Shader->use();
  glUniform4f(Shader->getUniformID("lightColor"), lights.lightColor.x, lights.lightColor.y, lights.lightColor.z, lights.lightColor.w);
  glUniform3f(Shader->getUniformID("lightPos"), lights.lightColor.x, lights.lightColor.y, lights.lightColor.z);
}

/// <summary>
/// Delete data on program end
/// </summary>
void Renderable::Delete() {
  _vao->Delete();
  _vbo->Delete();
  _ebo->Delete();
}