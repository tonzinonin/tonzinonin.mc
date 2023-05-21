#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/glew.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string v_FilePath;
	std::string f_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath1 , const std::string& filepath2);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int GetRendererID() const { return this->m_RendererID; }

private:
	ShaderProgramSource ParseShader(const std::string& filepath, const std::string& filepath2) const;
	unsigned int CompileShader(unsigned int type, const std::string& source); 
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};