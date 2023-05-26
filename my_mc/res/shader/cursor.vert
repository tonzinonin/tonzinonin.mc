#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoords;

void main()
{
	TexCoords = texCoord;
	mat4 scale = 
	mat4(0.03 , 0.0 , 0.0 , 0.0,
		 0.0 , 0.03 , 0.0 , 0.0,
		 0.0 , 0.0 , 0.03 , 0.0,
		 0.0 , 0.0 , 0.0 , 1.0);
	gl_Position = scale * vec4(aPos , 1.0);
}