#pragma once

#include "olcPixelGameEngine.h"

class cMap;

constexpr int UI_ADDITIONAL_PIXELS_RIGHT = 161;

#ifdef DrawText
#undef DrawText
#endif 

class cMapEditor : public olc::PixelGameEngine
{
private:
	olc::Sprite* sprTileSet;
	olc::Sprite* sprSelection;
	olc::Sprite* sprSelection2;
	olc::Sprite* sprSelection3;
	olc::Sprite* sprSelection4;
	olc::Sprite* sprSolid;
	olc::Sprite* sprSolid2;
	olc::Sprite* sprAnimated;

	int nTileWidth;
	int nTileHeight;
	cMap* m_currentMap;

	float fCameraPosX;
	float fCameraPosY;

	float m_fStaticAnimTime;
	float m_fStacicAnimInterval;
	int m_nStaticAnimFrame;

	float fCameraSpeed;

	enum TOOL
	{
		TOOL_PENCIL,
		TOOL_FLAGS
	} nTool;

	int nVisibleTilesX;
	int nVisibleTilesY;

	int nSelectedX;
	int nSelectedY;

	enum TEXT_COLOUR
	{
		TXT_BLACK,
		TXT_WHITE,
		TXT_RED,
		TXT_DARK_RED
	};

	olc::Sprite* m_sprFont6x8_white;
	olc::Sprite* m_sprFont6x8_black;
	olc::Sprite* m_sprFont6x8_red;
	olc::Sprite* m_sprFont6x8_dark_red;

	unsigned short nLayer;
	unsigned int nID;
	bool bFlagIsSolid;
	bool bFlagIsAnimated;

	bool bUserNavigatesTileSet;

	void DrawText(std::string sText, int x, int y, TEXT_COLOUR colour = TXT_BLACK);

	int nTileSelectOffset;
	float fTimePressedFlagKey;

public:
	cMapEditor()
	{
		sAppName = "RPG Map Editor by Sakue";

		sprTileSet = nullptr;
		nTileWidth = 16;
		nTileHeight = 16;
		m_currentMap = nullptr;
		sprSelection = nullptr;
		sprSelection2 = nullptr;
		sprSelection3 = nullptr;
		sprSelection4 = nullptr;
		sprSolid = nullptr;
		sprSolid2 = nullptr;
		sprAnimated = nullptr;
		m_fStacicAnimInterval = 1.0f;
		m_fStaticAnimTime = m_fStacicAnimInterval;
		m_nStaticAnimFrame = 0;
		fCameraPosX = 0.0f;
		fCameraPosY = 0.0f;
		fCameraSpeed = 0.0f;
		nTool = TOOL_PENCIL;
		nSelectedX = 0;
		nSelectedY = 0;
		nVisibleTilesX = 0;
		nVisibleTilesY = 0;
		nLayer = 1;
		nID = 0;
		bFlagIsSolid = false;
		bFlagIsAnimated = false;
		bUserNavigatesTileSet = false;
		nTileSelectOffset = 0;
		fTimePressedFlagKey = 0.0f;
	}

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:

};