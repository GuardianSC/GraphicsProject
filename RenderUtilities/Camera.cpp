#include "Camera.h"
#include "Timer.h"
#include "Input.h"

void FlyCamera::update(const Input &input, const Time &time)
{
	// direction represents our forward direction

	glm::vec3 moveDir = glm::vec3(0, 0, 0);
	glm::vec3 right = glm::cross(direction, glm::vec3(0, 1, 0));
	glm::vec3 up = glm::cross(right, direction);
	direction = glm::vec3(glm::rotate(yaw, glm::vec3(0, 1, 0))[2]);
	right = glm::cross(direction, up);
	direction = glm::mat3(glm::rotate(pitch, right)) * direction;

	//printf("%f\n", direction.x);

	if (input.getKeyState('W') == Input::DOWN)
		moveDir += direction;
	if (input.getKeyState('S') == Input::DOWN)
		moveDir -= direction;
	
	if (input.getKeyState('D') == Input::DOWN)
		moveDir += right;
	if (input.getKeyState('A') == Input::DOWN)
		moveDir -= right;
	if (input.getKeyState('E') == Input::DOWN)
			moveDir += up;
	if (input.getKeyState('E') == Input::DOWN)
		moveDir -= up;

	yaw -= input.getMouseH() * time.getDeltaTime() * 100;
	pitch -= input.getMouseV() * time.getDeltaTime() * 100;

	/*direction.x = cos(yaw) * sin(pitch);
	direction.y = cos(yaw);
	direction.z = sin(yaw) * sin(pitch);*/

	 

	if (glm::length(moveDir) >= .7f)
	{
		moveDir = glm::normalize(moveDir);
		position += moveDir * time.getDeltaTime();
	}
}