#pragma once
#include "olcPixelGameEngine.h"
#include "Stats.h"
#include "Script.h"

#ifdef DrawText
#undef DrawText
#endif 

//odleg³oœæ od wyœwietlanego UI do krawêdzi ekranu
constexpr auto UI_FromScreenBorder = 10;

class cMap;
class cDynamic;
class cDynamicCreature;

class cEngine : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	cMap* m_currentMap;
	float m_fStaticAnimTime;		//czas aktualizacji animacji mapy
	float m_fStacicAnimInterval;	//okres aktualizacji animacji mapy
	short m_nStaticAnimFrame;		//klatka animacji mapy
	float fCollisionDetectionDistancePow2;
	olc::Sprite* m_sprFont4x4;
	olc::Sprite* m_sprFont4x5;
	olc::Sprite* m_sprFont4x6;
	olc::Sprite* m_sprFont6x8_black;
	olc::Sprite* m_sprFont6x8_white;
	olc::Sprite* m_sprFont6x8_red;
	olc::Sprite* m_sprFont6x8_dark_red;
	olc::Sprite* m_sprFont8x12;
	olc::Sprite* m_sprFont16x16_white;
	olc::Sprite* m_sprFont16x16_black;

	float fHealthFlashTimer; // timer czasu migniêcia na czerwono wskaŸnika ¿ycia
	float fHealthFlashDuration; // czas przez jaki wskaŸnik ¿ycia bêdzie czerwony po otrzymaniu obra¿eñ
	float fOldHP; // HP w poprzedniej klatce potrzebne do wykrycia otrzymania przez gracza obra¿eñ

	bool bGfxHighSettings;
	bool m_bShowDialog;
	bool m_bShowMessage;
	std::list<std::vector<std::string>> m_listDialogsQueue;
	std::list<std::vector<std::string>> m_listMessagesQueue;

	void DrawFrontDialog(int x, int y); // wyœwietlanie dialogu z obramówik¹
	void DisplayFrontMessage(); // wyœwietlanie komunikatu na œrodku z obramówk¹

	//odczyt danych z pliku konfiguracyjnego i parametry które s¹ odczytywane
	void ReadConfigFile();
	std::string config_sLang;

	//menu g³ówne:
	float fTitleScrollSpeedBG;
	float fTitleScrollSpeedForest;
	float fTitleScrollOffsetBG;
	float fTitleScrollOffsetForest;
	float fInitialDimmTime;
	bool bTitleStart;
	float fStartDimmingDuration;

public:
	cScriptEngine ScriptEngine;

	cMap* GetCurrentMap()
	{
		return m_currentMap;
	}

	cDynamicCreature* pPlayer;
	cDynamicCreature* Player();

	cPlayerData PlayerData;

	void AddDyn(cDynamic* dyn);

	cDynamic* GetDyn(std::string name); // zwraca wskaŸnik do obiektu dynamicznego o danej nazwie 
										// (lub nullptr jeœli ¿adnego nie znalaz³)
	int nTileWidth;
	int nTileHeight;

	bool bPause;

	float fCameraPosX;
	float fCameraPosY;

	void ChangeMap(std::string mapName, float _px, float _py);

	float DistanceBetweenDynCenterPow2(cDynamic* A, cDynamic* B);

	void RecalculatePlayerStats();

	enum TEXT_COLOUR
	{
		TXT_BLACK,
		TXT_WHITE,
		TXT_RED,
		TXT_DARK_RED
	};

	// ka¿dy tekst jest domyœlnie czarny
	void DrawTinyText(std::string sText, int x, int y);	// rysuje tekst 4x4
	void DrawSmallText(std::string sText, int x, int y);// rysuje tekst 4x6
	void Draw4x5Text(std::string sText, int x, int y);	// rysuje tekst 4x5
	void Draw8x12Text(std::string sText, int x, int y);	// rysuje tekst 8x12

	// rysuje tekst 6x8 ( bia³y, czarny, czerwony lub ciemnoczerwony )
	void DrawText(std::string sText, int x, int y, TEXT_COLOUR colour = TXT_BLACK);	

	// rysuje tekst 16x16 o kolorze bia³y lub czarnym
	void Draw16x16Text(std::string sText, int x, int y, TEXT_COLOUR colour = TXT_BLACK); // UWAGA - tylko wielkie litery

	//dialogi:
	void NextDialog(); // funkcja ta powinna wy³¹czyæ wyœwietlanie dialogów jeœli nie ma ¿adnych dostêpnych
	// a jeœli jakieœ s¹ to ustawiæ jako wyœwietlany nastêpny w kolejce do wyœwietlania
	void AddDialog(std::vector<std::string> vecText);  // g³ówna funkcja u¿ywana przy towrzeniu zawartoœci
	void ClearAllDialogs(); // czyszczenie wszystkich dialogów w kolejce (z obecnie wyœwietlanym w³¹cznie)

	//komunikaty:
	void NextMessage(); // analogicznie do dialogów, lecz komunikaty maj¹ piorytet nad dialogami
	void AddMessage(std::vector<std::string> vecMessage); // g³ówna funkcja u¿ywana przy towrzeniu zawartoœci

	// wyœwietlanie interfejsu
	bool bShowUI;
	void DrawUI(float fElapsedTime);
	int8_t nDimm;

public:

	enum GAMESTATE
	{
		GS_LOCAL_MAP,
		GS_TITLE_MENU

	} GS_gamestate;

	bool UpdateLocalMap(float fElapsedTime);
	bool UpdateTitleMenu(float fElapsedTime);

public:
	cEngine()
	{
		sAppName = "RPG Engine Demo v0.16.1 by Sakue";
		m_currentMap = nullptr;
		pPlayer = nullptr;
		bPause = false;
		bGfxHighSettings = true;
		m_bShowDialog = false;
		m_bShowMessage = false;
		nDimm = 0;
		fHealthFlashTimer = 0.0f;
		fHealthFlashDuration = 0.4f;
		fOldHP = 0.0f;
		m_fStaticAnimTime = 0.0f;
		m_fStacicAnimInterval = 0.0f;
		m_nStaticAnimFrame = 0;
		fCameraPosX = 0.0f;
		fCameraPosY = 0.0f;
		bShowUI = true;
		GS_gamestate = GS_TITLE_MENU;
		fTitleScrollSpeedBG = 8.0f;
		fTitleScrollSpeedForest = 18.0f;
		fTitleScrollOffsetBG = 0.0f;
		fTitleScrollOffsetForest = 0.0f;
		fInitialDimmTime = 0.0f;
		bTitleStart = false;
		fStartDimmingDuration = 3.0f;
	}
};