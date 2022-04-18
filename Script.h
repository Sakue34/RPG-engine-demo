#pragma once
#include <list>
#include <string>

class cScript
{
protected:
	float fTime = 0.0f; // licznik obecnego czasu wykonywania skryptu
	float fExecutionTime = 0.0f; // ca³kowity czas jaki ma trwaæ skrypt
public:
	bool bHasStarted = false;
	bool bAllowForUserControl = false;
	bool bFreezeTime = false;
	bool bWaitForSkip = false; // skrypt nie zakoñczy siê sam, a jedynie gracz mo¿e go zakoñczyæ wciskaj¹c klawisz
	enum CAMERA_FOLLOW_SCRIPT
	{
		CAMERA_STICK_TO_PLAYER,
		CAMERA_FREE,
		CAMERA_DO_NOT_CHANGE
	} nCameraOnPlayer = CAMERA_DO_NOT_CHANGE;

	virtual void Start() { };
	virtual bool Update(float fElapsedTime) { return true; } // true jeœli skrypt zosta³ zakoñczony, false - jeœli ci¹gle ma trwaæ
	
public:
	cScript() { }
};

class cScriptEngine
{
public:
	std::list<cScript*> listScripts;

	void UpdateScripts(float fElapsedTime); // aktualizuje obecnie wykonywany skrypt
	void AddScript(cScript* script) // dodaje nowy skrypt do kolejki
	{
		listScripts.push_back(script);
	}

	void AddScriptInFront(cScript* script)  // dodaje nowy skrypt z przodu kolejki (wykorzystywany np. w makrach które wykonuj¹ kilka skryptów)
	{										// 
		listScripts.push_front(script);
	}

	void SkipAllScripts();

	bool bPlayerInControl;
	bool bTimeIsFreezed;
	bool bWaitForManualSkip;
	bool bCameraFollowsPlayer;

public:
	cScriptEngine();

};
