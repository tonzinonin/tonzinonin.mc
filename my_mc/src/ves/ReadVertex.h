#pragma once

#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class VertexUnion
{
private:
	std::string  Path;
	std::vector<float> vertexArr;
public:
	void LoadVertexUnion(const std::string path)
	{
		Path = path;
		std::ifstream file(path);
		std::string line;
		unsigned int i = 1;
		while(getline(file , line))
		{
			std::cout << i++ << std::endl;
			if (line.empty())
			{
				continue;
			}
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ','))
			{
				vertexArr.push_back(std::stof(token));
			}
		}
	}
	inline unsigned int GetCount() const { return vertexArr.size(); }
	void value(float *arr) const
	{
		int index = 0;
		for (auto it : vertexArr)
		{
			arr[index++] = it;
		}
	}
};