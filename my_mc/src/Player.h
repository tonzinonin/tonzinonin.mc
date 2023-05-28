#pragma once

#include "ves/Camera.h"
#include "GL/glew.h"
#include "LandLoader.h"

#include "ui/Menu.h"
#include "ui/ShortcutBar.h"

#include <cmath>

bool isLook = true;
bool is_menu = false;
float cursor_pos_x;
float cursor_pos_y;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(!is_menu)
		camera.LookMovement(xpos, ypos);
	else
	{
		cursor_pos_x = xpos;
		cursor_pos_y = ypos;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ScrollMovement(xoffset, yoffset);
	stuffIndex += yoffset;
	if (stuffIndex < -4) stuffIndex = -4;
	if (stuffIndex > 4) stuffIndex = 4;
}

bool isPlace = false;
bool isDestroy = false;
bool isSelect = false;
bool isSwap = false;
bool isChange = false;

bool CubeSelectActive = false;
bool CubePlaceActive = false;
bool CubeDestroyActive = false;
bool CubeSwapActive = false;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (is_menu == false)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && isPlace == false)
		{
			CubePlaceActive = true;
			isPlace = true;
		}
		if (isPlace == true && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		{
			isPlace = false;
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && isPlace == false)
		{
			CubeDestroyActive = true;
			isDestroy = true;
		}
		if (isPlace == true && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			isDestroy = false;
		}
	}
	else if (is_menu == true)
	{
		if (isSwap == false)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && isSelect == false)
			{

				isSelect = true;
			}
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && isSelect == true)
			{
				isSelect = false;

				CubeSelectActive = true;

				isSwap = true;
			}
		}
		else if (isSwap == true)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && isChange == false)
			{

				isChange = true;
			}
			if (isChange == true && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
			{
				isChange = false;

				CubeSwapActive = true;

				isSwap = false;
			}
		}
	}
}

class Player
{
private:

	enum Ray_mode
	{
		DESTROY, GENERATE
	};
	enum face_check
	{
		FC_UP, FC_DOWN, FC_LEFT, FC_RIGHT, FC_FORWARD, FC_BACK, NONE
	};
	GLFWwindow*& window;
	Camera& camera;
	Terrain& terrain;
	
	Menu menu;
	ShortcutBar bar;

public:

	float Collier_p_x = 0.5;
	float Collier_p_y = 0.4;
	float Collier_p_z = 0.5;
	float Collier_n_x = 0.5;
	float Collier_n_y = 1.5;
	float Collier_n_z = 0.5;

	float DropSpeed = 0.f;
	float gravity = 15.f;
	float DROP_SPEED_MAX = 30.f;

	bool Jump_check = false;
	bool isJump = false;
	float JumpStartSpeed = 6.f;

	float CubeStride = 1.0f;

	bool menu_check = false;
	bool is_icon_track = false;

	CubeType cubeList[9];

	CubeType cubeSelectedType = TYPE_NONE;
	CubeType cubeSwapedType = TYPE_NONE;

	int menuPos_swap_id;

	Player(GLFWwindow*& window, Camera& camera, Terrain& terrain)
		: window(window),
		camera(camera),
		terrain(terrain)
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		cubeList[0] = GRASS_BLOCK;
		cubeList[1] = DIRT;
		cubeList[2] = DIAMOND;
		cubeList[3] = OAK_LOG;
		cubeList[4] = OAK_PLANKS;
		cubeList[5] = SANDSTONE;
		cubeList[6] = STONE;
		cubeList[7] = TNT;
		cubeList[8] = WHITE_WOOL;

	}

	void Physics(float& deltaTime)
	{
		//DropCheck(deltaTime);
		//if (isJump) JumpCheck(deltaTime);
		if (CubePlaceActive && cubeList[stuffIndex] != TYPE_NONE) RayCheckCube(GENERATE);
		if (CubeDestroyActive) RayCheckCube(DESTROY);

		if (is_menu)
		{
			if (CubeSelectActive)
			{
				std::cout << "check!" << std::endl;
				std::cout << "cursor_pos : " << cursor_pos_x << ' ' << cursor_pos_y << std::endl;
				std::cout << "screen : " << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << std::endl;

				cubeSelectedType = MenuPressCheck();
				if (cubeSelectedType == TYPE_NONE) isSwap = false;
				is_icon_track = true;
			}
			if (CubeSwapActive)
			{
				is_icon_track = false;
				menuPos_swap_id = MenuListPressCheck();
				if (menuPos_swap_id != -1)
				{
					cubeList[menuPos_swap_id] = cubeSelectedType;
					cubeSelectedType = TYPE_NONE;
				}
			}
			if (is_icon_track == true && cubeSelectedType != TYPE_NONE)
			{
				float sx = (cursor_pos_x / SCREEN_WIDTH - 0.5) * 2;
				float sy = ( - cursor_pos_y / SCREEN_HEIGHT + 0.5) * 2;
				menu.DrawIcon(cubeSelectedType, sx * SCREEN_WIDTH / SCREEN_HEIGHT , sy);
			}
			menu.DrawAll(); 
			DrawListInMenu();
			menu.Draw();
		}
		else
		{
			DrawList();
			bar.Draw();
		}
	}

	unsigned int MenuListPressCheck()
	{
		float box_stride = 27;
		int j;
		bool isNone = true;
		for (j = 0; j < 9; j++)
		{
			float locationx = SCREEN_WIDTH / 2;
			float locationy = SCREEN_HEIGHT / 2;

			locationx = locationx - 230 + j * 57.25;
			locationy = locationy + 169;

			std::cout << "x:" << locationx << " y:" << locationy << std::endl;

			int right = locationx + box_stride;
			int left = locationx - box_stride;
			int up = locationy + box_stride;
			int down = locationy - box_stride;

			if (cursor_pos_x < right && cursor_pos_x > left
				&& cursor_pos_y < up && cursor_pos_y > down)
			{
				isNone = false;
				break;
			}
		}
		if (isNone) return -1;
		return j;
	}

	CubeType MenuPressCheck()
	{
		CubeType ans_type = TYPE_NONE;
		float box_stride = 27;
		float locationx;
		float locationy;
		bool isbreak = false;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				float locationx = SCREEN_WIDTH / 2;
				float locationy = SCREEN_HEIGHT / 2;

				locationx = locationx - 230 + j * 57.25;
				locationy = locationy - 132 + i * 57.75;

				int right = locationx + box_stride;
				int left = locationx - box_stride;
				int up = locationy + box_stride;
				int down = locationy - box_stride;

				if (cursor_pos_x < right && cursor_pos_x > left
					&& cursor_pos_y < up && cursor_pos_y > down)
				{
					ans_type = menu.pack_icon_map[i][j];
					isbreak = true;
					break;
					//TODO
				}
			}
			if (isbreak) break;
		}
		return ans_type;
	}

	void DrawList()
	{
		for (int i = 0; i < 9; i++)
		{
			menu.DrawIcon(cubeList[i], float(i) * 0.11 - 0.44, -0.5);
		}
	}
	void DrawListInMenu()
	{
		for (int i = 0; i < 9; i++)
		{
			menu.DrawIcon(cubeList[i], float(i) * 0.107 - 0.428, -0.31);
		}
	}
	void DropCheck(float deltaTime)
	{
		if (Jump_check == false)
		{
			camera.cameraPos.y -= DropSpeed * deltaTime;
			if (DropSpeed < DROP_SPEED_MAX) DropSpeed = DropSpeed + gravity * deltaTime;
		}
		else
		{
			DropSpeed = 0.0;
			camera.cameraPos.y -= DropSpeed * deltaTime;
		}
	}

	void JumpCheck(float deltaTime)
	{
		camera.cameraPos.y += JumpStartSpeed * deltaTime;
	}

	void processInput(float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.PositionMovement(deltaTime, FORWARD);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.PositionMovement(deltaTime, BACKWARD);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.PositionMovement(deltaTime, RIGHT);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.PositionMovement(deltaTime, LEFT);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camera.PositionMovement(deltaTime, UP);		

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && menu_check == false)
		{
			menu_check = true;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && menu_check == true)
		{
			menu_check = false;
			if (is_menu == false)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				is_menu = true;
			}
			else if (is_menu == true) 
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				is_menu = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && Jump_check == true)
		{
			isJump = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.PositionMovement(deltaTime, DOWN);
	}

	float _equation(float A, float B, float C, float D, float& x, float& y, float& z)
	{
		float x1 = camera.cameraPos.x;
		float x0 = camera.cameraPosLastFrame.x;
		float vx = x1 - x0;

		float y1 = camera.cameraPos.y;
		float y0 = camera.cameraPosLastFrame.y;
		float vy = y1 - y0;

		float z1 = camera.cameraPos.z;
		float z0 = camera.cameraPosLastFrame.z;
		float vz = z1 - z0;

		float t = -(A * x0 + B * y0 + C * z0 + D) / (A * vx + B * vy + C * vz);

		x = x0 + t * vx;
		y = y0 + t * vy;
		z = z0 + t * vz;

		float dist = (x - x0) * (x - x0) + (y - y0) * (y - y0) + (z - z0) * (z - z0);

		return dist;
	}

	float r_equation(float A, float B, float C, float D, float& x, float& y, float& z)
	{
		float x1 = camera.cameraPos.x + camera.cameraFront.x;
		float x0 = camera.cameraPos.x;
		float vx = x1 - x0;

		float y1 = camera.cameraPos.y + camera.cameraFront.y;
		float y0 = camera.cameraPos.y;
		float vy = y1 - y0;

		float z1 = camera.cameraPos.z + camera.cameraFront.z;
		float z0 = camera.cameraPos.z;
		float vz = z1 - z0;

		float t = -(A * x0 + B * y0 + C * z0 + D) / (A * vx + B * vy + C * vz);

		x = x0 + t * vx;
		y = y0 + t * vy;
		z = z0 + t * vz;

		float dist = (x - x0) * (x - x0) + (y - y0) * (y - y0) + (z - z0) * (z - z0);
		
		float v1px = x - camera.cameraPos.x;
		float v2px = camera.cameraFront.x;
		if (v1px * v2px < 0) return 0x3f3f3f3f;
		return dist;
	}

	void RayCheckCube(Ray_mode raymode)
	{
		float dist_r = 0x3f3f3f3f;
		CubeStruct cubestruct_r;
		std::vector<CubeStruct>::iterator cubePosition;
		face_check face_r = NONE;

		for (auto it = terrain.CubeInfo.begin() ; it != terrain.CubeInfo.end() ; it++)
		{
			float dist = dist_r;
			face_check face = NONE;
			float x, y, z;
			float tmp = r_equation(1, 0, 0, -(it -> BoxAxis.n_x), x, y, z);//n
			if (y < it -> BoxAxis.p_y
				&& y > it -> BoxAxis.n_y
				&& z < it -> BoxAxis.p_z
				&& z > it -> BoxAxis.n_z
				&& tmp < dist)
			{
				face = FC_LEFT;
				dist = tmp;
			}
			tmp = r_equation(1, 0, 0, -(it -> BoxAxis.p_x), x, y, z);//p
			if (y < it -> BoxAxis.p_y
				&& y > it -> BoxAxis.n_y
				&& z < it -> BoxAxis.p_z
				&& z > it -> BoxAxis.n_z
				&& tmp < dist)
			{
				face = FC_RIGHT;
				dist = tmp;
			}
			tmp = r_equation(0, 1, 0, -(it -> BoxAxis.n_y), x, y, z);
			if (x < it -> BoxAxis.p_x
				&& x > it -> BoxAxis.n_x
				&& z < it -> BoxAxis.p_z
				&& z > it -> BoxAxis.n_z
				&& tmp < dist)
			{
				face = FC_UP;
				dist = tmp;
			}
			tmp = r_equation(0, 1, 0, -(it -> BoxAxis.p_y), x, y, z);
			if (x < it -> BoxAxis.p_x
				&& x > it -> BoxAxis.n_x
				&& z < it -> BoxAxis.p_z
				&& z > it -> BoxAxis.n_z
				&& tmp < dist)
			{
				face = FC_DOWN;
				dist = tmp;
			}
			tmp = r_equation(0, 0, 1, -(it -> BoxAxis.n_z), x, y, z);
			if (y < it -> BoxAxis.p_y
				&& y > it -> BoxAxis.n_y
				&& x < it -> BoxAxis.p_x
				&& x > it -> BoxAxis.n_x
				&& tmp < dist)
			{
				face = FC_FORWARD;
				dist = tmp;
			}
			tmp = r_equation(0, 0, 1, -(it -> BoxAxis.p_z), x, y, z);
			if (y < it -> BoxAxis.p_y
				&& y > it -> BoxAxis.n_y
				&& x < it -> BoxAxis.p_x
				&& x > it -> BoxAxis.n_x
				&& tmp < dist)
			{
				face = FC_BACK;
				dist = tmp;
			}

			if (face == NONE) continue;
			else
			{
				dist_r = dist;
				face_r = face;
				cubestruct_r = *it;
				cubePosition = it;
			}
		}

		if (face_r == NONE) return;

		else switch (raymode)
		{
		case (DESTROY):
		{
			std::cout << "destory!" << std::endl;
			DestroyCube(cubePosition);
			break;
		}
		case (GENERATE):
		{
			std::cout << "place!" << std::endl;
			PlaceCube(face_r, cubestruct_r);
			break;
		}
		default:
			break;
		}
	}
	void DestroyCube(std::vector<CubeStruct>::iterator it)
	{
		checkout[(int)(it->location.x) + 11][(int)(it->location.y) + 11][(int)(it->location.z) + 11]--;
		terrain.CubeInfo.erase(it);
	}
	void PlaceCube(face_check& face_r , CubeStruct cubestruct_r)
	{
		std::cout << stuffIndex << std::endl;
		CubeType type;
		switch (stuffIndex)
		{
		case -4: type = cubeList[0]; std::cout << -4 << std::endl; break;
		case -3: type = cubeList[1]; std::cout << -3 << std::endl; break;
		case -2: type = cubeList[2]; std::cout << -2 << std::endl; break;
		case -1: type = cubeList[3]; std::cout << -1 << std::endl; break;
		case 0: type = cubeList[4]; std::cout << 0 << std::endl; break;
		case 1: type = cubeList[5]; std::cout << 1 << std::endl; break;
		case 2: type = cubeList[6]; std::cout << 2 << std::endl; break;
		case 3: type = cubeList[7]; std::cout << 3 << std::endl; break;
		case 4: type = cubeList[8]; std::cout << 4 << std::endl; break;
		}
		switch (face_r)
		{
		case(NONE):break;
		case(FC_LEFT): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x - CubeStride, cubestruct_r.location.y, cubestruct_r.location.z);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully left: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		case(FC_RIGHT): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x + CubeStride, cubestruct_r.location.y, cubestruct_r.location.z);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully right: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		case(FC_UP): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x, cubestruct_r.location.y - CubeStride, cubestruct_r.location.z);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully up: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		case(FC_DOWN): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x, cubestruct_r.location.y + CubeStride, cubestruct_r.location.z);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully down: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		case(FC_FORWARD): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x, cubestruct_r.location.y, cubestruct_r.location.z - CubeStride);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully forward: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		case(FC_BACK): {
			BoxAxisStruct ttmp;
			glm::vec3 res = glm::vec3(cubestruct_r.location.x, cubestruct_r.location.y, cubestruct_r.location.z + CubeStride);
			if (checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]) break;

			checkout[int(res.x) + 11][int(res.y) + 11][int(res.z) + 11]++;
			ttmp.GetAxis(res.x, res.y, res.z);
			terrain.CubeInfo.push_back({ res , type , ttmp });
			std::cout << "PlaceSuccessfully back: " << res.x << ' ' << res.y << ' ' << res.z << std::endl;
			break;
		};
		}
	}

	void CheckCollider()
	{
		glm::vec3 reset = camera.cameraPos;
		//玩家的碰撞体的盒坐标

		Jump_check = false;
		face_check check = NONE;
		float fx, fy, fz;

		for (CubeStruct it : terrain.CubeInfo)
		{
			float min_dist = 0x3f3f3f3f;
			if (Check_X_P(it))
			{
				float x = it.BoxAxis.n_x - Collier_p_x;
				float tmp = _equation(1, 0, 0, -x, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.x = x;
					check = FC_LEFT;
				}
			}

			if (Check_X_N(it))
			{
				float x = it.BoxAxis.p_x + Collier_n_x;
				float tmp = _equation(1, 0, 0, -x, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.x = x;
					check = FC_RIGHT;
				}
			} 

			if (Check_Z_P(it))
			{
				float z = it.BoxAxis.n_z - Collier_p_z;
				float tmp = _equation(0, 0, 1, -z, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.z = z;
					check = FC_FORWARD;
				}
			}
			
			if (Check_Z_N(it))
			{
				float z = it.BoxAxis.p_z + Collier_n_z;
				float tmp = _equation(0, 0, 1, -z, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.z = z;
					check = FC_BACK;
				}
			}

			if (Check_Y_P(it))
			{
				float y = it.BoxAxis.n_y - Collier_p_y;
				float tmp = _equation(0, 1, 0, -y, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.y = y;
					check = FC_DOWN;
				}
			}

			if (Check_Y_N(it))
			{
				float y = it.BoxAxis.p_y + Collier_n_y;
				float tmp = _equation(0, 1, 0, -y, fx, fy, fz);
				if (min_dist > tmp)
				{
					min_dist = tmp;
					reset = camera.cameraPos;
					reset.y = y;
					check = FC_UP;
				}
			}
			if (check == NONE)
			{
				continue;
			}
			else
			{
				if (check == FC_UP)
				{
					Jump_check = true;
					isJump = false;
				}
				camera.cameraPos = reset;
			}
		}
	}

	bool Check_X_P(CubeStruct& it)
	{
		//Check positive x
		if (camera.cameraPos.x + Collier_p_x > it.BoxAxis.n_x && camera.cameraPos.x < it.BoxAxis.p_x)
			if (((camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				&& ((it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_p_y)))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;
		return false;
	}

	bool Check_X_N(CubeStruct& it)
	{
		//Check negative x
		if (camera.cameraPos.x - Collier_n_x < it.BoxAxis.p_x && camera.cameraPos.x > it.BoxAxis.n_x)
			if (((camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				&& ((it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_p_y)))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;
		return false;
	}

	bool Check_Z_P(CubeStruct& it)
	{
		//Check positive z
		if (camera.cameraPos.z + Collier_p_z > it.BoxAxis.n_z && camera.cameraPos.z < it.BoxAxis.p_z)
			if (((camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				&& ((it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_p_y)))
				if (fabs(it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
					return true;
		return false;
	}

	bool Check_Z_N(CubeStruct& it)
	{
		//Check negative z
		if (camera.cameraPos.z - Collier_n_z < it.BoxAxis.p_z && camera.cameraPos.z > it.BoxAxis.n_z)
			if (((camera.cameraPos.y - it.location.y) < (it.BoxAxis.Cubesizehalf + Collier_n_y))
				&& ((it.location.y - camera.cameraPos.y) < (it.BoxAxis.Cubesizehalf + Collier_p_y)))
				if (fabs(it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
					return true;
		return false;
	}

	bool Check_Y_P(CubeStruct& it)
	{
		//Check positive y
		if (camera.cameraPos.y + Collier_p_y > it.BoxAxis.n_y && camera.cameraPos.y < it.BoxAxis.p_y)
			if (((camera.cameraPos.x - it.location.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
				&& ((it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_p_x)))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;
		return false;
	}

	bool Check_Y_N(CubeStruct& it)
	{
		//Check positive y
		if (camera.cameraPos.y - Collier_n_y < it.BoxAxis.p_y && camera.cameraPos.y > it.BoxAxis.n_y)
			if (((camera.cameraPos.x - it.location.x) < (it.BoxAxis.Cubesizehalf + Collier_n_x))
				&& ((it.location.x - camera.cameraPos.x) < (it.BoxAxis.Cubesizehalf + Collier_p_x)))
				if (fabs(it.location.z - camera.cameraPos.z) < (it.BoxAxis.Cubesizehalf + Collier_n_z))
					return true;
		return false;
	}
};