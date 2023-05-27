
#pragma once
#include "ves/GameSetting/Shader.h"
#include "ves/GameSetting/VertexArray.h"
#include "ves/GameSetting/VertexBuffer.h"
#include "ves/GameSetting/VertexBufferLayout.h"
#include "ves/GameSetting/IndexBuffer.h"
#include "ves/Texture.h"

float cursor_vertices[] = 
{
	0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // top left 

	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};

class BoxFrame
{
private:
	Texture texture;
	VertexArray va;
	VertexBuffer vb;
	Shader shader;
	VertexBufferLayout layout;
public:
	BoxFrame()
	{
		this->texture.T_INIT("res/texture/UI/squareframe2.png", GL_RGBA);
		this->shader.S_INIT("res/shader/barBoxFrame.vert", "res/shader/barBoxFrame.frag");
		this->vb.VB_INIT(cursor_vertices, sizeof(cursor_vertices));

		this->layout.Push<float>(3);
		this->layout.Push<float>(2);
		this->va.AddBuffer(vb, layout);
	}
	void Draw()
	{
		this->texture.Bind();
		this->shader.Bind();

		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(0.12, 0.12, 1.0));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0., -0.5, 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		glUniform1i(glGetUniformLocation(shader.GetRendererID(), "index"), stuffIndex);

		this->va.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 8);
		texture.Unbind();
		shader.Unbind();
		va.Unbind();
	}
};

class ShortcutBar
{
private:
	Texture texture;
	VertexArray va;
	VertexBuffer vb;
	Shader shader;
	VertexBufferLayout layout;
	
	BoxFrame box;

public:
	ShortcutBar()
	{
		this->texture.T_INIT("res/texture/UI/bar2.png", GL_RGBA);
		this->shader.S_INIT("res/shader/UI.vert", "res/shader/UI.frag");
		this->vb.VB_INIT(cursor_vertices, sizeof(cursor_vertices));
		
		this->layout.Push<float>(3);
		this->layout.Push<float>(2);
		this->va.AddBuffer(vb, layout);
	}
	void Draw()
	{
		box.Draw();

		this->texture.Bind();
		this->shader.Bind(); 
		
		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(1, 0.12, 1.0));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0., -0.5, 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		this->va.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 8);
		texture.Unbind();
		shader.Unbind();
		va.Unbind();
	}
};
