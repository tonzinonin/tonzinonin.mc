#pragma once

#include "Shader.h"

Shader::Shader(const std::string& filepath1 , const std::string& filepath2)
{
	v_FilePath = filepath1;
	f_FilePath = filepath1;
	m_RendererID = 0;
	const ShaderProgramSource source = ParseShader(filepath1 , filepath2);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	//std::cout << "2:" << m_RendererID << std::endl;
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath1 , const std::string& filepath2) const
{
	std::ifstream vstream(filepath1);
	std::ifstream fstream(filepath2);

	std::string line;
	std::stringstream ss[2];

	while (getline(vstream, line))//一行一行地浏览文件
	{
		ss[0] << line << '\n';
	}	
	while (getline(fstream, line))//一行一行地浏览文件
	{
		ss[1] << line << '\n';
	}
	return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
