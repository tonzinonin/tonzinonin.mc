#pragma once
#include "UItemplate.h"

class Cursor : UI
{
public:
	Cursor() : UI("res/texture/UI/crosshair_alpha_1.png", "res/shader/cursor.vert", "res/shader/cursor.frag")
	{}
	void Draw()
	{
		this->UIbind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		this->UIunbind();
	}
};