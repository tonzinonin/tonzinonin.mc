#pragma once
#include "ves/GameSetting/Shader.h"
#include "ves/GameSetting/VertexArray.h"
#include "ves/GameSetting/VertexBuffer.h"
#include "ves/GameSetting/VertexBufferLayout.h"
#include "ves/GameSetting/IndexBuffer.h"
#include "ves/Texture.h"

float cursor_vertices[] = {
	0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // top left 

	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 


	//0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	//0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	//-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};
unsigned int indices[] =
{
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};
class Cursor
{
private:
	Texture texture;
	IndexBuffer ib;
	VertexArray va;
	VertexBuffer vb;
	Shader shader;
	VertexBufferLayout layout;
public:
	Cursor()
	{
		this -> texture.T_INIT("res/texture/UI/crosshair_alpha_1.png" , GL_RGBA);
		this -> shader.S_INIT("res/shader/cursor.vert", "res/shader/cursor.frag");
		//this -> ib.ID_INIT(indices, sizeof(indices));
		this -> vb.VB_INIT(cursor_vertices, sizeof(cursor_vertices));

		this -> layout.Push<float>(3);
		this -> layout.Push<float>(2);
		this -> va.AddBuffer(vb , layout);
		glUniform1i(glGetUniformLocation(shader.GetRendererID(), "texture1"), 0);
	}
	void Draw()
	{
		//glBindTexture(GL_TEXTURE_2D, texture.GetRendererID());
		this -> texture.Bind();
		this -> shader.Bind();
		this -> va.Bind();
		//glDepthMask(GL_FALSE);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 8);
		texture.Unbind();
		shader.Unbind();
		va.Unbind();
		//glDepthMask(GL_TRUE);
	}
};