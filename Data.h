#pragma once

#include <map>
#include "Map.h"
#include "olcPixelGameEngine.h"

class cMap;
class cEngine;

#ifndef MAX_DIALOG_FILES_AMOUNT
#define MAX_DIALOG_FILES_AMOUNT 52
#endif // !MAX_DIALOG_FILES_AMOUNT

class cData
{
private:
	~cData();
	cData();

	std::map<std::string, olc::Sprite*> m_mapSprites;
	std::map<std::string, cMap*> m_mapMaps;
	std::map<std::string, olc::Sprite*> m_mapItemSprites;
	std::map<std::string, std::vector<std::string>> m_mapDialogs;

public:
	static cData& get()
	{
		static cData me;
		return me;
	}

	// usuniêcie operatorów zapewniaj¹ce istnienie tylko jednej instancji singletonu
	cData(cData const&) = delete;
	void operator=(cData const&) = delete;

	// funkcja zwracaj¹ca sprite'a o podanym indeksie
	olc::Sprite* GetSprite(std::string name)
	{
		return m_mapSprites[name];
	}

	cMap* GetMap(std::string mapName)
	{
		return m_mapMaps[mapName];
	}

	olc::Sprite* GetItemSprite(std::string itemName) 
	{
		return m_mapItemSprites[itemName];
	}

	std::vector<std::string> GetDialog(std::string dialogName)
	{
		return m_mapDialogs[dialogName];
	}

	void LoadSprites();
	void LoadMaps(cEngine* engine);
	void LoadItemSprites(); 
	void LoadDialogs();
};