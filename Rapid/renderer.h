#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H 

#include <vector>
#include "renderable.h"
#include <glad/glad.h>

class Renderer {
public:
  Renderer(std::vector<Renderable> _input, LightComposition lights);
  void Update();
  void Delete();
private:
  std::vector<Renderable> renderables;
  LightComposition lightComposition;
  ShaderProgram defaultShader;
};

#endif