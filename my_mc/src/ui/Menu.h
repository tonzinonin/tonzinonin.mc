#pragma once

#include "LandLoader.h"

#include "UItemplate.h"
#include <unordered_map>

class Icon : UI
{
private:
public:
	Icon() = default;
	Icon(std::string path) : UI(path, "res/shader/UI.vert", "res/shader/UI.frag")
	{}
	void Draw(float x , float y)
	{
		float k = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
		this->UIbind();

		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(0.075 * k , 0.08, 0.8));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(x * k, y, 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};

class Menu : UI
{
private:

	Icon icon_grass_block;
	Icon icon_dirt;
	Icon icon_diamond;
	Icon icon_oak_log;
	Icon icon_oak_planks;
	Icon icon_sandstone;
	Icon icon_stone;
	Icon icon_tnt;
	Icon icon_white_wool;
	
	Icon bedrock;
	Icon birch_planks;
	Icon birch_log;
	Icon block_of_diamond;
	Icon black_wool;
	Icon block_of_gold;
	Icon block_of_emerald;
	Icon block_of_lapis;
	Icon block_of_iron;

	Icon block_of_quartz;
	Icon block_of_redstone;
	Icon bookshelf;
	Icon bricks;
	Icon carved_pumpkin;
	Icon coal_ore; 
	Icon crafting_table;
	Icon emerald_ore;
	Icon furnace;

	Icon glass;
	Icon glowstone;
	Icon gold_ore;
	Icon hay_bale;
	Icon ice;
	Icon iron_ore;
	Icon lapis_lazuli_ore;
	Icon light_blue_wool;
	Icon lime_wool;

	Icon magenta_wool;
	Icon orange_wool;
	Icon pink_wool;
	Icon red_wool;
	Icon yellow_wool;
	Icon melon;
	Icon redstone_ore;
	Icon sand;
	Icon stone_bricks;
public:

	std::unordered_map<CubeType, Icon> iconMap;

	CubeType pack_icon_map[5][9] =
	{
	GRASS_BLOCK , DIRT , DIAMOND , OAK_LOG , OAK_PLANKS , SANDSTONE , STONE,TNT , WHITE_WOOL,

	BEDROCK , BIRCH_PLANKS , BIRCH_LOG , BLOCK_OF_DIAMOND , BLACK_WOOL , BLOCK_OF_GOLD , BLOCK_OF_EMERAL , BLOCK_OF_LAPIS , BLOCK_OF_IRON,

	BLOCK_OF_QUARTZ , BLOCK_OF_REDSTONE , BOOKSHELF , BRICKS , CARVED_PUMPKIN , COAL_ORE , CRAFTING_TABLE , EMERALD_ORE , FURNACE,

	GLASS , GLOWSTONE , GOLD_ORE , HAY_BALE , ICE , IRON_ORE , LAPIS_LAZULI_ORE , LIGHT_BLUE_WOOL , LIME_WOOL,

	MAGENTA_WOOL , ORANGE_WOOL , PINK_WOOL , RED_WOOL , YELLOW_WOOL , MELON , REDSTONE_ORE , SAND , STONE_BRICKS
	};
	//std::unordered_map<CubeType, Icon> icon_uodmap;

	Menu(): UI("res/texture/UI/pack.png", "res/shader/UI.vert", "res/shader/UI.frag")
		,
		icon_grass_block("res/texture/icon/Grass_Block.png"),
		icon_dirt       ("res/texture/icon/Dirt.png"),
		icon_diamond    ("res/texture/icon/Diamond_Ore.png"),
		icon_oak_log    ("res/texture/icon/Oak_Log.png"),
		icon_oak_planks ("res/texture/icon/Oak_Planks.png"),
		icon_sandstone  ("res/texture/icon/Sandstone.png"),
		icon_stone      ("res/texture/icon/Stone.png"),
		icon_tnt        ("res/texture/icon/TNT.png"),
		icon_white_wool ("res/texture/icon/White_Wool.png"),

		bedrock          ("res/texture/icon/Bedrock.png"),
		birch_planks	 ("res/texture/icon/Birch_Planks.png"),
		birch_log 		 ("res/texture/icon/Birch_Log.png"),
		block_of_diamond ("res/texture/icon/Block_of_Diamond.png"),
		black_wool		 ("res/texture/icon/Black_Wool.png"),
		block_of_gold	 ("res/texture/icon/Block_of_Gold.png"),
		block_of_emerald ("res/texture/icon/Block_of_Emerald.png"),
		block_of_lapis	 ("res/texture/icon/Block_of_Lapis.png"),
		block_of_iron	 ("res/texture/icon/Block_of_Iron.png"),

		block_of_quartz  ("res/texture/icon/Block_of_Quartz.png"),
		block_of_redstone("res/texture/icon/Block_of_Redstone.png"),
		bookshelf		 ("res/texture/icon/Bookshelf.png"),
		bricks			 ("res/texture/icon/Bricks.png"),
		carved_pumpkin   ("res/texture/icon/Carved_Pumpkin.png"),
		coal_ore		 ("res/texture/icon/Coal_Ore.png"),
		crafting_table   ("res/texture/icon/Crafting_Table3.png"),
		emerald_ore		 ("res/texture/icon/Emerald_Ore.png"),
		furnace			 ("res/texture/icon/Furnace.png"),

		glass			 ("res/texture/icon/Glass.png"),
		glowstone		 ("res/texture/icon/Glowstone.png"),
		gold_ore		 ("res/texture/icon/Gold_Ore.png"),
		hay_bale		 ("res/texture/icon/Hay_Bale.png"),
		ice				 ("res/texture/icon/Ice.png"),
		iron_ore		 ("res/texture/icon/Iron_Ore.png"),
		lapis_lazuli_ore ("res/texture/icon/Lapis_Lazuli_Ore.png"),
		light_blue_wool  ("res/texture/icon/Light_Blue_Wool.png"),
		lime_wool		 ("res/texture/icon/Lime_Wool.png"),

		magenta_wool	 ("res/texture/icon/Magenta_Wool.png"),
		orange_wool		 ("res/texture/icon/Orange_Wool.png"),
		pink_wool		 ("res/texture/icon/Pink_Wool.png"),
		red_wool		 ("res/texture/icon/Red_Wool.png"),
		yellow_wool		 ("res/texture/icon/Yellow_Wool.png"),
		melon			 ("res/texture/icon/Melon.png"),
		redstone_ore	 ("res/texture/icon/Redstone_Ore.png"),
		sand			 ("res/texture/icon/Sand.png"),
		stone_bricks	 ("res/texture/icon/Stone_Bricks.png")
	{
	}
	void DrawIcon(CubeType type , float x , float y)
	{
		switch (type) {
		case (GRASS_BLOCK): icon_grass_block.Draw(x , y);break;
		case (DIRT):	    icon_dirt.Draw(x , y);       break;
		case (DIAMOND):	    icon_diamond.Draw(x , y);    break;
		case (OAK_LOG):	    icon_oak_log.Draw(x , y);    break;
		case (OAK_PLANKS):	icon_oak_planks.Draw(x , y); break;
		case (SANDSTONE):	icon_sandstone.Draw(x , y);  break;
		case (STONE):    	icon_stone.Draw(x , y);      break;
		case (TNT):	        icon_tnt.Draw(x , y);        break;
		case (WHITE_WOOL):	icon_white_wool.Draw(x , y); break;

		case (BEDROCK):         bedrock.Draw(x, y);         break;
		case (BIRCH_PLANKS):    birch_planks.Draw(x, y);    break;
		case (BIRCH_LOG):	    birch_log.Draw(x, y);       break;
		case (BLOCK_OF_DIAMOND):block_of_diamond.Draw(x, y);break;
		case (BLACK_WOOL):	    black_wool.Draw(x, y);      break;
		case (BLOCK_OF_GOLD):	block_of_gold.Draw(x, y);   break;
		case (BLOCK_OF_EMERAL): block_of_emerald.Draw(x, y);break;
		case (BLOCK_OF_LAPIS):	block_of_lapis.Draw(x, y);  break;
		case (BLOCK_OF_IRON):	block_of_iron.Draw(x, y);   break;

		case (BLOCK_OF_QUARTZ):  block_of_quartz.Draw(x, y); break;
		case (BLOCK_OF_REDSTONE):block_of_redstone.Draw(x, y); break;
		case (BOOKSHELF):		 bookshelf.Draw(x, y); break;
		case (BRICKS):			 bricks.Draw(x, y); break;
		case (CARVED_PUMPKIN):	 carved_pumpkin.Draw(x, y); break;
		case (COAL_ORE):		 coal_ore.Draw(x, y); break;
		case (CRAFTING_TABLE):	 crafting_table.Draw(x, y); break;
		case (EMERALD_ORE):		 emerald_ore.Draw(x, y); break;
		case (FURNACE):			 furnace.Draw(x, y); break;

		case (GLASS):			 glass.Draw(x, y); break;
		case (GLOWSTONE):		 glowstone.Draw(x, y); break;
		case (GOLD_ORE):		 gold_ore.Draw(x, y); break;
		case (HAY_BALE):		 hay_bale.Draw(x, y); break;
		case (ICE):				 ice.Draw(x, y); break;
		case (IRON_ORE):		 iron_ore.Draw(x, y); break;
		case (LAPIS_LAZULI_ORE): lapis_lazuli_ore.Draw(x, y); break;
		case (LIGHT_BLUE_WOOL):	 light_blue_wool.Draw(x, y); break;
		case (LIME_WOOL):		 lime_wool.Draw(x, y); break;

		case (MAGENTA_WOOL):	 magenta_wool.Draw(x, y); break;
		case (ORANGE_WOOL):		 orange_wool.Draw(x, y); break;
		case (PINK_WOOL):		 pink_wool.Draw(x, y); break;
		case (RED_WOOL):		 red_wool.Draw(x, y); break;
		case (YELLOW_WOOL):		 yellow_wool.Draw(x, y); break;
		case (MELON):			 melon.Draw(x, y); break;
		case (REDSTONE_ORE):	 redstone_ore.Draw(x, y); break;
		case (SAND):			 sand.Draw(x, y); break;
		case (STONE_BRICKS):	 stone_bricks.Draw(x, y); break;

		}
	}
	void DrawAll()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				DrawIcon(pack_icon_map[i][j], float(j) * 0.107 - 0.428, - float(i) * 0.106 + 0.25);
			}
		}
	}
	void Draw()
	{
		this->UIbind();
		float k = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;

		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::scale(trans, glm::vec3(1.0 * k , 0.745 , 1.0));

		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0., 0., 0.));

		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "scale"), 1, GL_FALSE, &trans[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		this->UIunbind();
	}
};

