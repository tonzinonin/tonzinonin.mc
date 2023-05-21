#pragma once
#include "ves/Camera.h"
#include "CubeGameObject.h"

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 768

float fpositions[] =
{ 
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f

};


float skybox[] =
{
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

enum TerrainCubeType
{
    GRASS_BLOCK , DIRT
};
struct TerrainCube
{
    float x, y, z;
    TerrainCubeType type;
};

class Terrain
{
private:
    std::vector<TerrainCube> Cube;
	CubeGameObject grass_block;
    CubeGameObject dirt;
public:
	Terrain() : grass_block("res/texture/terrian/grass_block", "res/shader/basic.vert", "res/shader/basic.frag",fpositions,sizeof(fpositions)),
                dirt("res/texture/terrian/dirt", "res/shader/basic.vert", "res/shader/basic.frag", fpositions,sizeof(fpositions))
    {
        TerrainInit();
    }
    void TerrainInit()
    {
        for (float i = -5; i < 5; i+= 0.2)
        {
            for (float j = -5; j < 5; j+= 0.2)
            {
                float perlin = PerlinNoise(glm::vec2(i, j));
                float y = 0;
                while(1)
                {
                    if (y > perlin * 2 + 2)
                    {
                        Cube.push_back({i , y , j , GRASS_BLOCK});
                        break;
                    }
                    Cube.push_back({ i , y , j , DIRT});
                    y += 0.2f;
                }
            }
        }
    }

    void TerrainDraw(Camera& camera)
    {
        for (auto it : Cube)
        {
            if (it.type == DIRT) dirt.DrawCube(camera, glm::vec3(it.x , it.y , it.z));
            if (it.type == GRASS_BLOCK) grass_block.DrawCube(camera , glm::vec3(it.x, it.y, it.z));
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
        glm::vec2 pf = (p - pi) / glm::vec2(2 , 2);
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
        p = p * 2.f;
        f += 1.0000 * PerlinNoise(p); 
        p = p * 2.f;
        f += 0.5000 * PerlinNoise(p); 
        p = p * 2.f;
        f += 0.2500 * PerlinNoise(p); 
        p = p * 2.f;
        f += 0.1250 * PerlinNoise(p); 
        p = p * 2.f;
        f += 0.0625 * PerlinNoise(p); 
        p = p * 2.f;
        return f;
    }
};

class Sky
{
private:
    CubeGameObject Skybox;
public:
    Sky() : Skybox("res/texture/skybox", "res/shader/skybox.vert", "res/shader/skybox.frag", skybox , sizeof(skybox) , true)
    {
    }
    void SkyDraw(Camera& camera)
    {
        Skybox.DrawSkyBox(camera);
    }
};
