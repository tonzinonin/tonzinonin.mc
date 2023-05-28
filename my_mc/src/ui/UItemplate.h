#pragma once

#include "../ves/GameSetting/Shader.h"
#include "../ves/GameSetting/VertexArray.h"
#include "../ves/GameSetting/VertexBuffer.h"
#include "../ves/GameSetting/VertexBufferLayout.h"
#include "../ves/GameSetting/IndexBuffer.h"
#include "../ves/Texture.h"


#include "../thr/glm/glm/glm.hpp"
#include "../thr/glm/glm/gtc/matrix_transform.hpp"

float texture_vertices[] =
{
	0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // top left 

	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};
class UI
{
protected:
	Texture texture;
	VertexArray va;
	VertexBuffer vb;
	Shader shader;
	VertexBufferLayout layout;
public:
	UI() = default;
	UI(std::string textureFilepath , std::string vertFilepath , std::string fragFilepath)
	{
		this->texture.T_INIT(textureFilepath , GL_RGBA);
		this->shader.S_INIT(vertFilepath, fragFilepath);
		this->vb.VB_INIT(texture_vertices, sizeof(texture_vertices));

		this->layout.Push<float>(3);
		this->layout.Push<float>(2);
		this->va.AddBuffer(vb, layout);
	}
	void UIbind()
	{
		this->texture.Bind();
		this->shader.Bind();
		this->va.Bind();
	}
	void UIunbind()
	{
		texture.Unbind();
		shader.Unbind();
		va.Unbind();
	}
};
