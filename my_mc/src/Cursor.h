#pragma once
#include "ves/GameSetting/Shader.h"
#include "ves/GameSetting/VertexArray.h"
#include "ves/GameSetting/VertexBuffer.h"
#include "ves/GameSetting/VertexBufferLayout.h"
#include "ves/GameSetting/IndexBuffer.h"
#include "ves/Texture.h"

float bar_vertices[] = {
	0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // top left 

	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom righ
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 

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
		this -> vb.VB_INIT(bar_vertices, sizeof(bar_vertices));

		this -> layout.Push<float>(3);
		this -> layout.Push<float>(2);
		this -> va.AddBuffer(vb , layout);
		glUniform1i(glGetUniformLocation(shader.GetRendererID(), "texture1"), 0);
	}
	void Draw()
	{
		this -> texture.Bind();
		this -> shader.Bind();
		this -> va.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 8);
		texture.Unbind();
		shader.Unbind();
		va.Unbind();
	}
};