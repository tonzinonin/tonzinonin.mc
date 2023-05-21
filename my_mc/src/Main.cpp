#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <vector>
#include "thr/stb_image/stb_image.h"
#include "thr/glm/glm/glm.hpp"
#include "thr/glm/glm/gtc/matrix_transform.hpp"

#include "ves/Camera.h"

#include "ves/GameSetting/Shader.h"
#include "ves/ReadVertex.h"
#include "ves/GameSetting/VertexArray.h"
#include "ves/GameSetting/VertexBuffer.h"
#include "ves/GameSetting/VertexBufferLayout.h"

#include "LandLoader.h"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080

float mixValue = 0.2;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
bool isMouse = false;

Camera camera;

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "minecraft", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//GLCall(glEnable(GL_BLEND))
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))//开启混合
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Terrain terrain;
	Sky sky;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		float timeValue = glfwGetTime();
		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);
		sky.SkyDraw(camera);
		glDepthMask(GL_TRUE);
		terrain.TerrainDraw(camera);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01;
		if (mixValue >= 1.00) mixValue = 1.00;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01;
		if (mixValue <= 0.00) mixValue = 0.00;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.PositionMovement(deltaTime, FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.PositionMovement(deltaTime, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.PositionMovement(deltaTime, RIGHT);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.PositionMovement(deltaTime, LEFT);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) { camera.LookMovement(xpos, ypos); }

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { camera.ScrollMovement(xoffset, yoffset); }

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