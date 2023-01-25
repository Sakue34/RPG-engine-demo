#include "All_Dynamics.h"
#include "Engine.h"
#include "Data.h"
#include "All_Scripts.h"

// Miecz gracza (obiekt dynamiczny)
cPlayerMelee::cPlayerMelee(cEngine* _engine, float _px, float _py) 
	: cDynamic(_engine, "player melee", _px, _py, cData::get().GetSprite("player melee"), false, false, true)
{
	nDirection = engine->pPlayer->nDirection;
	fWidth = 0.875f;
	fHeight = 0.875f;
	bIsProjectile = true;
	fProjectileTime = engine->pPlayer->stats.fMeleeAttackImmobilityCooldown;
	nLayer = 3;
}

bool cPlayerMelee::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if(player != nullptr)
		if(target->sName != "player")
			if(target->bFriendly == false)
				if(nature == WALK_ON)
					dynamic_cast<cDynamicCreature*>(player)->PerformInstantAttack(target);
	return false;
}

void cPlayerMelee::DrawSelf(float fOffsetX, float fOffsetY)
{
	switch (nDirection)
	{
	case NORTH:
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, 0,
			(int)(fWidth * 16), (int)(fHeight * 16));
		return;
		break;
	case EAST:
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(16 * fWidth), 0,
			(int)(fWidth * 16), (int)(fHeight * 16));
		return;
		break;
	case SOUTH:
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(32 * fWidth), 0,
			(int)(fWidth * 16), (int)(fHeight * 16));
		return;
		break;
	case WEST:
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(48 * fWidth), 0,
			(int)(fWidth * 16), (int)(fHeight * 16));
		return;
		break;
	}
}

// Bañka-emotikona
cEmoteBubble::cEmoteBubble(cEngine* engine, cDynamic* _parent, EMOTE_BUBBLE _type, bool _loopanimation, float _lifetime) :
	cDynamic(engine, "emote bubble", _parent->px, _parent->py - 1.0f, cData::get().GetSprite("emote bubble"), false, false)
{
	nFrame = 0;
	nLayer = 4;
	fWidth = 1.0f;
	fHeight = 1.0f;
	bIsProjectile = true;

	if (_lifetime == 0.0f)
		bIsProjectile = false;
	else
		fProjectileTime = _lifetime;
		
	bLoopAnimation = _loopanimation;
	parent = _parent;
	nEmote = _type;
}

void cEmoteBubble::Update(float fElapsedTime, cDynamic* player)
{
	fTime += fElapsedTime;

	float fFrameTime = 0.2f;

	for (int i = 0; i < 8; i++)
	{
		if (fTime >= i * fFrameTime)
			nFrame = i;
	}

	if(bLoopAnimation)
		if (fTime >= 7 * fFrameTime)
			fTime = 0.0f;

	if (parent != nullptr)
	{
		px = parent->px;
		py = parent->py - 1.0f;
	}
	else
		bIsRedundant = true;
}

void cEmoteBubble::DrawSelf(float fOffsetX, float fOffsetY)
{
	switch (nEmote)
	{
		case EMOTE_BUBBLE_LOVE:
		{
			engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 0,
				(int)(fWidth * 16), (int)(fHeight * 16));
			return;
			break;
		}
		case EMOTE_BUBBLE_SILENCE:
		{
			engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 16,
				(int)(fWidth * 16), (int)(fHeight * 16));
			return;
			break;
		}
		case EMOTE_BUBBLE_ALERT:
		{
			engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 32,
				(int)(fWidth * 16), (int)(fHeight * 16));
			return;
			break;
		}
		case EMOTE_BUBBLE_CONFUSION:
		{
			engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 48,
				(int)(fWidth * 16), (int)(fHeight * 16));
			return;
			break;
		}
		case EMOTE_BUBBLE_E:
		{
			engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 64,
				(int)(fWidth * 16), (int)(fHeight * 16));
			return;
			break;
		}
		default:
			break;
	}
}

// Teleporter
cTeleporter::cTeleporter(cEngine* _engine, float _px, float _py, std::string map, float _x, float _y)
	: cDynamic(_engine, "teleporter", _px, _py, nullptr)
{
	fWidth = 1.0f;
	fHeight = 1.0f;
	bSolidVsDynamic = false;
	sTargetMap = map;
	fToX = _x;
	fToY = _y;
	nLayer = 0;
}

bool cTeleporter::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
	{
		//if (nature == INTERACT_KEY)
		//{
		//	engine->ChangeMap(sTargetMap, fToX, fToY);
		//	return true;
		//}
		/*else*/ if (nature == WALK_ON)
		{
			engine->ChangeMap(sTargetMap, fToX, fToY);
			return true;
		}
		//dev
		//if (nature == TALK)
		//{
		//	std::cout << "Do you really want to talk with a teleporter?" << std::endl;
		//}
		// /dev
	}
	return false;
}

// Aktywator skryptów 1 - cMap_Intro1
cMap_Intro1_ScriptActivator1::cMap_Intro1_ScriptActivator1(cEngine* _engine, float _px, float _py) 
	: cDynamic(_engine, "intro1 script1",_px,_py, nullptr, false, false)
{
	fWidth = 1.0f;
	fHeight = 1.0f;
	bActivated = false;
}

bool cMap_Intro1_ScriptActivator1::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (!bActivated)
	{
		if (target->sName == "player")
		{
			if (nature == WALK_ON)
			{
				bActivated = true;
				engine->GetCurrentMap()->RemoveDynamic(8);
			}
		}
	}

	return false;
}

// Aktywator skryptów 2 - cMap_Intro1
cMap_Intro1_ScriptActivator2::cMap_Intro1_ScriptActivator2(cEngine* _engine, float _px, float _py)
	: cDynamic(_engine, "intro1 script2", _px, _py, nullptr, false, false)
{
	fWidth = 1.0f;
	fHeight = 2.0f;
	bActivated = false;
}

bool cMap_Intro1_ScriptActivator2::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (!bActivated)
	{
		if (target->sName == "player")
		{
			if (nature == WALK_ON)
			{
				bActivated = true;
				engine->ScriptEngine.AddScript(new cScript_ChangeMap(engine, "intro4", target->px, target->py));
			}
		}
	}

	return false;
}
// Aktywator skryptów - cMap_Intro6
cMap_Intro6_ScriptActivator1::cMap_Intro6_ScriptActivator1(cEngine* _engine, float _px, float _py) 
	: cDynamic(_engine, "intro6 script1", _px, _py, nullptr, false, false)
{
	fWidth = 1.0f;
	fHeight = 3.0f;
	bActivated = false;
}

bool cMap_Intro6_ScriptActivator1::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (!bActivated)
	{
		if (target->sName == "player")
		{
			if (nature == WALK_ON)
			{
				bActivated = true;
				engine->ScriptEngine.AddScript(new cScript_MoveTo(target, 8.0f, 26.0f, 2.5f, false));
				engine->ScriptEngine.AddScript(new cScript_Wait(engine, 0.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_EmoteSilence(engine, target, false, 2.5f));
				engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("134"), true));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_MoveTo(target, 7.2f, 26.0f, 1.0f, false));
				engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_MoveTo(target, 8.0f, 26.0f, 1.0f, false));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("135"), true));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_MoveTo(target, 20.0f, 26.0f, 9.0f, false));
				engine->ScriptEngine.AddScript(new cScript_ShakeCamera(engine, 2.5f));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("136"), true));
				engine->ScriptEngine.AddScript(new cScript_Wait(engine, 0.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_EmoteAlert(engine, target, false, 1.5f));
				engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("137"), true));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("138"), true));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_MoveTo(target, 19.8f, 26.0f, 0.3f, false));
				engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("139"), true));
				engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
				engine->ScriptEngine.AddScript(new cScript_ShakeCameraLeaveCameraFreeAndDimmScreen(engine, 3.5f, false, false));
				engine->ScriptEngine.AddScript(new cScript_StickCameraToPlayer);
				engine->ScriptEngine.AddScript(new cScript_ChangeMap(engine, "plains1", 2.0f, 23.0f));
			}
		}
	}

	return false;
}

//Kolce:
cSpikes::cSpikes(cEngine* _engine, float _px, float _py) 
	: cDynamic(_engine, "spikes", _px, _py, cData::get().GetSprite("spikes"), true, false)
{
	nLayer = 0;
	fWidth = 1.0f;
	fHeight = 1.0f;
	nFrame = 0;
	bDanger = false;
}

bool cSpikes::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	//if (target->sName == "player")
	//{
		if (nature == WALK_ON)
		{
			if (bDanger)
			{
				if (dynamic_cast<cDynamicCreature*>(target) != nullptr)
				{
					if (!target->bInvincible)
					{
						//nadaj obra¿enia
						target->ReceiveDamage(dynamic_cast<cDynamicCreature*>(target)->fMaxHP / 10.0f);
						//oblicz odrzut
						float fTargetX = target->px - px;
						float fTargetY = target->py - py;
						float fDist = sqrtf(fTargetX * fTargetX + fTargetY * fTargetY);
						target->Knockback((fTargetX / fDist) * 4.0f, (fTargetY / fDist) * 4.0f, 0.5f);
					}
				}
			}
		}
	//}
	return false;
}

void cSpikes::Update(float fElapsedTime, cDynamic* player)
{
	fTime += fElapsedTime;

	if (fTime > 4.0f)
		fTime = 4.0f;

	if (fTime >= 0.0f && fTime < 2.0f)
	{
		nFrame = 0;
		bDanger = false;
	}
	if (fTime >= 2.0f && fTime < 2.2f)
	{
		nFrame = 1;
		bDanger = false;
	}
	if (fTime >= 2.2f )
	{
		nFrame = 2;
		bDanger = true;
	}
	if (fTime >= 3.7f && fTime <= 4.0f)
	{
		nFrame = 1;
		bDanger = false;
	}

	if (fTime == 4.0f)
		fTime = 0.0f;

}

void cSpikes::DrawSelf(float fOffsetX, float fOffsetY)
{
	engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, nFrame * 16, 0,
		(int)(fWidth * 16), (int)(fHeight * 16));
}

// Pochodnia
cTorch::cTorch(cEngine* _engine, float _px, float _py) : c3FrameAnimatedDynamic(_engine, "torch", _px, _py, cData::get().GetSprite("torch"), true, true)
{
}

// ¯elazne drzwi
cIronDoor::cIronDoor(cEngine* _engine, float _px, float _py) 
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("iron door"), "iron door", true, true)
{
}

cIronDoor::cIronDoor(cEngine* _engine, float _px, float _py, std::string _name)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("iron door"), _name, true, true)
{
}

void cIronDoor::Update(float fElapsedTime, cDynamic* player)
{
	if (bAnimOpening)
	{

		if (fTime < (4 * fFrameTime) - fElapsedTime)
		{
			fTime += fElapsedTime;
			nFrame = 0;
			for (int i = 0; i < 4; i++)
			{
				if (fTime > i * fFrameTime)
					nFrame = i;
			}
		}
		else
		{
			fTime = 3 * fFrameTime;
			bAnimOpening = false;
			bOpen = true;
			fWidth = 0.25f; // ró¿nica pomiêdzy normalnym cOpenable a cIronDoor
			if (!bHasBeenYetOpened)
			{
				bHasBeenYetOpened = true;
				FirstOpen();
			}
		}
	}

	if (bAnimClosing)
	{
		fWidth = 1.0f;

		if (fTime < (4 * fFrameTime) - fElapsedTime)
		{
			fTime += fElapsedTime;
			nFrame = 0;
			for (int i = 0; i < 4; i++)
			{
				if (fTime > i * fFrameTime)
					nFrame = 3 - i;
			}
		}
		else
		{
			fTime = 3 * fFrameTime;
			bAnimClosing = false;
			bOpen = false;
		}
	}
}

// Zakmniête ¿elazne drzwi
cLockedIronDoor::cLockedIronDoor(cEngine* _engine, float _px, float _py)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("iron door"), "iron door", true, true)
{
}

cLockedIronDoor::cLockedIronDoor(cEngine* _engine, float _px, float _py, std::string _name)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("iron door"), _name, true, true)
{
}

void cLockedIronDoor::Update(float fElapsedTime, cDynamic* player)
{
	if (bAnimOpening)
	{
		if (fTime < (4 * fFrameTime) - fElapsedTime)
		{
			fTime += fElapsedTime;
			nFrame = 0;
			for (int i = 0; i < 4; i++)
			{
				if (fTime > i * fFrameTime)
					nFrame = i;
			}
		}
		else
		{
			fTime = 3 * fFrameTime;
			bAnimOpening = false;
			bOpen = true;
			fWidth = 0.25f; // ró¿nica pomiêdzy normalnym cOpenable a cIronDoor
			if (!bHasBeenYetOpened)
			{
				bHasBeenYetOpened = true;
				FirstOpen();
			}
		}
	}

	if (bAnimClosing)
	{
		fWidth = 1.0f;

		if (fTime < (4 * fFrameTime) - fElapsedTime)
		{
			fTime += fElapsedTime;
			nFrame = 0;
			for (int i = 0; i < 4; i++)
			{
				if (fTime > i * fFrameTime)
					nFrame = 3 - i;
			}
		}
		else
		{
			fTime = 3 * fFrameTime;
			bAnimClosing = false;
			bOpen = false;
		}
	}
}

bool cLockedIronDoor::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
	{
		if (nature == TALK)
		{
			if (!bOpen)
				engine->AddDialog(cData::get().GetDialog("133"));
		}
	}
	return false;
}

// Skrzynia
cChest::cChest(cEngine* _engine, float _px, float _py)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("chest"), "chest", true, true)
{
}

cChest::cChest(cEngine* _engine, float _px, float _py, std::vector<cScript*> _scripts)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("chest"), "chest", true, true)
{
	vecScripts = _scripts;
}

cChest::cChest(cEngine* _engine, float _px, float _py, std::vector<cScript*> _scripts, std::string _name)
	: cOpenable(_engine, _px, _py, cData::get().GetSprite("chest"), _name, true, true)
{
	vecScripts = _scripts;
}

void cChest::FirstOpen()
{
	for (unsigned i = 0; i < vecScripts.size(); i++)
	{
		engine->ScriptEngine.AddScript(vecScripts[i]);
	}
}

// Szkielet
cSkeleton::cSkeleton(cEngine* engine, float _px, float _py) 
	: cDynamicCreature(engine, "skeleton", _px, _py, cData::get().GetSprite("skeleton"), true, true, 0.625f, 0.9375f, STATE_STANDING, 5.0f, false)
{
	fMaxWalkingVel = 1.0f;
	stats.fMeleeAttackImmobilityCooldown = 0.1f;
}

void cSkeleton::UpdateAI(float fElapsedTime, cDynamic* player)
{
	AI_SimpleFollowHostile(fElapsedTime, player);
}

// Nietoperz
cBat::cBat(cEngine* engine, float _px, float _py)
	: cDynamicCreature(engine, "bat", _px, _py, cData::get().GetSprite("bat"), true, false, 1.0f, 0.8125f, STATE_WALKING, 5.0f, false, 3)
{
	fMaxWalkingVel = 3.0f;
	fAIActivationDistance = 6.0f;
	fAIUpdateInterval = 2.0f;
	bWalkAnimationAlwaysOn = true;
	stats.fDmg = 0.8f;
	stats.fDmgFluct = 0.8f;
	stats.fMeleeAttackImmobilityCooldown = 0.4f;
	fKnockbackSpeedDeclineMultiplier = 0.8f;
	fProneToKnockbackMultiplier = 1.2f;
}

// Tabliczka
void cBat::UpdateAI(float fElapsedTime, cDynamic* player)
{
	AI_SimpleFollowHostile(fElapsedTime, player);
}

cSignpost::cSignpost(cEngine* engine, float _px, float _py, std::vector<std::string> _vecText) 
	: cDynamic(engine,"signpost",_px,_py,cData::get().GetSprite("signpost"),false,true)
{
	vecText = _vecText;
}

bool cSignpost::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
		if (nature == TALK)
			engine->AddMessage(vecText);
	return false;
}

// Schody w dó³

cStairwayDown::cStairwayDown(cEngine* engine, float _px, float _py, std::string map, float _x, float _y) 
	: cDynamic(engine, "stairway down", _px, _py, cData::get().GetSprite("stairway down"), true, false)
{
	fWidth = 1.0f;
	fHeight = 1.0f;
	sTargetMap = map;
	fToX = _x;
	fToY = _y;
}

bool cStairwayDown::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
	{
		if (nature == TALK || nature == INTERACT_KEY)
		{
			engine->ChangeMap(sTargetMap, fToX, fToY);
			return true;
		}
	}
	return false;
}

// Schody do góry

cStairwayUp::cStairwayUp(cEngine* engine, float _px, float _py, std::string map, float _x, float _y)
	: cDynamic(engine, "stairway up", _px, _py, cData::get().GetSprite("stairway up"), true, true)
{
	fWidth = 1.0f;
	fHeight = 1.0f;
	sTargetMap = map;
	fToX = _x;
	fToY = _y;
}

bool cStairwayUp::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
	{
		if (nature == TALK)
		{
			engine->ChangeMap(sTargetMap, fToX, fToY);
			return true;
		}
	}
	return false;
}

// Kobieta NPC
cFemale::cFemale(cEngine* engine, float _px, float _py) 
	: cDynamicCreature(engine, "female", _px, _py, cData::get().GetSprite("female"), true, true, 0.875f, 1.0f, STATE_STANDING, 2.5f, true)
{
	bHasSthToSay = false;
}

cFemale::cFemale(cEngine* engine, float _px, float _py, std::vector<std::string> _vecText)
	: cDynamicCreature(engine, "female", _px, _py, cData::get().GetSprite("female"), true, true, 0.875f, 1.0f, STATE_STANDING, 2.5f, true)
{
	bHasSthToSay = true;
	vecText = _vecText;
}

void cFemale::UpdateAI(float fElapsedTime, cDynamic* player)
{
	AI_Default(fElapsedTime, player);
}

bool cFemale::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (bHasSthToSay)
	{
		if (target->sName == "player")
		{
			if (nature == TALK)
			{
				engine->AddDialog(vecText);
			}
		}
	}
	return false;
}

// Slime
cSlime::cSlime(cEngine* engine, float _px, float _py) : cDynamicCreature(engine, "slime",_px, _py, cData::get().GetSprite("slime"), true, true, 1.0f, 0.8125f, STATE_STANDING, 6.0f, false)
{
	fMaxWalkingVel = 1.4f;
	stats.fDmg = 0.6f;
	stats.fDmgFluct = 0.2f;
	fAIActivationDistance = 6.0f;
	stats.fMeleeAttackImmobilityCooldown = 0.5f;
	fAIUpdateInterval = 0.6f;
}

void cSlime::UpdateAI(float fElapsedTime, cDynamic* player)
{
	AI_SimpleFollowHostile(fElapsedTime, player);
}