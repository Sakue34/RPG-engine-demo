#include "All_Scripts.h"
#include "All_Dynamics.h"
#include "Engine.h"
#include "Data.h"

cScript_MoveTo::cScript_MoveTo(cDynamic* _dyn, float ToX, float ToY, float time, bool playerincontrol)
{
	fExecutionTime = time;
	fTargetX = ToX;
	fTargetY = ToY;
	dynamic = _dyn;
	fStartX = 0.0f;
	fStartY = 0.0f;
	fDistanceToDestX = 0.0f;
	fDistanceToDestY = 0.0f;
	bAllowForUserControl = playerincontrol;
}

void cScript_MoveTo::Start()
{
	if (dynamic != nullptr)
	{
		fStartX = dynamic->px;
		fStartY = dynamic->py;
		dynamic->bIsMovedByScript = true;

		fDistanceToDestX = fTargetX - fStartX;
		fDistanceToDestY = fTargetY - fStartY;
	}

	bHasStarted = true;
}

bool cScript_MoveTo::Update(float fElapsedTime)
{
	if (dynamic == nullptr)
		return true;

	//aktualizacja timera
	fTime += fElapsedTime;

	// v = s/t		prêdkoœæ = droga / czas
	dynamic->vx = fDistanceToDestX / fExecutionTime;
	dynamic->vy = fDistanceToDestY / fExecutionTime;

	if (fTime >= fExecutionTime)
	{
		// rêczne ustawienie po³o¿enia po zakoñczeniu skryptu aby upewniæ siê ¿e np. kolizja nie uniemo¿liwi³a ruchu po prostej
		dynamic->px = fTargetX;
		dynamic->py = fTargetY;

		//wyzerowanie prêdkoœci obiektu po zakoñczeniu ruchu przez skrypt
		dynamic->vx = 0.0f;
		dynamic->vy = 0.0f;
		dynamic->ZeroNewVelocities();

		// oddanie kontroli nad obiektem AI i funkcji cDynamicCreature::Update()
		dynamic->bIsMovedByScript = false;
		return true; // zg³oœ funkcji nadrzêdnej ¿e skrypt siê zakoñczy³
	}

	return false; // skrypt bêdzie jeszcze trwa³
}

cScript_DimmScreenFor::cScript_DimmScreenFor(cEngine* _engine, float total_length_with_transitions, float dimming_speed, float brighten_speed, bool playerincontrol, bool freeze_time)
{
	fSpeed = dimming_speed;
	fSpeed2 = brighten_speed;
	fExecutionTime = dimming_speed + total_length_with_transitions;
	bAllowForUserControl = playerincontrol;
	engine = _engine;
	bFreezeTime = freeze_time;
}

void cScript_DimmScreenFor::Start()
{
	bHasStarted = true;
}

bool cScript_DimmScreenFor::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (fTime < fSpeed)
	{
		engine->nDimm = (int8_t)((fTime / fSpeed) * 255);
	}
	else
	{
		if (fTime <= (fExecutionTime - fSpeed2))
			engine->nDimm = (int8_t)255;
		else
			engine->nDimm = (int8_t)((1.0f - ((fTime - (fExecutionTime - fSpeed2)) / fSpeed2)) * 255);

		if (fTime >= fExecutionTime)
		{
			engine->nDimm = 0;
			return true;
		}
	}

	return false;
}

cScript_MakeSleeping::cScript_MakeSleeping(cDynamic* _dyn)
{
	dynamic = _dyn;
}

void cScript_MakeSleeping::Start()
{
	cDynamicCreature* pDyn = dynamic_cast<cDynamicCreature*>(dynamic);
	if (pDyn != nullptr) // zabezpieczenie przed podaniem nieistniej¹cego obiektu lub obiektu o niepoprawnym typie (np. cDynamic)
	{
		pDyn->SetState(cDynamicCreature::STATE_SLEEPING);
		pDyn->nLayer = 1;
	}
	
	bHasStarted = true;
}

cScript_MakeUnconscious::cScript_MakeUnconscious(cDynamic* _dyn)
{
	dynamic = _dyn;
}

void cScript_MakeUnconscious::Start()
{
	cDynamicCreature* pDyn = dynamic_cast<cDynamicCreature*>(dynamic);
	if (pDyn != nullptr) // zabezpieczenie przed podaniem nieistniej¹cego obiektu lub obiektu o niepoprawnym typie (np. cDynamic)
	{
		pDyn->SetState(cDynamicCreature::STATE_UNCONSCIOUS);
		pDyn->nLayer = 1;
	}

	bHasStarted = true;
}

cScript_WakeUp::cScript_WakeUp(cDynamic* _dyn)
{
	dynamic = _dyn;
}

void cScript_WakeUp::Start()
{
	cDynamicCreature* pDyn = dynamic_cast<cDynamicCreature*>(dynamic);
	if (pDyn != nullptr) // zabezpieczenie przed podaniem nieistniej¹cego obiektu lub obiektu o niepoprawnym typie (np. cDynamic)
	{
		pDyn->SetState(cDynamicCreature::STATE_STANDING);
		pDyn->nLayer = pDyn->nDefaultLayer;
	}

	bHasStarted = true;
}

cScript_Wait::cScript_Wait(cEngine* _engine, float duration, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	fExecutionTime = duration;
	bAllowForUserControl = playerincontrol;
	bFreezeTime = freeze_time;
}

void cScript_Wait::Start()
{
	bHasStarted = true;
}

bool cScript_Wait::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (fTime >= fExecutionTime)
		return true;

	return false;
}

cScript_AddDialog::cScript_AddDialog(cEngine* _engine, std::vector<std::string> _vecText, bool waitWithScriptsForUserSkip)
{
	engine = _engine;
	vecText = _vecText;
	bWaitForSkip = waitWithScriptsForUserSkip;
}

void cScript_AddDialog::Start()
{
	engine->AddDialog(vecText);
	bHasStarted = true;
}

cScript_ClearAllDialogs::cScript_ClearAllDialogs(cEngine* _engine)
{
	engine = _engine;
}

void cScript_ClearAllDialogs::Start()
{
	engine->ClearAllDialogs();
	bHasStarted = true;
}

cScript_DimmScreen::cScript_DimmScreen(cEngine* _engine, float dimming_speed, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	bFreezeTime = freeze_time;
	bAllowForUserControl = playerincontrol;
	fExecutionTime = dimming_speed;
}

void cScript_DimmScreen::Start()
{
	bHasStarted = true;
}

bool cScript_DimmScreen::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (fTime < fExecutionTime)
	{
		engine->nDimm = (int8_t)((fTime / fExecutionTime) * 255);
	}
	else
	{
		engine->nDimm = (int8_t)255;
		return true;
	}

	return false;
}

cScript_DimmScreenPartially::cScript_DimmScreenPartially(cEngine* _engine, float dimming_speed, int _startdimm, int _enddimm, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	bFreezeTime = freeze_time;
	bAllowForUserControl = playerincontrol;
	fExecutionTime = dimming_speed;

	if(_startdimm >= 0 && _startdimm <= 255)
		nStartDimm = _startdimm;
	else
		nStartDimm = 0;

	if (_enddimm >= 0 && _enddimm <= 255)
		nEndDimm = _enddimm;
	else
		nEndDimm = 255;
}

void cScript_DimmScreenPartially::Start()
{
	engine->nDimm = nStartDimm;
	bHasStarted = true;
}

bool cScript_DimmScreenPartially::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (fTime < fExecutionTime)
	{
		engine->nDimm = (int8_t)(((fTime / fExecutionTime) * (nEndDimm - nStartDimm)) + nStartDimm);
	}
	else
	{
		engine->nDimm = nEndDimm;
		return true;
	}

	return false;
}

cScript_BrightenScreen::cScript_BrightenScreen(cEngine* _engine, float brightening_speed, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	bFreezeTime = freeze_time;
	bAllowForUserControl = playerincontrol;
	fExecutionTime = brightening_speed;
}

void cScript_BrightenScreen::Start()
{
	bHasStarted = true;
}

bool cScript_BrightenScreen::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (engine->nDimm == 0)
		return true;

	if (fTime < fExecutionTime)
	{
		engine->nDimm = (int8_t)((1.0f - (fTime / fExecutionTime)) * 255);
	}
	else
	{
		engine->nDimm = (int8_t)0;
		return true;
	}

	return false;
}

cScript_BrightenScreenPartially::cScript_BrightenScreenPartially(cEngine* _engine, float brightening_speed, int _startdimm, int _enddimm, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	bFreezeTime = freeze_time;
	bAllowForUserControl = playerincontrol;
	fExecutionTime = brightening_speed;
	if (_startdimm >= 0 && _startdimm <= 255)
		nStartDimm = _startdimm;
	else
		nStartDimm = 255;

	if (_enddimm >= 0 && _enddimm <= 255)
		nEndDimm = _enddimm;
	else
		nEndDimm = 0;
}

void cScript_BrightenScreenPartially::Start()
{
	engine->nDimm = nStartDimm;
	bHasStarted = true;
}

bool cScript_BrightenScreenPartially::Update(float fElapsedTime)
{
	//aktualizacja timera
	fTime += fElapsedTime;

	if (engine->nDimm == 0)
		return true;

	if (fTime < fExecutionTime)
	{
		engine->nDimm = (int8_t)(nEndDimm + ((1.0f - (fTime / fExecutionTime)) * (nStartDimm - nEndDimm)));
	}
	else
	{
		engine->nDimm = nEndDimm;
		return true;
	}

	return false;
}

cScript_ChangeMap::cScript_ChangeMap(cEngine* _engine, std::string _map, float _x, float _y)
{
	engine = _engine;
	sMap = _map;
	x = _x;
	y = _y;
}

void cScript_ChangeMap::Start()
{
	cMap* map = cData::get().GetMap(sMap);

	if (map != nullptr)
	{
		engine->ChangeMap(sMap, x, y);
	}
	else
	{
		// handle error
	}

	bHasStarted = true;
}

cScript_AddMessage::cScript_AddMessage(cEngine* _engine, std::vector<std::string> _vecText)
{
	engine = _engine;
	vecText = _vecText;
}

void cScript_AddMessage::Start()
{
	engine->AddMessage(vecText);
	bHasStarted = true;
}

cScript_StickCameraToPlayer::cScript_StickCameraToPlayer()
{
	nCameraOnPlayer = CAMERA_STICK_TO_PLAYER;
}

void cScript_StickCameraToPlayer::Start()
{
	bHasStarted = true;
}

cScript_MoveCameraTo::cScript_MoveCameraTo(cEngine* _engine, float x, float y, float time, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	fToX = x;
	fToY = y;
	fExecutionTime = time;
	nCameraOnPlayer = CAMERA_FREE;
	fStartX = 0.0f;
	fStartY = 0.0f;
	fDistanceToDestX = 0.0f;
	fDistanceToDestY = 0.0f;
	bAllowForUserControl = playerincontrol;
	bFreezeTime = freeze_time;
}

void cScript_MoveCameraTo::Start()
{
	fStartX = engine->fCameraPosX;
	fStartY = engine->fCameraPosY;

	fDistanceToDestX = fToX - fStartX;
	fDistanceToDestY = fToY - fStartY;

	bHasStarted = true;
}

bool cScript_MoveCameraTo::Update(float fElapsedTime)
{
	fTime += fElapsedTime;

	if (fTime < fExecutionTime)
	{
		float vx = fDistanceToDestX / fExecutionTime;
		float vy = fDistanceToDestY / fExecutionTime;

		engine->fCameraPosX += vx * fElapsedTime;
		engine->fCameraPosY += vy * fElapsedTime;
	}
	else
	{
		engine->fCameraPosX = fToX;
		engine->fCameraPosY = fToY;
		return true;
	}

	return false;
}

cScript_ShakeCameraLeaveCameraFree::cScript_ShakeCameraLeaveCameraFree(cEngine* _engine, float time, bool playerincontrol, bool freeze_time)
{
	fExecutionTime = time;
	bAllowForUserControl = playerincontrol;
	bFreezeTime = freeze_time;
	engine = _engine;
	nCameraOnPlayer = CAMERA_FREE;
	fShakeSpeed = 13.0f;
}

void cScript_ShakeCameraLeaveCameraFree::Start()
{
	bHasStarted = true;
}

bool cScript_ShakeCameraLeaveCameraFree::Update(float fElapsedTime)
{
	fTime += fElapsedTime;
	
	if (fTime < fExecutionTime)
	{
		float fDist = 
			sqrtf((engine->pPlayer->px - engine->fCameraPosX) * (engine->pPlayer->px - engine->fCameraPosX) - 
			(engine->pPlayer->py - engine->fCameraPosY) * (engine->pPlayer->py - engine->fCameraPosY));

		if (fDist < 100.0f)
		{
			engine->fCameraPosX += (((rand() / (float)RAND_MAX) * 2.0f) - 1.0f) * fShakeSpeed * fElapsedTime;
			engine->fCameraPosY += (((rand() / (float)RAND_MAX) * 2.0f) - 1.0f) * fShakeSpeed * fElapsedTime;
		}
		else
		{
			engine->fCameraPosX += (engine->pPlayer->px - engine->fCameraPosX);
			engine->fCameraPosY += (engine->pPlayer->py - engine->fCameraPosY);
		}
	
		return false;
	}

	engine->fCameraPosX = engine->pPlayer->px;
	engine->fCameraPosY = engine->pPlayer->py;

	return true;
}

cScript_ShakeCamera::cScript_ShakeCamera(cEngine* _engine, float _time, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	time = _time;
	bAllowForUserControl = playerincontrol;
	bFreezeTime = freeze_time;
}

void cScript_ShakeCamera::Start()
{
	engine->ScriptEngine.AddScriptInFront(new cScript_StickCameraToPlayer());
	engine->ScriptEngine.AddScriptInFront(new cScript_ShakeCameraLeaveCameraFree(engine, time, bAllowForUserControl, bFreezeTime));
	bHasStarted = true;
}

cScript_EmoteLove::cScript_EmoteLove(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime)
{
	engine = _engine;
	owner = _owner;
	bLoopAnimation = _loopanimation;
	fLifeTime = _lifetime;
}

void cScript_EmoteLove::Start()
{
	engine->AddDyn(new cEmoteBubble(engine, owner, cEmoteBubble::EMOTE_BUBBLE_LOVE, bLoopAnimation, fLifeTime));
	bHasStarted = true;
}

cScript_EmoteSilence::cScript_EmoteSilence(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime)
{
	engine = _engine;
	owner = _owner;
	bLoopAnimation = _loopanimation;
	fLifeTime = _lifetime;
}

void cScript_EmoteSilence::Start()
{
	engine->AddDyn(new cEmoteBubble(engine, owner, cEmoteBubble::EMOTE_BUBBLE_SILENCE, bLoopAnimation, fLifeTime));
	bHasStarted = true;
}

cScript_EmoteAlert::cScript_EmoteAlert(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime)
{
	engine = _engine;
	owner = _owner;
	bLoopAnimation = _loopanimation;
	fLifeTime = _lifetime;
}

void cScript_EmoteAlert::Start()
{
	engine->AddDyn(new cEmoteBubble(engine, owner, cEmoteBubble::EMOTE_BUBBLE_ALERT, bLoopAnimation, fLifeTime));
	bHasStarted = true;
}

cScript_EmoteConfusion::cScript_EmoteConfusion(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime)
{
	engine = _engine;
	owner = _owner;
	bLoopAnimation = _loopanimation;
	fLifeTime = _lifetime;
}

void cScript_EmoteConfusion::Start()
{
	engine->AddDyn(new cEmoteBubble(engine, owner, cEmoteBubble::EMOTE_BUBBLE_CONFUSION, bLoopAnimation, fLifeTime));
	bHasStarted = true;
}

cScript_EmoteE::cScript_EmoteE(cEngine* _engine, cDynamic* _owner, bool _loopanimation, float _lifetime)
{
	engine = _engine;
	owner = _owner;
	bLoopAnimation = _loopanimation;
	fLifeTime = _lifetime;
}

void cScript_EmoteE::Start()
{
	engine->AddDyn(new cEmoteBubble(engine, owner, cEmoteBubble::EMOTE_BUBBLE_E, bLoopAnimation, fLifeTime));
	bHasStarted = true;
}

cScript_SetDimm::cScript_SetDimm(cEngine* _engine, int _dimm)
{
	if (_dimm >= 0 && _dimm <= 255)
		nDimm = (int8_t)_dimm;
	else
		nDimm = (int8_t)0;
	engine = _engine;
}

void cScript_SetDimm::Start()
{
	engine->nDimm = nDimm;
	bHasStarted = true;
}

cScript_ShowUI::cScript_ShowUI(cEngine* _engine)
{
	engine = _engine;
}

void cScript_ShowUI::Start()
{
	engine->bShowUI = true;
	bHasStarted = true;
}

cScript_HideUI::cScript_HideUI(cEngine* _engine)
{
	engine = _engine;
}

void cScript_HideUI::Start()
{
	engine->bShowUI = false;
	bHasStarted = true;
}

cScript_DevGiveAndEqiupWeapon::cScript_DevGiveAndEqiupWeapon(cEngine* _engine, cWeapon* _weapon)
{
	engine = _engine;
	weapon = _weapon;
}

void cScript_DevGiveAndEqiupWeapon::Start()
{
	bHasStarted = true;
	engine->PlayerData.currentWeapon = weapon;
}

cScript_Spawn::cScript_Spawn(cEngine* _engine, cDynamic* _dyn)
{
	engine = _engine;
	dynamic = _dyn;
}

void cScript_Spawn::Start()
{
	bHasStarted = true;
	engine->AddDyn(dynamic);
}

cScript_OpenOpenable::cScript_OpenOpenable(cEngine* _engine, cOpenable* _dynamic)
{
	engine = _engine;
	dynamic = _dynamic;
}

void cScript_OpenOpenable::Start()
{
	bHasStarted = true;
	dynamic->Open();
}

cScript_ShakeCameraLeaveCameraFreeAndDimmScreen::cScript_ShakeCameraLeaveCameraFreeAndDimmScreen(cEngine* _engine, float time, bool playerincontrol, bool freeze_time)
{
	engine = _engine;
	bFreezeTime = freeze_time;
	bAllowForUserControl = playerincontrol;
	fExecutionTime = time;
	nCameraOnPlayer = CAMERA_FREE;
	fShakeSpeed = 13.0f;
}

void cScript_ShakeCameraLeaveCameraFreeAndDimmScreen::Start()
{
	bHasStarted = true;
}

bool cScript_ShakeCameraLeaveCameraFreeAndDimmScreen::Update(float fElapsedTime)
{
	fTime += fElapsedTime;

	if (fTime < fExecutionTime)
	{
		float temp_dimm = (fTime / fExecutionTime) * 255;
		if (temp_dimm > (int)engine->nDimm)
			engine->nDimm = (int8_t)temp_dimm;

		float fDist =
			sqrtf((engine->pPlayer->px - engine->fCameraPosX) * (engine->pPlayer->px - engine->fCameraPosX) -
			(engine->pPlayer->py - engine->fCameraPosY) * (engine->pPlayer->py - engine->fCameraPosY));

		if (fDist < 100.0f)
		{
			engine->fCameraPosX += (((rand() / (float)RAND_MAX) * 2.0f) - 1.0f) * fShakeSpeed * fElapsedTime;
			engine->fCameraPosY += (((rand() / (float)RAND_MAX) * 2.0f) - 1.0f) * fShakeSpeed * fElapsedTime;
		}
		else
		{
			engine->fCameraPosX += (engine->pPlayer->px - engine->fCameraPosX);
			engine->fCameraPosY += (engine->pPlayer->py - engine->fCameraPosY);
		}

		return false;
	}

	engine->nDimm = (int8_t)255;
	engine->fCameraPosX = engine->pPlayer->px;
	engine->fCameraPosY = engine->pPlayer->py;

	return true;
}

cScript_HealFor::cScript_HealFor(cDynamicCreature* _dyn, float _healfor)
{
	dynamic = _dyn;
	fHealFor = _healfor;
}

void cScript_HealFor::Start()
{
	bHasStarted = true;
	if (dynamic->fHP + fHealFor > dynamic->fMaxHP)
		dynamic->fHP = dynamic->fMaxHP;
	else
	dynamic->fHP += fHealFor;
}

cScript_SetMaxStamina::cScript_SetMaxStamina(cEngine* _engine, float _newmaxstam)
{
	engine = _engine;
	fNewMaxStamina = _newmaxstam;
}

void cScript_SetMaxStamina::Start()
{
	bHasStarted = true;
	engine->PlayerData.fMaxStamina = fNewMaxStamina;
	engine->PlayerData.fStamina = fNewMaxStamina;
}

cScript_SetMaxHP::cScript_SetMaxHP(cDynamic* _dynamic, float _newmaxhp)
{
	dyn = _dynamic;
	fNewMaxHP = _newmaxhp;
}

void cScript_SetMaxHP::Start()
{
	bHasStarted = true;
	cDynamicCreature* target = dynamic_cast<cDynamicCreature*>(dyn);
	if (target != nullptr)
	{
		target->fMaxHP = fNewMaxHP;
		target->fHP = fNewMaxHP;
	}
}