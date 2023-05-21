#pragma once
#include "Camera.h"

void Camera::PositionMovement(float deltaTime, Camera_Movement direction)
{
	float cameraSpeed = movementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		cameraPos += cameraFront * cameraSpeed;
	}
	if (direction == BACKWARD)
	{
		cameraPos -= cameraFront * cameraSpeed;
	}
	if (direction == RIGHT)
	{
		cameraPos -= glm::cross(cameraUp, cameraFront) * cameraSpeed;
	}
	if (direction == LEFT)
	{
		cameraPos += glm::cross(cameraUp, cameraFront) * cameraSpeed;
	}
}	

void Camera::ScrollMovement(double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

void Camera::LookMovement(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}