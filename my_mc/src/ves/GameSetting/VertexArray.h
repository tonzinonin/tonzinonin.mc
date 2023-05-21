#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout); 
};