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


Camera camera;

#include "UI.h"
#include "LandLoader.h"
#include "Player.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080
int IMGUI_WIDTH = 600;
int IMGUI_HEIGHT = 300;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

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

	glEnable(GL_DEPTH_TEST); 
	//glDepthFunc(GL_LESS);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Terrain terrain;
	Sky sky;
	Player player(window , camera , terrain);
	OpenglImgui ui(window , camera, player);

	while (!glfwWindowShouldClose(window))
	{
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		camera.cameraPosLastFrame = camera.cameraPos;
		player.processInput(deltaTime);

		float timeValue = glfwGetTime();
		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.Physics(deltaTime);
		player.CheckCollider();
		sky.SkyDraw(camera);
		terrain.TerrainDraw(camera);
		ui.Draw(IMGUI_WIDTH, IMGUI_HEIGHT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

