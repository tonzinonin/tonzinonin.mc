#pragma once
#pragma once

#include "thr/imgui/imgui.h"
#include "thr/imgui/imgui_impl_glfw.h"
#include "thr/imgui/imgui_impl_opengl3.h"

#include "ves/Camera.h"

class OpenglImgui
{
private:
	Camera& camera;
public:

	OpenglImgui(GLFWwindow* window , Camera& camera) : camera(camera)
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
		const char* glsl_version = "#version 330";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
	void ShowPositionInformation()
	{
		ImGui::Text("camera position: x = %.3f , y = %.3f , z = %.3f\n", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
		ImGui::Text("fabs(it.location.y - camera.cameraPos.y) = %.3f : 0.9", 0 - camera.cameraPos.y);
		//ImGui::Text("camera.cameraPos.y - it.location.y = %.3f : 2", camera.cameraPos.y);

		ImGui::Text("fabs(it.location.z - camera.cameraPos.z) = %.3f : 1", 0 - camera.cameraPos.z);
		//ImGui::Text("camera.cameraPos.z - it.location.z = %.3f : 1", camera.cameraPos.z);
		ImGui::Text("camera.cameraPos.x - Collier_n_x = %.3f : 0.5", camera.cameraPos.x - 0.5);

	}
	void Draw(unsigned int IMGUI_WIDTH, unsigned int IMGUI_HEIGHT)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("ImGui");
			ShowPositionInformation();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Press R to enable/unenable cursor in window");
			ImGui::SetWindowSize(ImVec2(IMGUI_WIDTH, IMGUI_HEIGHT));
			ImGui::End();
		}
		//// ´´½¨ GUI ÔªËØ
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	~OpenglImgui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};