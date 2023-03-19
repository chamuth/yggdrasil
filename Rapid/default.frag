#version 330 core

// final color output
out vec4 FragColor;

in vec3 normal;
in vec3 currentPos;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
  float ambient = 0.2f;
  vec3 n = normalize(normal);
  vec3 lightDirection = normalize(lightPos - currentPos);

  // Diffuse lighting
  float diffuse = max(dot(n, lightDirection), 0.0f);

  // Specular Lighting
  float spec = 2f;
  vec3 viewDirection = normalize(camPos - currentPos);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
  float specular = specAmount * spec;

  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f) * lightColor * (diffuse + ambient + specular );
}