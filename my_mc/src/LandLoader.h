#pragma once
#include "ves/Camera.h"
#include "CubeGameObject.h"
#include <algorithm>

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 768

int checkout[105][105][105];

int dx[] = {1 , -1 , 0 , 0 , 0 , 0};
int dy[] = {0 , 0 , 1 , -1 , 0 , 0};
int dz[] = {0 , 0 , 0 , 0 , -1 , 1};
float mi = 0x3f3f3f3f;
float ma = -0x3f3f;

enum CubeType
{
    GRASS_BLOCK, DIRT, SKYBOX
};
struct BoxAxisStruct
{
    float p_x, p_y, p_z;
    float n_x, n_y, n_z;
    float Cubesizehalf = 0.5;
    const void GetAxis(float x , float y , float z)
    {
        p_x = x + Cubesizehalf;
        p_y = y + Cubesizehalf;
        p_z = z + Cubesizehalf;
        n_x = x - Cubesizehalf;
        n_y = y - Cubesizehalf;
        n_z = z - Cubesizehalf;

    }
};
struct CubeStruct
{
    glm::vec3 location;
    CubeType type;
    BoxAxisStruct BoxAxis;
};


class Terrain
{
private:

	CubeGameObject grass_block;
    CubeGameObject dirt;

public:

    std::vector<CubeStruct> CubeInfo;

	Terrain() : grass_block("res/texture/terrian/grass_block", "res/shader/basic.vert", "res/shader/basic.frag"),
                dirt("res/texture/terrian/dirt", "res/shader/basic.vert", "res/shader/basic.frag")
    {
        TerrainInit();
    }
    void TerrainInit()
    {
        //BoxAxisStruct tmp;
        //tmp.GetAxis(0, 0, 0);
        //CubeInfo.push_back({ glm::vec3(0.0f) , GRASS_BLOCK , tmp });
        for (int i = -40; i < 40; i += 1)
        {
            for (int j = -40; j < 40; j += 1)
            {
                float perlin = noise_sum(glm::vec2((float)i * 0.05, (float)j * 0.05));
                mi = std::min(mi, perlin);
                ma = std::max(ma, perlin);
                std::cout <<"noisevalue : "<< perlin << std::endl;
                int y = 0;
                while(1)
                {
                    if (y > perlin * 10 + 10)
                    {
                        BoxAxisStruct tmp;
                        tmp.GetAxis(i, y, j);
                        CubeInfo.push_back({ glm::vec3(i , y , j) , GRASS_BLOCK , tmp});
                        
                        for (int k = 0; k < 6; k++)
                        {
                            int lx = i + dx[k] + 51;
                            int ly = y + dy[k] + 51;
                            int lz = j + dz[k] + 51;
                            checkout[lx][ly][lz]++;
                        }
                        break;
                    }         

                    BoxAxisStruct tmp;
                    tmp.GetAxis(i, y, j);
                    CubeInfo.push_back({ glm::vec3(i , y , j) , DIRT , tmp});

                    for (int k = 0; k < 6; k++)
                    {
                        int lx = i + dx[k] + 51;
                        int ly = y + dy[k] + 51;
                        int lz = j + dz[k] + 51;
                        checkout[lx][ly][lz]++;
                    }
                    y += 1;
                }
            }
        }
        std::cout << "minvalue = " << mi << std::endl << "maxvalue = " << ma << std::endl;
    }

    void TerrainDraw(Camera& camera)
    {
        for (auto it : CubeInfo)
        {
            if (checkout[(int)it.location.x + 51][(int)it.location.y + 51][(int)it.location.z + 51] == 6) continue;
            if (it.type == DIRT) dirt.DrawCube(camera, it.location);
            if (it.type == GRASS_BLOCK) grass_block.DrawCube(camera , it.location);
        }
    }

    glm::vec2 hash22(glm::vec2 p)
    {
        p = glm::vec2(glm::dot(p, glm::vec2(127.1, 311.7)),
            glm::dot(p, glm::vec2(269.5, 183.3)));
        return glm::vec2(-1.0 + 2.0 * glm::fract(glm::sin(p.x) * 43758.543123),
            -1.0 + 2.0 * glm::fract(glm::sin(p.y) * 43758.543123));
    }

    float PerlinNoise(glm::vec2 p)
    {
        glm::vec2 pi = glm::floor(p);
        glm::vec2 pf = (p - pi);
        glm::vec2 w = glm::vec2(pf.x * pf.x * (3.0 - 2.0 * pf.x) ,
                                pf.y * pf.y * (3.0 - 2.0 * pf.y));

        return glm::mix(glm::mix(glm::dot(hash22(pi + glm::vec2(0.0, 0.0)), pf - glm::vec2(0.0, 0.0)),
            glm::dot(hash22(pi + glm::vec2(1.0, 0.0)), pf - glm::vec2(1.0, 0.0)), w.x),
            glm::mix(dot(hash22(pi + glm::vec2(0.0, 1.0)), pf - glm::vec2(0.0, 1.0)),
                glm::dot(hash22(pi + glm::vec2(1.0, 1.0)), pf - glm::vec2(1.0, 1.0)), w.x),
            w.y);
    }
    float noise_sum(glm::vec2 p)
    {
        float f = 0.0;
        //p = p * 2.f;
        f += 1.0000 * PerlinNoise(p); 
        //p = p * 2.f;
        //f += 0.5000 * PerlinNoise(p); 
        //p = p * 2.f;
        //f += 0.2500 * PerlinNoise(p); 
        //p = p * 2.f;
        //f += 0.1250 * PerlinNoise(p); 
        //p = p * 2.f;
        //f += 0.0625 * PerlinNoise(p); 
        return f;
    }
};

class Sky
{
private:
    SkyBoxObject Skybox;
public:
    Sky() : Skybox("res/texture/skybox", "res/shader/skybox.vert", "res/shader/skybox.frag")
    {
    }
    void SkyDraw(Camera& camera)
    {
        Skybox.DrawSkyBox(camera);
    }
};
