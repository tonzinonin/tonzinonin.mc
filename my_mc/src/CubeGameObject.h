#pragma once

//#include "ves/GameEngine.h"
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

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 768

unsigned int LoadCubeTexture(std::vector<std::string> faces);
unsigned int LoadSkyCubeTexture(std::vector<std::string> faces);

class CubeGameObject
{
private:
	//glm::vec3 location;
	Shader shader;
	VertexBuffer vb;

public:

	unsigned int cubemapTexture;
	VertexArray va;
	VertexBufferLayout layout;
	std::string face[6] = {"/right.png",
		"/left.png",
		"/top.png",
		"/bottom.png",
		"/front.png",
		"/back.png" };

	CubeGameObject(std::string filepath, std::string shaderfilepath1, std::string shaderfilepath2, float* positions, float size, bool isky = false) :
		shader(shaderfilepath1, shaderfilepath2),
		vb(positions, size)
	{
		std::vector<std::string> faces;
		for (int i = 0; i < 6; i++)
		{
			faces.push_back(filepath + face[i]);
		}
		if (isky)
		{
			cubemapTexture = LoadSkyCubeTexture(faces);
			LoadSkyBuffer();
		}
		else
		{
			cubemapTexture = LoadCubeTexture(faces);
			LoadBuffer();
		}
	}
	void LoadBuffer()
	{
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
	}
	void LoadSkyBuffer()
	{
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);
	}
	void DrawCube(Camera& camera , glm::vec3 translation)
	{
		shader.Bind();
		va.Bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation); 
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void DrawSkyBox(Camera& camera)
	{
		shader.Bind();
		va.Bind();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};
unsigned int LoadCubeTexture(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

unsigned int LoadSkyCubeTexture(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}