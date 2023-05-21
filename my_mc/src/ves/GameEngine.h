#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
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
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
public:
	VertexBufferLayout() : m_Stride(0)
	{}

	template<typename T>
	void Push(unsigned int count)
	{

	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT , count ,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT , count ,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count ,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline unsigned int GetStride() const { return m_Stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
};

class Shader 
{
private:
	unsigned int rendererID;
public:
	Shader(std::string path1, std::string path2) : rendererID(0)
	{
		std::string vsp = ParseShader(path1);
		std::string fsp = ParseShader(path2);
		const char* vs = vsp.c_str();
		const char* fs = fsp.c_str();
		rendererID = CompileShader(vs, fs);
	}
	~Shader()
	{
		glDeleteProgram(rendererID);
	}
	void Bind() const
	{
		glUseProgram(rendererID);
	}
	void Unbind() const
	{
		glUseProgram(0);
	}
	std::string ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::string line;
		std::stringstream ss;
		while (getline(stream, line))
		{
			ss << line << '\n';
		}
		return ss.str();
	}
	unsigned int CompileShader(const char* vs , const char* fs)
	{
		unsigned int vsid = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fsid = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vsid, 1, &vs, nullptr);
		glShaderSource(fsid, 1, &fs, nullptr);
		glCompileShader(vsid);
		glCompileShader(fsid);

		unsigned int program = glCreateProgram();
		glAttachShader(program, vsid);
		glAttachShader(program, fsid);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vsid);
		glDeleteShader(fsid);

		return program;
	}
};

class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray()
	{
		glGenVertexArrays(1 , &rendererID);
	}
	~VertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}
	void Bind()
	{
		glBindVertexArray(rendererID);
	}
	void Unbind()
	{
		glBindVertexArray(0);
	}
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();

		unsigned int offset = 0;
		const auto& elements = layout.GetElements();
		for (int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type , element.normalized, layout.GetStride(), (const void*)offset);

			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}
};
class VertexBuffer
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(const void* data , unsigned int size)
	{
		glGenBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size , data , GL_STATIC_DRAW);
	}
	~VertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}
	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}
	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count)
		: count(count)
	{
		sizeof(unsigned int) == sizeof(GLuint);//与跨平台有关

		glGenBuffers(1, &rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}

	~IndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}
	void Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	inline unsigned int GetCount() const { return count; }
};
