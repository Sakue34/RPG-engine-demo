#pragma once
#include "olcPixelGameEngine.h"
#include "Stats.h"
#include "Script.h"

#ifdef DrawText
#undef DrawText
#endif 

//odleg�o�� od wy�wietlanego UI do kraw�dzi ekranu
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

	float fHealthFlashTimer; // timer czasu migni�cia na czerwono wska�nika �ycia
	float fHealthFlashDuration; // czas przez jaki wska�nik �ycia b�dzie czerwony po otrzymaniu obra�e�
	float fOldHP; // HP w poprzedniej klatce potrzebne do wykrycia otrzymania przez gracza obra�e�

	bool bGfxHighSettings;
	bool m_bShowDialog;
	bool m_bShowMessage;
	std::list<std::vector<std::string>> m_listDialogsQueue;
	std::list<std::vector<std::string>> m_listMessagesQueue;

	void DrawFrontDialog(int x, int y); // wy�wietlanie dialogu z obram�wik�
	void DisplayFrontMessage(); // wy�wietlanie komunikatu na �rodku z obram�wk�

	//odczyt danych z pliku konfiguracyjnego i parametry kt�re s� odczytywane
	void ReadConfigFile();
	std::string config_sLang;

	//menu g��wne:
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

	cDynamic* GetDyn(std::string name); // zwraca wska�nik do obiektu dynamicznego o danej nazwie 
										// (lub nullptr je�li �adnego nie znalaz�)
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

	// ka�dy tekst jest domy�lnie czarny
	void DrawTinyText(std::string sText, int x, int y);	// rysuje tekst 4x4
	void DrawSmallText(std::string sText, int x, int y);// rysuje tekst 4x6
	void Draw4x5Text(std::string sText, int x, int y);	// rysuje tekst 4x5
	void Draw8x12Text(std::string sText, int x, int y);	// rysuje tekst 8x12

	// rysuje tekst 6x8 ( bia�y, czarny, czerwony lub ciemnoczerwony )
	void DrawText(std::string sText, int x, int y, TEXT_COLOUR colour = TXT_BLACK);	

	// rysuje tekst 16x16 o kolorze bia�y lub czarnym
	void Draw16x16Text(std::string sText, int x, int y, TEXT_COLOUR colour = TXT_BLACK); // UWAGA - tylko wielkie litery

	//dialogi:
	void NextDialog(); // funkcja ta powinna wy��czy� wy�wietlanie dialog�w je�li nie ma �adnych dost�pnych
	// a je�li jakie� s� to ustawi� jako wy�wietlany nast�pny w kolejce do wy�wietlania
	void AddDialog(std::vector<std::string> vecText);  // g��wna funkcja u�ywana przy towrzeniu zawarto�ci
	void ClearAllDialogs(); // czyszczenie wszystkich dialog�w w kolejce (z obecnie wy�wietlanym w��cznie)

	//komunikaty:
	void NextMessage(); // analogicznie do dialog�w, lecz komunikaty maj� piorytet nad dialogami
	void AddMessage(std::vector<std::string> vecMessage); // g��wna funkcja u�ywana przy towrzeniu zawarto�ci

	// wy�wietlanie interfejsu
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