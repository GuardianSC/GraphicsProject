#pragma once
#define GLM_SWIZZLE
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

class FlyCamera
{
	glm::vec3 position; // Camera position
	glm::vec3 direction; // Direction camera is facing

	glm::mat4 transform; // Camera's transform

	// yaw is along the Y axis, pitch is along the X axis, roll is along the Z axis
	float yaw, pitch, roll;

	float aspect, fov, near, far; // near must be greater than 0
	
	float speed;
public:
	// Default constructor
	FlyCamera(float a_aspect = 16.f / 9.f, float a_fov = 45.f, float a_near = 1.f, float a_far = 100.f)
		: aspect(a_aspect), fov(a_fov), near(a_near), far(a_far), direction(0, 0, 1), speed(20), pitch(0), yaw(0), roll(0) {}

	void update(const class Input &input, const class Time &time);

	// Look at a specific position(target)
	void lookAt(const glm::vec3 target) { direction = normalize(target - position); }

	// Jump the camera to a location
	void jumpTo(const glm::vec3 &location) { position = location; }

	// Get the viewing matrix
	glm::mat4 getView() const { return glm::inverse(transform); }

	// Get the projection matrix
	glm::mat4 getProjection() const { return glm::perspective(fov, aspect, near, far); }
};