#include "Data.h"
#include "All_Maps.h"
#include "Stats.h"
#include <fstream>

cData::~cData() { }
cData::cData() { }

void cData::LoadSprites()
{
	auto load = [&](std::string sName, std::string sFileName)
	{
		olc::Sprite* s = new olc::Sprite(sFileName);
		m_mapSprites[sName] = s;
	};

	//gracz
	load("player", "data/gfx/player.png");
	
	//NPC
	load("female", "data/gfx/female.png");

	//miecz gracza (obiekt dynamiczny w œwiecie gry)
	load("player melee", "data/gfx/player_sword.png");

	//stwory
	load("skeleton", "data/gfx/skeleton.png");
	load("bat", "data/gfx/bat.png");
	load("slime", "data/gfx/slime.png");
	
	//obiekty
	load("signpost", "data/gfx/signpost.png");
	load("iron door", "data/gfx/iron_door.png");
	load("spikes", "data/gfx/spikes.png");
	load("torch", "data/gfx/torch.png");
	load("chest", "data/gfx/chest.png");
	load("stairway down", "data/gfx/stairway_down.png");
	load("stairway up", "data/gfx/stairway_up.png");

	//tesktury mapy
	load("tileset1", "data/gfx/tileset1.png");

	//bañki-emotikony
	load("emote bubble", "data/gfx/emote_bubbles.png");

	//t³o ekranu tytu³owego
	load("title background", "data/gfx/title_background.png");
	load("title forest", "data/gfx/title_forest.png");
	
}

void cData::LoadMaps(cEngine* engine)
{
	auto load = [&](cMap* m)
	{
		m_mapMaps[m->sName] = m;
	};

	load(new cMap1(engine));
	load(new cMap2(engine));
	load(new cMap_Test(engine));
	load(new cMap_Intro1(engine));
	load(new cMap_Intro2(engine));
	load(new cMap_Intro3(engine));
	load(new cMap_Intro4(engine));
	load(new cMap_Intro5(engine));
	load(new cMap_Intro6(engine));
	load(new cMap_Plains1(engine));
	load(new cMap_Dungeon1(engine));
	load(new cMap_Village1(engine));
	load(new cMap_Plains2(engine));
	load(new cMap_Cave1(engine));
	load(new cMap_Cep(engine));
}

void cData::LoadItemSprites()
{
	auto load = [&](std::string sName, std::string sFileName)
	{
		olc::Sprite* s = new olc::Sprite(sFileName);
		m_mapItemSprites[sName] = s;
	};

	//przedmioty
	load("Basic sword", "data/gfx/items/basic_sword.png");
	load("Steel sword", "data/gfx/items/steel_sword.png");
}

void cData::LoadDialogs()
{
	std::string sFilePathPrefix = "data/lang/EN/";

	auto load = [&](std::string sNameAndFileName)
	{
		std::vector<std::string> dialog;

		std::ifstream ifs;
		ifs.open(sFilePathPrefix + sNameAndFileName + ".txt", std::ios::in);
		if (ifs.good())
		{
			while (!ifs.eof())
			{
				std::string line;
				std::getline(ifs, line);
				dialog.push_back(line);
			}

			ifs.close();
		}
		else // nieudany odczyt pliku
		{
			dialog.push_back("Error reading file:");
			dialog.push_back(sFilePathPrefix + sNameAndFileName + ".txt");
		}

		m_mapDialogs[sNameAndFileName] = dialog;
	};

	for (unsigned i = 100; i < MAX_DIALOG_FILES_AMOUNT + 101; i++)
		load(std::to_string(i));

}