#pragma once

#include "VertexArray.h"

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}