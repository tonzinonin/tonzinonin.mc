#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube cursor;

void main()
{
	FragColor = texture(cursor , TexCoords);
}