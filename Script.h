#pragma once
#include <list>
#include <string>

class cScript
{
protected:
	float fTime = 0.0f; // licznik obecnego czasu wykonywania skryptu
	float fExecutionTime = 0.0f; // ca�kowity czas jaki ma trwa� skrypt
public:
	bool bHasStarted = false;
	bool bAllowForUserControl = false;
	bool bFreezeTime = false;
	bool bWaitForSkip = false; // skrypt nie zako�czy si� sam, a jedynie gracz mo�e go zako�czy� wciskaj�c klawisz
	enum CAMERA_FOLLOW_SCRIPT
	{
		CAMERA_STICK_TO_PLAYER,
		CAMERA_FREE,
		CAMERA_DO_NOT_CHANGE
	} nCameraOnPlayer = CAMERA_DO_NOT_CHANGE;

	virtual void Start() { };
	virtual bool Update(float fElapsedTime) { return true; } // true je�li skrypt zosta� zako�czony, false - je�li ci�gle ma trwa�
	
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

	void AddScriptInFront(cScript* script)  // dodaje nowy skrypt z przodu kolejki (wykorzystywany np. w makrach kt�re wykonuj� kilka skrypt�w)
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
