#include "renderer.h"

Renderer::Renderer(std::vector<Renderable> _input, LightComposition lights) {
  renderables = _input;
  lightComposition = lights;
  
  // Initialize default shader
  ShaderProgram program;
  Shader frag("default.frag", GL_FRAGMENT_SHADER);
  Shader vert("default.vert", GL_VERTEX_SHADER);
  program.addShader(frag);
  program.addShader(vert);
  program.link();

  for (Renderable renderable : renderables) {
    renderable.Shader = &program;
    renderable.Setup();
    renderable.UpdateLights(lights);
  }

  // initial clear
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Update() {
  //clear 
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (Renderable renderable : renderables) {
    renderable.Update();
  }
}

void Renderer::Delete() {
  for (Renderable renderable : renderables) {
    renderable.Delete();
  }
}