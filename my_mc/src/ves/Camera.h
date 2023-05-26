#pragma once

#include "../thr/glm/glm/glm.hpp"
#include "../thr/glm/glm/gtc/matrix_transform.hpp"

enum Camera_Movement
{
	FORWARD , BACKWARD , LEFT , RIGHT , UP , DOWN
};

class Camera
{
private:	
public:	
	float lastX = 0;
	float lastY = 0;
	//euler angle
	float yaw = -90.0f;
	float pitch = 0.0f;
	//camera position
	float fov = 40.0f;
	float sensitivity = 0.05;
	float movementSpeed = 6.5f;
	bool firstMouse = true;

	//glm::vec3 cameraPos = glm::vec3(5.f, 40.f, 5.f);
	glm::vec3 cameraPos = glm::vec3(0.f, 60.f, 0.f);
	glm::vec3 cameraPosLastFrame = cameraPos;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	void PositionMovement(float deltaTime, Camera_Movement direction);

	void ScrollMovement(double xoffset, double yoffset);

	void LookMovement(double xpos, double ypos);

	glm::mat4 GetViewMatrix(){return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);}
};