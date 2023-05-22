#pragma once

#include "GL/glew.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	//VertexBuffer(){}
	//VertexBuffer(const void* data, unsigned int size)
	//{
	//	glGenBuffers(1, &m_RendererID);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//}
	void VB_INIT(const void* data, unsigned int size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};