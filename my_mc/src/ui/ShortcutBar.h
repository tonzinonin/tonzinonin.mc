
#pragma once

#include "UItemplate.h"

class BoxFrame : UI
{
public:
	BoxFrame() : UI("res/texture/UI/squareframe2.png", "res/shader/barBoxFrame.vert", "res/shader/barBoxFrame.frag")
	{}
	void Draw()
	{
		this->UIbind();
		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(0.12, 0.12, 1.0));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0., -0.5, 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		glUniform1i(glGetUniformLocation(shader.GetRendererID(), "index"), stuffIndex);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		this->UIunbind();
	}
};

class ShortcutBar : UI
{
private:
	BoxFrame box;
public:
	ShortcutBar() : UI("res/texture/UI/bar2.png", "res/shader/UI.vert", "res/shader/UI.frag")
	{}
	void Draw()
	{
		box.Draw();

		this->UIbind();

		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(1, 0.12, 1.0));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0., -0.5, 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		this->UIunbind();
	}
};
