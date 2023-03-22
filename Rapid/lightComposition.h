#ifndef LIGHT_COMPOSITION_STRUCT_H
#define LIGHT_COMPOSITION_STRUCT_H 

#include <glm/glm.hpp>

struct LightComposition {
  glm::vec4 lightColor;
  glm::vec3 lightPosition;
};

#endif