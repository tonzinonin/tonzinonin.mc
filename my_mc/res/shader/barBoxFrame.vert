#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 scale;
uniform int index;

void main()
{
	TexCoords = texCoord;
	mat4 xmodel =
			mat4
				(1., 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, -0.4,
				0.0, 0.0, 1.0, 0,
				0.0, 0.0, 0.0, 1.0);
	gl_Position = model * scale * vec4(aPos.x + index * 0.92, aPos.y , aPos.z , 1.0);
}
