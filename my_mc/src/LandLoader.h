#pragma once
#include "ves/Camera.h"
#include "CubeGameObject.h"
#include <algorithm>

int checkout[105][105][105];

int dx[] = {1 , -1 , 0 , 0 , 0 , 0};
int dy[] = {0 , 0 , 1 , -1 , 0 , 0};
int dz[] = {0 , 0 , 0 , 0 , -1 , 1};
float mi = 0x3f3f3f3f;
float ma = -0x3f3f;

enum CubeType
{
    GRASS_BLOCK,
    DIRT,
    DIAMOND,
    OAK_LOG,
    OAK_PLANKS,
    SANDSTONE,
    STONE,
    TNT,
    WHITE_WOOL,
    SKYBOX,

    BEDROCK,
    BIRCH_PLANKS,
    BIRCH_LOG,
    BLOCK_OF_DIAMOND,
    BLACK_WOOL,
    BLOCK_OF_GOLD,
    BLOCK_OF_EMERAL,
    BLOCK_OF_LAPIS,
    BLOCK_OF_IRON,

    BLOCK_OF_QUARTZ,
    BLOCK_OF_REDSTONE,
    BOOKSHELF,
    BRICKS,
    CARVED_PUMPKIN,
    COAL_ORE,
    CRAFTING_TABLE,
    EMERALD_ORE,
    FURNACE,

    GLASS,
    GLOWSTONE,
    GOLD_ORE,
    HAY_BALE,
    ICE,
    IRON_ORE,
    LAPIS_LAZULI_ORE,
    LIGHT_BLUE_WOOL,
    LIME_WOOL,

    MAGENTA_WOOL,
    ORANGE_WOOL,
    PINK_WOOL,
    RED_WOOL,
    YELLOW_WOOL,
    MELON,
    REDSTONE_ORE,
    SAND,
    STONE_BRICKS,

    TYPE_NONE
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
    CubeGameObject diamond;
    CubeGameObject oak_log;
    CubeGameObject oak_planks;
    CubeGameObject sandstone;
    CubeGameObject stone;
    CubeGameObject tnt;
    CubeGameObject white_wool;

    CubeGameObject bedrock;
    CubeGameObject birch_planks;
    CubeGameObject birch_log;
    CubeGameObject block_of_diamond;
    CubeGameObject black_wool;
    CubeGameObject block_of_gold;
    CubeGameObject block_of_emerald;
    CubeGameObject block_of_lapis;
    CubeGameObject block_of_iron;

    CubeGameObject block_of_quartz;
    CubeGameObject block_of_redstone;
    CubeGameObject bookshelf;
    CubeGameObject bricks;
    CubeGameObject carved_pumpkin;
    CubeGameObject coal_ore;
    CubeGameObject crafting_table;
    CubeGameObject emerald_ore;
    CubeGameObject furnace;

    CubeGameObject glass;
    CubeGameObject glowstone;
    CubeGameObject gold_ore;
    CubeGameObject hay_bale;
    CubeGameObject ice;
    CubeGameObject iron_ore;
    CubeGameObject lapis_lazuli_ore;
    CubeGameObject light_blue_wool;
    CubeGameObject lime_wool;

    CubeGameObject magenta_wool;
    CubeGameObject orange_wool;
    CubeGameObject pink_wool;
    CubeGameObject red_wool;
    CubeGameObject yellow_wool;
    CubeGameObject melon;
    CubeGameObject redstone_ore;
    CubeGameObject sand;
    CubeGameObject stone_bricks;
public:

    std::vector<CubeStruct> CubeInfo;
    std::vector<CubeStruct> VisbleCubeInfo;

	Terrain() : grass_block("res/texture/terrian/grass_block", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGBA),
                dirt("res/texture/terrian/dirt", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGBA),
                diamond("res/texture/terrian/diamond", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGB),
                oak_log("res/texture/terrian/oak_log", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGB),
                oak_planks("res/texture/terrian/oak_planks", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGB),
                sandstone("res/texture/terrian/sandstone", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGB),
                stone("res/texture/terrian/stone", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGB),
                tnt("res/texture/terrian/tnt", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGB),
                white_wool("res/texture/terrian/white_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGB),
    
                bedrock("res/texture/terrian/bedrock", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                birch_planks("res/texture/terrian/birch_planks", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                birch_log("res/texture/terrian/birch_log", "res/shader/basic.vert", "res/shader/basic.frag",GL_RGBA),
                block_of_diamond("res/texture/terrian/block_of_diamond", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                black_wool("res/texture/terrian/black_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                block_of_gold("res/texture/terrian/block_of_gold", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                block_of_emerald("res/texture/terrian/block_of_emerald", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                block_of_lapis("res/texture/terrian/block_of_lapis", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                block_of_iron("res/texture/terrian/block_of_iron", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),

                block_of_quartz("res/texture/terrian/block_of_quartz", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                block_of_redstone("res/texture/terrian/block_of_redstone", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                bookshelf("res/texture/terrian/bookshelf", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                bricks("res/texture/terrian/bricks", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                carved_pumpkin("res/texture/terrian/carved_pumpkin", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                coal_ore("res/texture/terrian/coal_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                crafting_table("res/texture/terrian/crafting_table", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                emerald_ore("res/texture/terrian/emerald_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                furnace("res/texture/terrian/furnace", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),

                glass("res/texture/terrian/glass", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                glowstone("res/texture/terrian/glowstone", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                gold_ore("res/texture/terrian/gold_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                hay_bale("res/texture/terrian/hay_bale", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                ice("res/texture/terrian/ice", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                iron_ore("res/texture/terrian/iron_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                lapis_lazuli_ore("res/texture/terrian/lapis_lazuli_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                light_blue_wool("res/texture/terrian/light_blue_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                lime_wool("res/texture/terrian/lime_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),

                magenta_wool("res/texture/terrian/magenta_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                orange_wool("res/texture/terrian/orange_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                pink_wool("res/texture/terrian/pink_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                red_wool("res/texture/terrian/red_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                yellow_wool("res/texture/terrian/yellow_wool", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                melon("res/texture/terrian/melon", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                redstone_ore("res/texture/terrian/redstone_ore", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                sand("res/texture/terrian/sand", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA),
                stone_bricks("res/texture/terrian/stone_bricks", "res/shader/basic.vert", "res/shader/basic.frag", GL_RGBA)
    {
        TerrainInit();
    }
    void TerrainInit()
    {
        BoxAxisStruct tmp;
        tmp.GetAxis(0, 0, 0);
        CubeInfo.push_back({ glm::vec3(0.0f) , GRASS_BLOCK , tmp });
        checkout[11][11][11]++;

        //for (int i = -10; i < 10; i += 1)
        //{
        //    for (int j = -10; j < 10; j += 1)
        //    {
        //        float perlin = noise_sum(glm::vec2((float)i * 0.05, (float)j * 0.05));
        //        mi = std::min(mi, perlin);
        //        ma = std::max(ma, perlin);
        //        //std::cout <<"noisevalue : "<< perlin << std::endl;
        //        int y = 0;
        //        while(1)
        //        {
        //            if (y > perlin * 10 + 10)
        //            {
        //                BoxAxisStruct tmp;
        //                tmp.GetAxis(i, y, j);
        //                CubeInfo.push_back({ glm::vec3(float(i) , float(y) , float(j)) , GRASS_BLOCK , tmp});

        //                checkout[i + 11][y + 11][j + 11]++;
        //                break;
        //            }         

        //            BoxAxisStruct tmp;
        //            tmp.GetAxis(i, y, j);
        //            CubeInfo.push_back({ glm::vec3(float(i) , float(y) , float(j)) , DIRT , tmp});

        //            checkout[i + 11][y + 11][j + 11]++;
        //            y += 1;
        //        }
        //    }
        //}
        //std::cout << "minvalue = " << mi << std::endl << "maxvalue = " << ma << std::endl;
    }

    void TerrainDraw(Camera& camera)
    {
        VisbleCubeInfo.clear();
        for (auto it : CubeInfo)
        {
            //if (checkout[(int)it.location.x + 51][(int)it.location.y + 51][(int)it.location.z + 51] == 6) continue;
            if (ViewOptimize(it.location)) continue;
            //else
            //{
            //    VisbleCubeInfo.push_back(it);
            //}
            switch (it.type)
            {
            case (GRASS_BLOCK): grass_block.DrawCube(camera, it.location);break;
            case (DIRT):        dirt.DrawCube(camera, it.location);       break;
            case (DIAMOND):     diamond.DrawCube(camera, it.location);    break;
            case (OAK_LOG):     oak_log.DrawCube(camera, it.location);    break;
            case (OAK_PLANKS):  oak_planks.DrawCube(camera, it.location); break;
            case (SANDSTONE):   sandstone.DrawCube(camera, it.location);  break;
            case (STONE):       stone.DrawCube(camera, it.location);      break;
            case (TNT):         tnt.DrawCube(camera, it.location);        break;
            case (WHITE_WOOL):  white_wool.DrawCube(camera, it.location); break;

            case (BEDROCK):         bedrock.DrawCube(camera, it.location);         break;
            case (BIRCH_PLANKS):    birch_planks.DrawCube(camera, it.location);    break;
            case (BIRCH_LOG):	    birch_log.DrawCube(camera, it.location);       break;
            case (BLOCK_OF_DIAMOND):block_of_diamond.DrawCube(camera, it.location);break;
            case (BLACK_WOOL):	    black_wool.DrawCube(camera, it.location);      break;
            case (BLOCK_OF_GOLD):	block_of_gold.DrawCube(camera, it.location);   break;
            case (BLOCK_OF_EMERAL): block_of_emerald.DrawCube(camera, it.location);break;
            case (BLOCK_OF_LAPIS):	block_of_lapis.DrawCube(camera, it.location);  break;
            case (BLOCK_OF_IRON):	block_of_iron.DrawCube(camera, it.location);   break;

            case (BLOCK_OF_QUARTZ):  block_of_quartz.DrawCube(camera, it.location);   break;
            case (BLOCK_OF_REDSTONE):block_of_redstone.DrawCube(camera, it.location); break;
            case (BOOKSHELF):		 bookshelf.DrawCube(camera, it.location);         break;
            case (BRICKS):			 bricks.DrawCube(camera, it.location);            break;
            case (CARVED_PUMPKIN):	 carved_pumpkin.DrawCube(camera, it.location);    break;
            case (COAL_ORE):		 coal_ore.DrawCube(camera, it.location);          break;
            case (CRAFTING_TABLE):	 crafting_table.DrawCube(camera, it.location);    break;
            case (EMERALD_ORE):		 emerald_ore.DrawCube(camera, it.location);       break;
            case (FURNACE):			 furnace.DrawCube(camera, it.location);           break;

            case (GLASS):			 glass.DrawCube(camera, it.location);           break;
            case (GLOWSTONE):		 glowstone.DrawCube(camera, it.location);       break;
            case (GOLD_ORE):		 gold_ore.DrawCube(camera, it.location);        break;
            case (HAY_BALE):		 hay_bale.DrawCube(camera, it.location);        break;
            case (ICE):				 ice.DrawCube(camera, it.location);             break;
            case (IRON_ORE):		 iron_ore.DrawCube(camera, it.location);        break;
            case (LAPIS_LAZULI_ORE): lapis_lazuli_ore.DrawCube(camera, it.location);break;
            case (LIGHT_BLUE_WOOL):	 light_blue_wool.DrawCube(camera, it.location); break;
            case (LIME_WOOL):		 lime_wool.DrawCube(camera, it.location);       break;

            case (MAGENTA_WOOL):	 magenta_wool.DrawCube(camera, it.location);    break;
            case (ORANGE_WOOL):		 orange_wool.DrawCube(camera, it.location);     break;
            case (PINK_WOOL):		 pink_wool.DrawCube(camera, it.location);       break;
            case (RED_WOOL):		 red_wool.DrawCube(camera, it.location);        break;
            case (YELLOW_WOOL):		 yellow_wool.DrawCube(camera, it.location);     break;
            case (MELON):			 melon.DrawCube(camera, it.location);           break;
            case (REDSTONE_ORE):	 redstone_ore.DrawCube(camera, it.location);    break;
            case (SAND):			 sand.DrawCube(camera, it.location);            break;
            case (STONE_BRICKS):	 stone_bricks.DrawCube(camera, it.location);    break;
            }
        }
    }

    bool ViewOptimize(glm::vec3 location)
    {
        float dist = 
              (location.x - camera.cameraPos.x) * (location.x - camera.cameraPos.x)
            + (location.y - camera.cameraPos.y) * (location.y - camera.cameraPos.y)
            + (location.z - camera.cameraPos.z) * (location.z - camera.cameraPos.z);
        glm::vec3 CubeVec = glm::normalize(location - camera.cameraPos);
        float angle_cos = glm::dot(CubeVec, glm::normalize(camera.cameraFront));
        //float angle_cos = CubeVec.x * camera.cameraFront.x + CubeVec.y * camera.cameraFront.y + CubeVec.z * camera.cameraFront.z;
        if (dist < 4.) return false;
        if((angle_cos < glm::cos(glm::radians(camera.fov)) || dist > 400.))
        //if (angle_cos < 0.766)
        {
            return true;
        }
        return false;
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
