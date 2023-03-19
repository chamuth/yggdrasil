#version 330 core

// Stride inputs
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

out vec3 currentPos;
out vec3 normal;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
  currentPos = vec3(model * vec4(aPos, 1.0f));
  gl_Position = camMatrix * vec4(aPos, 1.0);
  normal = aNormal;
}