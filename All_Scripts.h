#pragma once

#include "Script.h"
#include <vector>

class cDynamic;
class cDynamicCreature;
class cEngine;
class cWeapon;
class cOpenable;

class cScript_MoveTo : public cScript
{
private:
	float fTargetX;
	float fTargetY;

	cDynamic* dynamic;

	float fStartX;
	float fStartY;

	float fDistanceToDestX;
	float fDistanceToDestY;
public:
	cScript_MoveTo(cDynamic* _dyn, float ToX, float ToY, float time, bool playerincontrol = false);
	void Start();
	bool Update(float fElapsedTime);
};

class cScript_DimmScreenFor : public cScript
{
private:
	cEngine* engine;
	float fSpeed; // czas w jakim ma siê œciemniæ
	float fSpeed2; // czas w jakim ma siê rozjaœniæ
public:
	cScript_DimmScreenFor(cEngine* _engine, float length, float dimming_speed, float brighten_speed, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);
};

class cScript_MakeSleeping : public cScript
{
private:
	cDynamic* dynamic;
public:
	cScript_MakeSleeping(cDynamic* _dyn);
	void Start();
};

class cScript_MakeUnconscious : public cScript
{
private:
	cDynamic* dynamic;
public:
	cScript_MakeUnconscious(cDynamic* _dyn);
	void Start();
};

class cScript_WakeUp : public cScript
{
private:
	cDynamic* dynamic;
public:
	cScript_WakeUp(cDynamic* _dyn);
	void Start();
};

class cScript_Wait : public cScript
{
private:
	cEngine* engine;
public:
	cScript_Wait(cEngine* _engine, float duration, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);

};

class cScript_AddDialog : public cScript	//uwaga: rêczne pominiêcie tego skryptu (mo¿liwe po ustawieniu ostatniego parametru jako true) nie pomija jednoczeœnie dialogu!
{											//nale¿y po skrypcie dodaj¹cy dialog z rêcznym pominiêciem wywo³aæ skrypt cScript_ClearAllDialogs
private:
	cEngine* engine;
	std::vector<std::string> vecText;
public:
	cScript_AddDialog(cEngine* _engine, std::vector<std::string> _vecText, bool waitWithScriptsForUserSkip = false);
	void Start();
};

class cScript_ClearAllDialogs : public cScript
{
private:
	cEngine* engine;
public:
	cScript_ClearAllDialogs(cEngine* _engine);
	void Start();
};

class cScript_DimmScreen : public cScript
{
private:
	cEngine* engine;
public:
	cScript_DimmScreen(cEngine* _engine, float dimming_speed, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);

};

class cScript_DimmScreenPartially : public cScript
{
private:
	cEngine* engine;
	int nStartDimm;
	int nEndDimm;
public:
	cScript_DimmScreenPartially(cEngine* _engine, float dimming_speed, int _startdimm, int _enddimm, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);

};


class cScript_BrightenScreen : public cScript
{
private:
	cEngine* engine;
public:
	cScript_BrightenScreen(cEngine* _engine, float brightening_speed, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);

};

class cScript_BrightenScreenPartially : public cScript
{
private:
	cEngine* engine;
	int nStartDimm;
	int nEndDimm;
public:
	cScript_BrightenScreenPartially(cEngine* _engine, float brightening_speed, int _startdimm, int _enddimm, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);

};


class cScript_ChangeMap : public cScript
{
private:
	cEngine* engine;
	std::string sMap;
	float x;
	float y;
public:
	cScript_ChangeMap(cEngine* _engine, std::string _map, float _x, float _y);
	void Start();
};

class cScript_AddMessage : public cScript
{
private:
	cEngine* engine;
	std::vector<std::string> vecText;
public:
	cScript_AddMessage(cEngine* _engine, std::vector<std::string> _vecText);
	void Start();

};

class cScript_StickCameraToPlayer : public cScript
{
public:
	cScript_StickCameraToPlayer();
	void Start();
};

class cScript_MoveCameraTo : public cScript
{
private:
	cEngine* engine;

	float fToX;
	float fToY;

	float fStartX;
	float fStartY;

	float fDistanceToDestX;
	float fDistanceToDestY;
public:
	cScript_MoveCameraTo(cEngine* _engine, float x, float y, float time, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);
};

class cScript_ShakeCameraLeaveCameraFree : public cScript
{
private:
	cEngine* engine;
	float fShakeSpeed;
public:
	cScript_ShakeCameraLeaveCameraFree(cEngine* _engine, float time, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);
};

class cScript_ShakeCamera : public cScript
{
private:
	cEngine* engine;
	float time;
public:
	cScript_ShakeCamera(cEngine* _engine, float time, bool playerincontrol = false, bool freeze_time = false);
	void Start();
};

class cScript_EmoteLove : public cScript
{
private:
	cEngine* engine;
	cDynamic* owner;
	bool bLoopAnimation;
	float fLifeTime;
public:
	cScript_EmoteLove(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime);
	void Start();
};

class cScript_EmoteSilence : public cScript
{
private:
	cEngine* engine;
	cDynamic* owner;
	bool bLoopAnimation;
	float fLifeTime;
public:
	cScript_EmoteSilence(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime);
	void Start();
};

class cScript_EmoteAlert : public cScript
{
private:
	cEngine* engine;
	cDynamic* owner;
	bool bLoopAnimation;
	float fLifeTime;
public:
	cScript_EmoteAlert(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime);
	void Start();
};

class cScript_EmoteConfusion : public cScript
{
private:
	cEngine* engine;
	cDynamic* owner;
	bool bLoopAnimation;
	float fLifeTime;
public:
	cScript_EmoteConfusion(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime);
	void Start();
};

class cScript_EmoteE : public cScript
{
private:
	cEngine* engine;
	cDynamic* owner;
	bool bLoopAnimation;
	float fLifeTime;
public:
	cScript_EmoteE(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime);
	void Start();
};

class cScript_SetDimm : public cScript
{
private:
	int8_t nDimm;
	cEngine* engine;
public:
	cScript_SetDimm(cEngine* _engine, int _dimm);
	void Start();
};

class cScript_ShowUI : public cScript
{
private:
	cEngine* engine;
public:
	cScript_ShowUI(cEngine* _engine);
	void Start();
};

class cScript_HideUI : public cScript
{
private:
	cEngine* engine;
public:
	cScript_HideUI(cEngine* _engine);
	void Start();
};

class cScript_DevGiveAndEqiupWeapon : public cScript
{
private:
	cEngine* engine;
	cWeapon* weapon;
public:
	cScript_DevGiveAndEqiupWeapon(cEngine* _engine, cWeapon* _weapon);
	void Start();
};

class cScript_Spawn : public cScript
{
private:
	cEngine* engine;
	cDynamic* dynamic;
public:
	void Start();
	cScript_Spawn(cEngine* _engine, cDynamic* _dyn);
};

class cScript_OpenOpenable : public cScript
{
private:
	cEngine* engine;
	cOpenable* dynamic;
public:
	void Start();
	cScript_OpenOpenable(cEngine* _engine, cOpenable* _dynamic);

};

class cScript_ShakeCameraLeaveCameraFreeAndDimmScreen : public cScript
{
private:
	cEngine* engine;
	float fShakeSpeed;
public:
	cScript_ShakeCameraLeaveCameraFreeAndDimmScreen(cEngine* _engine, float time, bool playerincontrol = false, bool freeze_time = false);
	void Start();
	bool Update(float fElapsedTime);
};

class cScript_HealFor : public cScript
{
private:
	cDynamicCreature* dynamic;
	float fHealFor;
public:
	void Start();
	cScript_HealFor(cDynamicCreature* _dyn, float _healfor);
};

class cScript_SetMaxStamina : public cScript
{
private:
	cEngine* engine;
	float fNewMaxStamina;
public:
	void Start();
	cScript_SetMaxStamina(cEngine* _engine, float _newmaxstam);
};

class cScript_SetMaxHP : public cScript
{
private:
	cDynamic* dyn;
	float fNewMaxHP;
public:
	void Start();
	cScript_SetMaxHP(cDynamic*, float);
};