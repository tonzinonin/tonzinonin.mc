#pragma once

#include "ves/Camera.h"
#include "GL/glew.h"
#include "LandLoader.h"

bool isMouse = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
camera.LookMovement(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ScrollMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{
		if (isMouse == false)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, NULL);
			isMouse = true;
			std::cout << '!' << std::endl;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, mouse_callback);
			isMouse = false;
			std::cout << '?' << std::endl;
		}
	}
}

class Player
{
private:

	GLFWwindow*& window;
	Camera& camera;
	Terrain& terrain;

public:

	glm::vec3 moveVec;

	bool isMove_p_x = true;
	bool isMove_p_y = true;
	bool isMove_p_z = true;
	bool isMove_n_x = true;
	bool isMove_n_y = true;
	bool isMove_n_z = true;

	float CollierPos[6] = { 0.5 , 0.4 , 0.5 , -0.5 , -0.5 , -1.5 };
	float Collier_p_x = 0.5;
	float Collier_p_y = 0.4;
	float Collier_p_z = 0.5;
	float Collier_n_x = 0.5;
	float Collier_n_y = 1.5;
	float Collier_n_z = 0.5;

	Player(GLFWwindow*& window, Camera& camera, Terrain& terrain)
		: window(window),
		camera(camera),
		terrain(terrain)
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetKeyCallback(window, key_callback);
	}

	void processInput(float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.PositionMovement(deltaTime, FORWARD);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.PositionMovement(deltaTime, BACKWARD);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.PositionMovement(deltaTime, RIGHT);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.PositionMovement(deltaTime, LEFT);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.PositionMovement(deltaTime, UP);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.PositionMovement(deltaTime, DOWN);

	}

	bool GetPoint_Xplane(CubeStruct& it , float x)
	{
		moveVec = camera.cameraPos - camera.cameraPosLastFrame;
		float tz = (x - camera.cameraPosLastFrame.x) * moveVec.z / moveVec.x + camera.cameraPosLastFrame.z;
		float ty = (x - camera.cameraPosLastFrame.x) * moveVec.y / moveVec.x + camera.cameraPosLastFrame.y;
		if (tz <= it.BoxAxis.p_z && tz >= it.BoxAxis.n_z && ty <= it.BoxAxis.p_y && ty >= it.BoxAxis.n_y)
			return true;
		return false;
	}

	bool GetPoint_Zplane(CubeStruct& it, float z)
	{
		moveVec = camera.cameraPos - camera.cameraPosLastFrame;
		float tx = (z - camera.cameraPosLastFrame.z) * moveVec.x / moveVec.z + camera.cameraPosLastFrame.x;
		float ty = (z - camera.cameraPosLastFrame.z) * moveVec.y / moveVec.z + camera.cameraPosLastFrame.y;
		if (tx <= it.BoxAxis.p_x && tx >= it.BoxAxis.n_x && ty <= it.BoxAxis.p_y && ty >= it.BoxAxis.n_y)
			return true;
		return false;
	}

	void CheckCollider()
	{
		float reset;
		//玩家的碰撞体的盒坐标
		glm::vec3 st;
		for (auto it : terrain.CubeInfo)
		{
			if (Check_X_P(it) && GetPoint_Xplane(it, it.BoxAxis.n_x))
			{
				reset = it.BoxAxis.n_x - Collier_p_x;
				camera.cameraPos.x = reset;
			}
			if (Check_X_N(it) && GetPoint_Xplane(it, it.BoxAxis.p_x))
			{
				reset = it.BoxAxis.p_x + Collier_n_x;
				camera.cameraPos.x = reset;
			} 
			if (Check_Z_P(it) && GetPoint_Zplane(it, it.BoxAxis.n_z))
			{
				reset = it.BoxAxis.n_z - Collier_p_z;
				camera.cameraPos.z = reset;
			}
			if (Check_Z_N(it) && GetPoint_Zplane(it, it.BoxAxis.p_z))
			{
				reset = it.BoxAxis.p_z + Collier_n_z;
				camera.cameraPos.z = reset;
			}
		}
	}

	bool Check_X_P(CubeStruct& it)
	{
		//Check positive x
		if (camera.cameraPos.x + Collier_p_x > it.BoxAxis.n_x && camera.cameraPos.x < it.BoxAxis.p_x)
			if (fabs(camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y) && fabs(it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;
		return false;
	}

	bool Check_X_N(CubeStruct& it)
	{
		//Check negative x
		if (camera.cameraPos.x - Collier_n_x < it.BoxAxis.p_x && camera.cameraPos.x > it.BoxAxis.n_x)
			if (fabs(camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y) && fabs(it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;		
		return false;
	}

	bool Check_Z_P(CubeStruct& it)
	{
		//Check positive x
		if (camera.cameraPos.z + Collier_p_z > it.BoxAxis.n_z && camera.cameraPos.z < it.BoxAxis.p_z)
			if (fabs(camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y) && fabs(it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				if (fabs(it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
					return true;
		return false;
	}

	bool Check_Z_N(CubeStruct& it)
	{
		//Check negative x
		if (camera.cameraPos.z - Collier_n_z < it.BoxAxis.p_z && camera.cameraPos.z > it.BoxAxis.n_z)
			if (fabs(camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y) && fabs(it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				if (fabs(it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
					return true;
		return false;
	}
};