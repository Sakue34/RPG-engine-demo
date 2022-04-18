#include "Script.h"

void cScriptEngine::UpdateScripts(float fElapsedTime)
{
	// je�eli lista nie jest pusta to aktualizuj pierwszy skrypt w kolejce
	if (!listScripts.empty())
	{
		// je�li pierwszy skrypt w kolejce si� jeszcze nie rozpocz�� to go rozpocznij
		if (listScripts.front()->bHasStarted == false)
		{
			// rozpocznij skrypt i obliczanie potrzebnych mu danych
			listScripts.front()->Start();

			// ustaw mo�liwo�� ruchu gracza w trakcie wykonywania skryptu
			// w zale�no�ci od w�sno�ci skryptu
			if (listScripts.front()->bAllowForUserControl == false)
				bPlayerInControl = false;
			else
				bPlayerInControl = true;

			//ustaw zamro�enie czasu w zale�no�ci od skryptu
			if (listScripts.front()->bFreezeTime == false)
				bTimeIsFreezed = false;
			else
				bTimeIsFreezed = true;

			//ustaw mo�liwo�� pomini�cia skryptu wy��cznie manualnie
			if (listScripts.front()->bWaitForSkip == false)
				bWaitForManualSkip = false;
			else
				bWaitForManualSkip = true;

			//ustaw �ledzenie gracza kamer�
			if (listScripts.front()->nCameraOnPlayer == cScript::CAMERA_STICK_TO_PLAYER)
				bCameraFollowsPlayer = true;
			
			if (listScripts.front()->nCameraOnPlayer == cScript::CAMERA_FREE)
				bCameraFollowsPlayer = false;

		}
		
		if(listScripts.front()->bHasStarted == true) // je�li przy rozpocz�ciu obs�ugi skrypt�w zosta�y dodane jakie� nowe na pocz�tku kolejki to zostanie to wychwycone
			if(bWaitForManualSkip == false)		// je�li obecnie wykonywany skrypt nie musi zosta� zako�czony wy��cznie r�cznym pomini�ciem
				if (listScripts.front()->Update(fElapsedTime))	// je�li skrypt uza �e si� sko�czy� to go usu�
					listScripts.pop_front();
	}
	else
	{
		bPlayerInControl = true;
		bTimeIsFreezed = false;
		bWaitForManualSkip = false;
		//kamera samodzielnie nie przykleja si� do gracza!
	}
}

void cScriptEngine::SkipAllScripts()
{
	for (int i = 0; i < listScripts.size(); i ++)
	{
		listScripts.front()->Start();
		listScripts.pop_front();
	}
}

cScriptEngine::cScriptEngine()
{
	bPlayerInControl = true;
	bTimeIsFreezed = false;
	bWaitForManualSkip = false;
	bCameraFollowsPlayer = true;
}
