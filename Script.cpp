#include "Script.h"

void cScriptEngine::UpdateScripts(float fElapsedTime)
{
	// je¿eli lista nie jest pusta to aktualizuj pierwszy skrypt w kolejce
	if (!listScripts.empty())
	{
		// jeœli pierwszy skrypt w kolejce siê jeszcze nie rozpocz¹³ to go rozpocznij
		if (listScripts.front()->bHasStarted == false)
		{
			// rozpocznij skrypt i obliczanie potrzebnych mu danych
			listScripts.front()->Start();

			// ustaw mo¿liwoœæ ruchu gracza w trakcie wykonywania skryptu
			// w zale¿noœci od w³snoœci skryptu
			if (listScripts.front()->bAllowForUserControl == false)
				bPlayerInControl = false;
			else
				bPlayerInControl = true;

			//ustaw zamro¿enie czasu w zale¿noœci od skryptu
			if (listScripts.front()->bFreezeTime == false)
				bTimeIsFreezed = false;
			else
				bTimeIsFreezed = true;

			//ustaw mo¿liwoœæ pominiêcia skryptu wy³¹cznie manualnie
			if (listScripts.front()->bWaitForSkip == false)
				bWaitForManualSkip = false;
			else
				bWaitForManualSkip = true;

			//ustaw œledzenie gracza kamer¹
			if (listScripts.front()->nCameraOnPlayer == cScript::CAMERA_STICK_TO_PLAYER)
				bCameraFollowsPlayer = true;
			
			if (listScripts.front()->nCameraOnPlayer == cScript::CAMERA_FREE)
				bCameraFollowsPlayer = false;

		}
		
		if(listScripts.front()->bHasStarted == true) // jeœli przy rozpoczêciu obs³ugi skryptów zosta³y dodane jakieœ nowe na pocz¹tku kolejki to zostanie to wychwycone
			if(bWaitForManualSkip == false)		// jeœli obecnie wykonywany skrypt nie musi zostaæ zakoñczony wy³¹cznie rêcznym pominiêciem
				if (listScripts.front()->Update(fElapsedTime))	// jeœli skrypt uza ¿e siê skoñczy³ to go usuñ
					listScripts.pop_front();
	}
	else
	{
		bPlayerInControl = true;
		bTimeIsFreezed = false;
		bWaitForManualSkip = false;
		//kamera samodzielnie nie przykleja siê do gracza!
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
