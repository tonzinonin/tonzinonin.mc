#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		//ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;

public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		// static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT , count , GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT , count , GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count , GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned int GetStride() const { return m_Stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
};