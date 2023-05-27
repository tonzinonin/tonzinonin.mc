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
#include "ves/GameSetting/IndexBuffer.h"
#include "ves/Texture.h"

Camera camera;
int stuffIndex = 0;

#include "ui/ImgUI.h"
#include "LandLoader.h"
#include "Player.h"
#include "ui/Cursor.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080
int IMGUI_WIDTH = 600;
int IMGUI_HEIGHT = 300;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

std::string ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
	{
		ss << line << '\n';
	}
	return ss.str();
}

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
	glDepthFunc(GL_LESS);

	//glDepthFunc(GL_ALWAYS);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Cursor cursor;
	Terrain terrain;
	Sky sky;
	Player player(window, camera, terrain);
	OpenglImgui ui(window, camera, player, terrain);

	while (!glfwWindowShouldClose(window))
	{
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		camera.cameraPosLastFrame = camera.cameraPos;
		player.processInput(deltaTime);

		float timeValue = glfwGetTime();
		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.Physics(deltaTime);
		player.CheckCollider();

		cursor.Draw();
		sky.SkyDraw(camera);
		terrain.TerrainDraw(camera);
		ui.Draw(IMGUI_WIDTH, IMGUI_HEIGHT);

		glfwSwapBuffers(window);

		CubeSelectActive = false;
		CubePlaceActive = false; 
		CubeDestroyActive = false;

		glfwPollEvents();
	}

		glfwDestroyWindow(window);
	
	glfwTerminate();
	return 0;
}

