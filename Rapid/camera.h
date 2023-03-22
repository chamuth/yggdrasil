#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderProgram.h"

struct CameraConfig {
	/// <summary>
	/// Width of the viewport
	/// </summary>
	int width;
	/// <summary>
	/// Height of the viewport
	/// </summary>
	int height;
	/// <summary>
	/// Position vector of the camera
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// FOV of camera
	/// </summary>
	float fov;
	/// <summary>
	/// Near clip plane
	/// </summary>
	float nearPlane;
	/// <summary>
	/// Far clip plane
	/// </summary>
	float farPlane;
	/// <summary>
	/// CameraMatrix uniform name
	/// </summary>
	const char* uniformName;

	// Movement configurations
};


class Camera
{
public:
	CameraConfig* config;

	// Stores the main vectors of the camera
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;


	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(CameraConfig *config);

	// Updates and exports the camera matrix to the Vertex Shader
	void Update(std::vector<ShaderProgram> shaders);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
};
#endif