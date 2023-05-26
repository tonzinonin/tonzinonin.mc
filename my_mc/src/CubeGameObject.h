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

float positions[] =
{
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f

};


float skybox[] =
{
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

class CubeGameObject
{
private:

	void LoadBuffer()
	{
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
	}

protected:

	unsigned int cubemapTexture;
	Shader shader;
	VertexBuffer vb;
	VertexArray va;
	VertexBufferLayout layout;

	std::string face[6] = { "/right.png",
		"/left.png",
		"/top.png",
		"/bottom.png",
		"/front.png",
		"/back.png" };

	std::vector<std::string> faces;
public:
	CubeGameObject(std::string filepath, std::string shaderfilepath1, std::string shaderfilepath2, bool isSky = false)
	{
		shader.S_INIT(shaderfilepath1, shaderfilepath2);
		for (int i = 0; i < 6; i++)
		{
			faces.push_back(filepath + face[i]);
		}
		if (isSky == true) return;
		vb.VB_INIT(positions, sizeof(positions));
		cubemapTexture = LoadCubeTexture(faces, GL_RGBA);
		std::cout << "cubemapTexture:" << cubemapTexture << std::endl;
		LoadBuffer();
	}
	void DrawCube(Camera& camera , glm::vec3 translation)
	{
		shader.Bind();
		va.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation); 
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shader.Unbind();
		va.Unbind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	unsigned int LoadCubeTexture(std::vector<std::string> faces , GLint Renderer_type)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		unsigned char* data;
		stbi_set_flip_vertically_on_load(0);
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, Renderer_type , width, height, 0, Renderer_type , GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		return textureID;
	}
};

class SkyBoxObject : public CubeGameObject
{
private:
	void LoadSkyBuffer()
	{
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);
	}
public:

	SkyBoxObject(std::string filepath, std::string shaderfilepath1, std::string shaderfilepath2)
		: CubeGameObject(filepath, shaderfilepath1, shaderfilepath2, true)
	{
		vb.VB_INIT(skybox, sizeof(skybox));
		cubemapTexture = LoadCubeTexture(faces, GL_RGB);
		LoadSkyBuffer();
	}
	void DrawSkyBox(Camera& camera)
	{
		glDepthMask(GL_FALSE);
		shader.Bind();
		va.Bind();

		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
};