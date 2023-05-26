#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D cursor;

void main()
{
	vec4 texColor = texture2D(cursor, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
	//FragColor = vec4(1.0 , 0 , 0 ,1.0);
}