#include "All_Maps.h"
#include "All_Dynamics.h"
#include "Engine.h"
#include "All_Scripts.h"
#include "All_Items.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cMap1::cMap1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/map1.txt", "map1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap1::PopulateDynamics()
{
	vecDyn.push_back(new cTeleporter(engine, 2.0f, 10.5f, "map2", 23.0f, 12.0f));
	vecDyn.push_back(new cTeleporter(engine, 1.0f, 1.0f, "test map", 7.0f, 6.0f));

	vecDyn.push_back(new cBat(engine, 8.0f, 8.0f));
	vecDyn.push_back(new cBat(engine, 11.0f, 9.0f));
	vecDyn.push_back(new cSignpost(engine, 3.1875f, 3.125f, cData::get().GetDialog("101")));
	vecDyn.push_back(new cFemale(engine, 5.0f, 3.4f));

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cMap2::cMap2(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/map2.txt", "map2", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap2::PopulateDynamics()
{
	vecDyn.push_back(new cSkeleton(engine, 3.0f, 13.0f));
	vecDyn.push_back(new cSkeleton(engine, 3.2f, 6.0f));
	vecDyn.push_back(new cSkeleton(engine, 3.0f, 3.3f));
	vecDyn.push_back(new cSkeleton(engine, 5.3f, 11.2f));
	vecDyn.push_back(new cSkeleton(engine, 5.0f, 7.8f));


	vecDyn.push_back(new cTeleporter(engine, 7.0f, 8.0f, "map1", 3.0f, 2.2f));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cMap_Test::cMap_Test(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/test.txt", "test map", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Test::PopulateDynamics()
{
	vecDyn.push_back(new cTeleporter(engine, 7.0f, 8.0f, "map1", 3.0f, 2.2f));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cMap_Intro1::cMap_Intro1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro1.txt", "intro1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro1::PopulateDynamics()
{
	
}

void cMap_Intro1::FirstEnter()
{
	bHasBeenEntered = true;
	engine->ScriptEngine.AddScript(new cScript_SetDimm(engine, 255));
	engine->ScriptEngine.AddScript(new cScript_HideUI(engine));
	engine->ScriptEngine.AddScript(new cScript_MakeUnconscious(engine->pPlayer));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, true));
	engine->ScriptEngine.AddScript(new cScript_BrightenScreenPartially(engine, 2.0f, 255, 170, false, true));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("101"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("102"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("103"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_BrightenScreenPartially(engine, 1.0f, 170, 120, false, true));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("104"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("105"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("106"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 3.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("107"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("108"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("109"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("110"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("111"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("112"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("113"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("114"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("115"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_ShakeCamera(engine, 2.5f, false, false));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("116"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("117"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("118"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("119"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_BrightenScreenPartially(engine, 1.0f, 120, 40, false, true));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("120"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("121"), true));
	engine->ScriptEngine.AddScript(new cScript_ClearAllDialogs(engine));
	engine->ScriptEngine.AddScript(new cScript_DimmScreenPartially(engine, 1.0f, 40, 255));
	engine->ScriptEngine.AddScript(new cScript_ChangeMap(engine, "intro2", 15.0f, 12.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cMap_Intro2::cMap_Intro2(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro2.txt", "intro2", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro2::PopulateDynamics()
{
	vecDyn.push_back(new cTeleporter(engine, 49.0f, 29.0f, "intro3", 2.0f, 3.5f));
	vecDyn.push_back(new cTeleporter(engine, 49.0f, 30.0f, "intro3", 2.0f, 3.5f));
	vecDyn.push_back(new cTeleporter(engine, 49.0f, 31.0f, "intro3", 2.0f, 3.5f));
}

void cMap_Intro2::FirstEnter()
{
	engine->ScriptEngine.AddScript(new cScript_BrightenScreen(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 0.4f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("122")));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_WakeUp(engine->pPlayer));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cMap_Intro3::cMap_Intro3(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro3.txt", "intro3", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro3::PopulateDynamics()
{
	vecDyn.push_back(new cIronDoor(engine, 8.0f, 17.0f, "iron door1"));
	vecDyn.push_back(new cMap_Intro1_ScriptActivator1(engine, 8.0f, 16.0f));
	vecDyn.push_back(new cMap_Intro1_ScriptActivator2(engine, 21.0f, 13.0f));
	//vecDyn.push_back(new cTorch(engine, 5.0f, 3.0f));
	//vecDyn.push_back(new cTorch(engine, 5.0f, 7.0f));
	//vecDyn.push_back(new cTorch(engine, 5.0f, 11.0f));
	vecDyn.push_back(new cTorch(engine, 5.0f, 15.0f));
	vecDyn.push_back(new cTorch(engine, 7.0f, 12.0f));
	vecDyn.push_back(new cTorch(engine, 14.0f, 12.0f));
	vecDyn.push_back(new cTorch(engine, 18.0f, 12.0f));
}

void cMap_Intro3::FirstEnter()
{
	engine->ScriptEngine.AddScript(new cScript_HideUI(engine));
	engine->ScriptEngine.AddScript(new cScript_SetDimm(engine, 40));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("123")));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 6.0f, true, false));
	engine->ScriptEngine.AddScript(new cScript_EmoteE(engine, engine->GetDyn("iron door1"), true, 0.0f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cMap_Intro4::cMap_Intro4(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro4.txt", "intro4", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro4::PopulateDynamics()
{
	vecDyn.push_back(new cIronDoor(engine, 8.0f, 17.0f, "iron door1"));

	vecDyn.push_back(new cTorch(engine, 5.0f, 3.0f));
	vecDyn.push_back(new cTorch(engine, 5.0f, 7.0f));
	vecDyn.push_back(new cTorch(engine, 5.0f, 11.0f));
	vecDyn.push_back(new cTorch(engine, 5.0f, 15.0f));
	vecDyn.push_back(new cTorch(engine, 7.0f, 12.0f));
	vecDyn.push_back(new cTorch(engine, 14.0f, 12.0f));
	vecDyn.push_back(new cTorch(engine, 18.0f, 12.0f));
	vecDyn.push_back(new cTorch(engine, 32.0f, 13.0f));
	vecDyn.push_back(new cTorch(engine, 38.0f, 46.0f));
	vecDyn.push_back(new cTorch(engine, 40.0f, 46.0f));
	vecDyn.push_back(new cTorch(engine, 34.0f, 27.0f));
	vecDyn.push_back(new cTorch(engine, 40.0f, 37.0f));
	vecDyn.push_back(new cTorch(engine, 31.0f, 32.0f));

	vecDyn.push_back(new cSpikes(engine, 31.0f, 18.0f));
	vecDyn.push_back(new cSpikes(engine, 32.0f, 18.0f));
	vecDyn.push_back(new cSpikes(engine, 33.0f, 18.0f));
	vecDyn.push_back(new cSpikes(engine, 34.0f, 18.0f));

	vecDyn.push_back(new cSpikes(engine, 31.0f, 21.0f));
	vecDyn.push_back(new cSpikes(engine, 32.0f, 21.0f));
	vecDyn.push_back(new cSpikes(engine, 33.0f, 21.0f));
	vecDyn.push_back(new cSpikes(engine, 34.0f, 21.0f));

	vecDyn.push_back(new cSpikes(engine, 38.0f, 40.0f));
	vecDyn.push_back(new cSpikes(engine, 39.0f, 40.0f));
	vecDyn.push_back(new cSpikes(engine, 40.0f, 40.0f));

	vecDyn.push_back(new cTeleporter(engine, 39.0f, 49.0f, "intro5", 20.0f, 1.0f));
}

void cMap_Intro4::FirstEnter()
{
	engine->ScriptEngine.AddScript(new cScript_SetDimm(engine, 40));

	engine->ScriptEngine.AddScript(new cScript_ShakeCamera(engine, 2.5f, false, false));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));

	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("124")));
	engine->ScriptEngine.AddScript(new cScript_ShowUI(engine));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("125")));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("126")));
}

cMap_Intro5::cMap_Intro5(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro5.txt", "intro5", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro5::PopulateDynamics()
{
	vecDyn.push_back(new cIronDoor(engine, 20.0f, 2.0f));

	vecDyn.push_back(new cTorch(engine, 19.0f, 3.0f));
	vecDyn.push_back(new cTorch(engine, 21.0f, 3.0f));
	vecDyn.push_back(new cTorch(engine, 14.0f, 15.0f));
	vecDyn.push_back(new cTorch(engine, 26.0f, 15.0f));
	vecDyn.push_back(new cTorch(engine, 11.0f, 3.0f));
	vecDyn.push_back(new cTorch(engine, 29.0f, 10.0f));

	cLockedIronDoor* temp = new cLockedIronDoor(engine, 20.0f, 18.0f, "iron door2");
	vecDyn.push_back(temp);

	vecDyn.push_back(new cChest(engine, 20.0f, 5.0f, { 
	new cScript_AddMessage(engine, cData::get().GetDialog("128")),
	new cScript_DevGiveAndEqiupWeapon(engine, new cBasic_Sword()),
	new cScript_AddMessage(engine, cData::get().GetDialog("129")),
	new cScript_AddMessage(engine, cData::get().GetDialog("130")),
	new cScript_AddMessage(engine, cData::get().GetDialog("131")),
	new cScript_Wait(engine, 16.0f, true, false),
	new cScript_EmoteAlert(engine, engine->pPlayer, false, 2.5f),
	new cScript_Wait(engine, 2.0f, false, false),
	new cScript_ShakeCamera(engine, 2.5f, false, false),
	new cScript_ClearAllDialogs(engine),
	new cScript_Spawn(engine, new cSkeleton(engine, 22.0f, 16.0f)),
	new cScript_Spawn(engine, new cSkeleton(engine, 20.0f, 25.0f)),
	new cScript_Spawn(engine, new cSkeleton(engine, 20.0f, 30.0f)),
	new cScript_AddDialog(engine, cData::get().GetDialog("132"), false),
	new cScript_OpenOpenable(engine, temp)
		}, "chest1"));

	vecDyn.push_back(new cSpikes(engine, 19.0f, 27.0f));
	vecDyn.push_back(new cSpikes(engine, 20.0f, 27.0f));
	vecDyn.push_back(new cSpikes(engine, 21.0f, 27.0f));
	vecDyn.push_back(new cTorch(engine, 24.0f, 28.0f));
	vecDyn.push_back(new cTorch(engine, 16.0f, 28.0f));
	vecDyn.push_back(new cTorch(engine, 30.0f, 36.0f));
	vecDyn.push_back(new cTorch(engine, 35.0f, 32.0f));

	vecDyn.push_back(new cTeleporter(engine, 39.0f, 32.0f, "intro6", 1.0f, 25.0f));
	vecDyn.push_back(new cTeleporter(engine, 39.0f, 33.0f, "intro6", 1.0f, 26.0f));
	vecDyn.push_back(new cTeleporter(engine, 39.0f, 34.0f, "intro6", 1.0f, 27.0f));

}

void cMap_Intro5::FirstEnter()
{
	engine->ScriptEngine.AddScript(new cScript_SetDimm(engine, 40));
	engine->ScriptEngine.AddScript(new cScript_AddDialog(engine, cData::get().GetDialog("127")));
	engine->ScriptEngine.AddScript(new cScript_EmoteE(engine, engine->GetDyn("chest1"), true, 6.0f));
	engine->ScriptEngine.AddScript(new cScript_EmoteE(engine, engine->GetDyn("iron door"), true, 2.0f));
}

cMap_Intro6::cMap_Intro6(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/intro6.txt", "intro6", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Intro6::PopulateDynamics()
{
	engine->ScriptEngine.AddScript(new cScript_SetDimm(engine, 40));
	vecDyn.push_back(new cTorch(engine, 2.0f, 28.0f));
	vecDyn.push_back(new cTorch(engine, 4.0f, 28.0f));
	vecDyn.push_back(new cTorch(engine, 4.0f, 24.0f));
	vecDyn.push_back(new cTorch(engine, 2.0f, 24.0f));
	vecDyn.push_back(new cMap_Intro6_ScriptActivator1(engine, 6.0f, 25.0f));
}

cMap_Plains1::cMap_Plains1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/plains1.txt", "plains1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Plains1::PopulateDynamics()
{
	vecDyn.push_back(new cSlime(engine, 48.0f, 11.0f));
	vecDyn.push_back(new cSlime(engine, 38.0f, 3.0f));
	vecDyn.push_back(new cSlime(engine, 22.0f, 6.0f));
	vecDyn.push_back(new cSlime(engine, 19.0f, 8.0f));
	vecDyn.push_back(new cSlime(engine, 10.0f, 27.0f));
	vecDyn.push_back(new cSlime(engine, 36.0f, 28.0f));
	vecDyn.push_back(new cSlime(engine, 27.0f, 33.0f));
	vecDyn.push_back(new cSlime(engine, 30.0f, 6.0f));
	vecDyn.push_back(new cSkeleton(engine, 50.0f, 30.0f));
	vecDyn.push_back(new cStairwayDown(engine, 51.0f, 32.0f, "dungeon1", 2.0f, 8.0f));
	vecDyn.push_back(new cTeleporter(engine, 59.0f, 5.0f, "village1", 1.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 59.0f, 6.0f, "village1", 1.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 59.0f, 7.0f, "village1", 1.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 59.0f, 8.0f, "village1", 1.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 22.0f, "plains2", 39.0f, 23.0f));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 23.0f, "plains2", 39.0f, 24.0f));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 24.0f, "plains2", 39.0f, 25.0f));
}

void cMap_Plains1::FirstEnter()
{
	bHasBeenEntered = true;
	engine->ScriptEngine.AddScript(new cScript_DevGiveAndEqiupWeapon(engine, new cBasic_Sword));
	engine->ScriptEngine.AddScript(new cScript_SetMaxStamina(engine, 20.0f));
	engine->ScriptEngine.AddScript(new cScript_SetMaxHP(engine->Player(), 22.0f));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 2.5f, false, false));
	//engine->ScriptEngine.AddScript(new cScript_MakeUnconscious(engine->Player()));
	engine->ScriptEngine.AddScript(new cScript_BrightenScreen(engine, 3.5f, false, false));
	engine->ScriptEngine.AddScript(new cScript_Wait(engine, 1.0f, false, false));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("141")));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("151")));
	engine->ScriptEngine.AddScript(new cScript_AddMessage(engine, cData::get().GetDialog("142")));
	engine->ScriptEngine.AddScript(new cScript_MoveTo(engine->Player(), 3.0f, 23.0f, 1.0f, false));
	engine->ScriptEngine.AddScript(new cScript_HealFor(engine->Player(), 15.0f));
	//engine->ScriptEngine.AddScript(new cScript_WakeUp(engine->Player()));
}

void cMap_Dungeon1::PopulateDynamics()
{
	vecDyn.push_back(new cSkeleton(engine, 6.0f, 5.0f));
	vecDyn.push_back(new cStairwayUp(engine, 3.0f, 8.0f, "plains1", 50.0f, 32.0f));
	vecDyn.push_back(new cChest(engine, 6.0f, 4.0f, {
		new cScript_AddDialog(engine, cData::get().GetDialog("143")),
		new cScript_DevGiveAndEqiupWeapon(engine, new cSteel_Sword()) }));
}

cMap_Dungeon1::cMap_Dungeon1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/dungeon1.txt", "dungeon1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Village1::PopulateDynamics()
{
	vecDyn.push_back(new cSignpost(engine, 6.0f, 6.0f, cData::get().GetDialog("144")));
	vecDyn.push_back(new cFemale(engine, 17.0f, 7.0f, cData::get().GetDialog("145")));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 6.0f, "plains1", 58.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 7.0f, "plains1", 58.0f, 7.0f));
	vecDyn.push_back(new cTeleporter(engine, 0.0f, 8.0f, "plains1", 58.0f, 7.0f));
}

cMap_Village1::cMap_Village1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/village1.txt", "village1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Plains2::PopulateDynamics()
{
	vecDyn.push_back(new cTeleporter(engine, 40.0f, 22.0f, "plains1", 1.0f, 22.0f));
	vecDyn.push_back(new cTeleporter(engine, 40.0f, 23.0f, "plains1", 1.0f, 23.0f));
	vecDyn.push_back(new cTeleporter(engine, 40.0f, 24.0f, "plains1", 1.0f, 24.0f));

	vecDyn.push_back(new cChest(engine, 37.0f, 3.0f, {
		new cScript_AddMessage(engine, cData::get().GetDialog("146")),
		new cScript_AddMessage(engine, cData::get().GetDialog("147")),
		new cScript_SetMaxHP(engine->pPlayer, 35.0f) }));

	vecDyn.push_back(new cSkeleton(engine, 35.0f, 4.0f));
	vecDyn.push_back(new cSlime(engine, 38.0f, 7.0f));
	vecDyn.push_back(new cSlime(engine, 8.0f, 12.0f));
	vecDyn.push_back(new cSlime(engine, 11.0f, 12.0f));
	vecDyn.push_back(new cSlime(engine, 10.0f, 6.0f));
	vecDyn.push_back(new cBat(engine, 23.0f, 10.0f));
	vecDyn.push_back(new cBat(engine, 8.0f, 23.0f));

	vecDyn.push_back(new cTeleporter(engine, 2.0f, 9.0f, "cave1", 8.0f, 12.5f));
}

cMap_Plains2::cMap_Plains2(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/plains2.txt", "plains2", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}

void cMap_Cave1::PopulateDynamics()
{
	vecDyn.push_back(new cSignpost(engine, 8.0f, 10.0f, cData::get().GetDialog("148")));
	vecDyn.push_back(new cSignpost(engine, 6.0f, 5.0f, cData::get().GetDialog("149")));
	vecDyn.push_back(new cSignpost(engine, 8.0f, 5.0f, cData::get().GetDialog("150")));
	vecDyn.push_back(new cTorch(engine, 10.0f, 13.0f));
	vecDyn.push_back(new cTorch(engine, 6.0f, 13.0f));
	vecDyn.push_back(new cTeleporter(engine, 8.0f, 14.0f, "plains2", 2.0f, 10.5f));
}

cMap_Cave1::cMap_Cave1(cEngine* _engine) : cMap(_engine)
{
	Create(L"data/maps/cave1.txt", "cave1", cData::get().GetSprite("tileset1"));
	PopulateDynamics();
}