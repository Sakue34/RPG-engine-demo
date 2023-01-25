#include "Engine.h"
#include "Dynamic.h"
#include "Map.h"
#include "All_Items.h"
#include "All_Scripts.h"

float cEngine::DistanceBetweenDynCenterPow2(cDynamic* A, cDynamic* B)
{
	float ax = A->px + A->fWidth / 2.0f;
	float ay = A->py + A->fHeight / 2.0f;
	float bx = B->px + B->fWidth / 2.0f;
	float by = B->py + B->fHeight / 2.0f;
	return (bx - ax)*(bx - ax) + (by - ay)*(by - ay);
}

void cEngine::DrawTinyText(std::string sText, int x, int y) // 4x4
{
	int i = 0;
	for (auto c : sText)
	{
		int sx = ((c - 32) % 32) * 4;
		int sy = ((c - 32) / 32) * 4;
		DrawPartialSprite(x + i * 4, y, m_sprFont4x4, sx, sy, 4, 4);
		i++;
	}
}

void cEngine::DrawSmallText(std::string sText, int x, int y) // 4x6
{
	int i = 0;
	for (auto c : sText)
	{
		int sx = ((c - 32) % 32) * 4;
		int sy = ((c - 32) / 32) * 6;
		DrawPartialSprite(x + i * 4, y, m_sprFont4x6, sx, sy, 4, 6);
		i++;
	}
}

void cEngine::Draw4x5Text(std::string sText, int x, int y)
{
	int i = 0;
	for (auto c : sText)
	{
		int sx = ((c - 32) % 16) * 4;
		int sy = ((c - 32) / 16) * 5;
		DrawPartialSprite(x + i * 5, y, m_sprFont4x5, sx, sy, 4, 5);
		i++;
	}
}

void cEngine::DrawText(std::string sText, int x, int y, TEXT_COLOUR colour)
{
	switch (colour)
	{
		case TXT_DARK_RED:
		{
			int i = 0;
			for (auto c : sText)
			{
				int sx = ((c - 32) % 16) * 6;
				int sy = ((c - 32) / 16) * 8;
				DrawPartialSprite(x + i * 6, y, m_sprFont6x8_dark_red, sx, sy, 6, 8);
				i++;
			}
			break;
		}
		case TXT_RED:
		{
			int i = 0;
			for (auto c : sText)
			{
				int sx = ((c - 32) % 16) * 6;
				int sy = ((c - 32) / 16) * 8;
				DrawPartialSprite(x + i * 6, y, m_sprFont6x8_red, sx, sy, 6, 8);
				i++;
			}
			break;
		}
		case TXT_BLACK:
		{
			int i = 0;
			for (auto c : sText)
			{
				int sx = ((c - 32) % 16) * 6;
				int sy = ((c - 32) / 16) * 8;
				DrawPartialSprite(x + i * 6, y, m_sprFont6x8_black, sx, sy, 6, 8);
				i++;
			}
			break;
		}
		case TXT_WHITE:
		{
			int i = 0;
			for (auto c : sText)
			{
				int sx = ((c - 32) % 16) * 6;
				int sy = ((c - 32) / 16) * 8;
				DrawPartialSprite(x + i * 6, y, m_sprFont6x8_white, sx, sy, 6, 8);
				i++;
			}
			break;
		}
		default:
			break;
	}
}

void cEngine::Draw8x12Text(std::string sText, int x, int y) 
{
	int i = 0;
	for (auto c : sText)
	{
		int sx = ((c - 32) % 16) * 8;
		int sy = ((c - 32) / 16) * 12;
		DrawPartialSprite(x + i * 8, y, m_sprFont8x12, sx, sy, 8, 12);
		i++;
	}
}

void cEngine::Draw16x16Text(std::string sText, int x, int y, TEXT_COLOUR colour)
{
	int i = 0;
	for (auto ch : sText)
	{
		int c = ch;
		if (c > 95)
			c -= 32;
		int sx = ((c - 32) % 16) * 16;
		int sy = ((c - 32) / 16) * 16;
		DrawPartialSprite(x + i * 16, y, colour == TXT_WHITE ? m_sprFont16x16_white : m_sprFont16x16_black, sx, sy, 16, 16);
		i++;
	}
}

void cEngine::DrawFrontDialog(int x, int y)
{
	if (m_bShowDialog)
	{
		if (m_listDialogsQueue.empty())
			return;

		//pobieranie wymiar�w ramki
		unsigned nMaxLineLength = 0;
		int nLines = m_listDialogsQueue.front().size();

		for (auto l : m_listDialogsQueue.front())	if (l.size() > nMaxLineLength) nMaxLineLength = l.size();

		// rysowanie obram�wki i t�a dla tekstu
		FillRect(x - 1, y - 1, nMaxLineLength * 6 + 2, nLines * 8 + 2, olc::Pixel(255, 255, 255, bGfxHighSettings ? 150 : 255)); // prostok�t stanowi�cy t�o dla tekstu
		DrawLine(x - 2, y - 2, x - 2, y + nLines * 8 + 1, olc::DARK_RED); // linia pionowa lewa
		DrawLine(x + nMaxLineLength * 6 + 1, y - 2, x + nMaxLineLength * 6 + 1, y + nLines * 8 + 1, olc::DARK_RED); // linia pionowa prawa
		DrawLine(x - 2, y - 2, x + nMaxLineLength * 6 + 1, y - 2, olc::DARK_RED); // linia pozioma g�rna 
		DrawLine(x - 2, y + nLines * 8 + 1, x + nMaxLineLength * 6 + 1, y + nLines * 8 + 1, olc::DARK_RED); // linia pozioma dolna

		for (unsigned l = 0; l < m_listDialogsQueue.front().size(); l++) // rysowane samego tekstu
			DrawText(m_listDialogsQueue.front()[l], x, y + l * 8);
	}
}

void cEngine::NextDialog()
{
	if (m_listDialogsQueue.size() == 1)
		m_bShowDialog = false;

	m_listDialogsQueue.pop_front();
}

void cEngine::AddDialog(std::vector<std::string> vecText)
{
	m_listDialogsQueue.push_back(vecText);
	m_bShowDialog = true;
}

void cEngine::DisplayFrontMessage()
{
	if (m_bShowMessage)
	{
		if (m_listMessagesQueue.empty())
			return;

		//pobieranie wymiar�w ramki
		unsigned nMaxLineLength = 0;
		int nLines = m_listMessagesQueue.front().size();

		for (auto l : m_listMessagesQueue.front())	if (l.size() > nMaxLineLength) nMaxLineLength = l.size();

		int x = (ScreenWidth() - (nMaxLineLength * 6)) / 2;
		int y = (ScreenHeight() - (m_listMessagesQueue.front().size() * 8)) / 2;

		// rysowanie obram�wki i t�a dla tekstu
		FillRect(x - 1, y - 1, nMaxLineLength * 6 + 2, nLines * 8 + 2, olc::Pixel(255, 255, 255, bGfxHighSettings ? 190 : 255)); // prostok�t stanowi�cy t�o dla tekstu
		DrawLine(x - 2, y - 2, x - 2, y + nLines * 8 + 1, olc::DARK_RED); // linia pionowa lewa
		DrawLine(x + nMaxLineLength * 6 + 1, y - 2, x + nMaxLineLength * 6 + 1, y + nLines * 8 + 1, olc::DARK_RED); // linia pionowa prawa
		DrawLine(x - 2, y - 2, x + nMaxLineLength * 6 + 1, y - 2, olc::DARK_RED); // linia pozioma g�rna 
		DrawLine(x - 2, y + nLines * 8 + 1, x + nMaxLineLength * 6 + 1, y + nLines * 8 + 1, olc::DARK_RED); // linia pozioma dolna

		for (unsigned l = 0; l < m_listMessagesQueue.front().size(); l++) // rysowane samego tekstu
			DrawText(m_listMessagesQueue.front()[l], x, y + l * 8);
	}
}

void cEngine::ClearAllDialogs()
{
	m_bShowDialog = false;
	m_listDialogsQueue.clear();
}

void cEngine::NextMessage()
{
	if (m_listMessagesQueue.size() == 1)
		m_bShowMessage = false;

	m_listMessagesQueue.pop_front();
}

void cEngine::AddMessage(std::vector<std::string> vecMessage)
{
	m_listMessagesQueue.push_back(vecMessage);
	m_bShowMessage = true;
}

cDynamicCreature* cEngine::Player()
{
	for (unsigned i = 0; i < m_currentMap->vecDyn.size(); i++)
	{
		if (m_currentMap->vecDyn[i]->sName == "player")
			return dynamic_cast<cDynamicCreature*>(m_currentMap->vecDyn[i]);
	}
	return nullptr;
}

void cEngine::AddDyn(cDynamic* dyn)
{ 
	m_currentMap->vecDyn.push_back(dyn); 
}

cDynamic* cEngine::GetDyn(std::string name)
{
	for (auto &d : m_currentMap->vecDyn)
	{
		if (d->sName == name)
			return d;
	}
	return nullptr;
}

void cEngine::DrawUI(float fElapsedTime)
{
	if (bShowUI)
	{

		// HP ##.# / ##.#
		TEXT_COLOUR HPcolour = TXT_BLACK;

		if (pPlayer->fHP <= (0.20 * pPlayer->fMaxHP))
			HPcolour = TXT_DARK_RED;

		if (pPlayer->fHP < fOldHP) // gracz otrzyma� obra�enia
			fHealthFlashTimer = fHealthFlashDuration;

		fOldHP = pPlayer->fHP;

		if (fHealthFlashTimer > 0.0f)
		{
			fHealthFlashTimer -= fElapsedTime; // migni�cie na czerwono po otrzymaniu obra�e�
			HPcolour = TXT_RED;
			if (fHealthFlashTimer < 0.0f)
				fHealthFlashTimer = 0.0f;
		}

		// obecne HP
		std::string TextHP;
		std::string TextHPBuffer = std::to_string(pPlayer->fHP);
		for (unsigned i = 0; i < TextHPBuffer.length() - 1; i++)
		{
			if (TextHPBuffer[i] != '.')
				TextHP += TextHPBuffer[i];
			else
			{
				TextHP += TextHPBuffer[i];
				TextHP += TextHPBuffer[i + 1];
				break;
			}
		}

		// maksymalne HP
		std::string TextMaxHP;
		std::string TextMaxHPBuffer = std::to_string(pPlayer->fMaxHP);
		for (unsigned i = 0; i < TextMaxHPBuffer.length() - 1; i++)
		{
			if (TextMaxHPBuffer[i] != '.')
				TextMaxHP += TextMaxHPBuffer[i];
			else
			{
				TextMaxHP += TextMaxHPBuffer[i];
				TextMaxHP += TextMaxHPBuffer[i + 1];
				break;
			}
		}

		// obram�wka
		int tempY = ScreenHeight() - UI_FromScreenBorder - 7;
		FillRect(UI_FromScreenBorder, tempY, (TextHP.length() + TextMaxHP.length() + 6) * 6, 7, olc::Pixel(255, 255, 255, bGfxHighSettings ? 100 : 255));
		// tekst
		std::string TextHPFinal = "HP " + TextHP + " / " + TextMaxHP;
		DrawText(TextHPFinal, UI_FromScreenBorder, tempY, HPcolour);

		/* wersja alternatywna - miga tylko samo obecne zdrowie
		DrawText("HP ", UI_FromScreenBorder, tempY);
		DrawText(TextHP, UI_FromScreenBorder + 18, tempY, HPcolour);
		DrawText(" / ", UI_FromScreenBorder + 18 + TextHP.length() * 6, tempY);
		DrawText(TextMaxHP, UI_FromScreenBorder + 36 + TextHP.length() * 6, tempY);
		*/

		// STAM ## / ##
		TEXT_COLOUR Stamcolour = TXT_BLACK;

		// ustaw wska�nik staminy na czerwono je�li obecna stamina jest mniejsza ni� koszt doskoku
		if (PlayerData.fStamina < PlayerData.fStaminaDashCost)
			Stamcolour = TXT_RED;

		// obecna stamina
		std::string TextStam;
		std::string TextStamBuffer = std::to_string(PlayerData.fStamina);

		for (unsigned i = 0; i < TextStamBuffer.length() - 1; i++)
		{
			if (TextStamBuffer[i] != '.')
				TextStam += TextStamBuffer[i];
			else
				break;
		}

		// maksymalna stamina
		std::string TextMaxStam;
		std::string TextMaxStamBuffer = std::to_string(PlayerData.fMaxStamina);

		for (unsigned i = 0; i < TextMaxStamBuffer.length() - 1; i++)
		{
			if (TextMaxStamBuffer[i] != '.')
				TextMaxStam += TextMaxStamBuffer[i];
			else
				break;
		}

		std::string TextStamFinal = "Stam " + TextStam + " / " + TextMaxStam;
		int nStatSpacing = 12; // odleg�o�� w poziomie pomi�dzy poszczeg�lnymi statystykami
		int tempX2 = UI_FromScreenBorder + TextHPFinal.length() * 6 + nStatSpacing;
		FillRect(tempX2, tempY, TextStamFinal.length() * 6, 7, olc::Pixel(255, 255, 255, bGfxHighSettings ? 100 : 255)); // obram�wka
		DrawText("Stam ", tempX2, tempY); // tekst
		DrawText(TextStam, tempX2 + 30, tempY, Stamcolour); // tekst
		DrawText(" / ", tempX2 + 30 + TextStam.length() * 6, tempY); // tekst
		DrawText(TextMaxStam, tempX2 + TextStam.length() * 6 + 48, tempY); // tekst

		// ikona dier�onej broni
		if (PlayerData.currentWeapon != nullptr)
		{
			float fWeaponIconRows = (1.0f - (pPlayer->fTime3 / pPlayer->stats.fMeleeAttackCooldown)) * 16;
			int nIconX = ScreenWidth() - 16 - UI_FromScreenBorder;
			int nIconY = ScreenHeight() - UI_FromScreenBorder;
			for (unsigned i = 0; i < fWeaponIconRows; i++)
			{
				FillRect(nIconX, nIconY - i, 16, 1, olc::Pixel(255 - i * 10, 255 - i * 10, 255 - i * 10, 255));
				DrawPartialSprite(nIconX, nIconY - i, PlayerData.currentWeapon->sprite, 0, (15 - i), 16, 1);
			}

		}
	}

	// w��cz obs�ugiwanie przez silnik cz�ciowej prze�roczysto�ci niezale�nie od ustawie� graficznych 
	// aby umo�liwi� efekt wygaszenia ekranu
	SetPixelMode(olc::Pixel::ALPHA);

	// wygaszenie ekranu
	if (nDimm != 0)
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0, nDimm));
}

void cEngine::RecalculatePlayerStats()
{
	if (PlayerData.currentWeapon == nullptr)
		return;

	//przekalkulowanie statystyk gracza - narazie wszystkie 1:1 ze statystykami dier�onej bronii
	pPlayer->stats.fDmg = PlayerData.currentWeapon->fDmg;
	pPlayer->stats.fDmgFluct = PlayerData.currentWeapon->fDmgFluct;
	pPlayer->stats.fKnockbackMultiplier = PlayerData.currentWeapon->fKnockbackMultiplier;
	pPlayer->stats.fKnockbackTimer = PlayerData.currentWeapon->fKnockbackTimer;
	pPlayer->stats.fMeleeAttackCooldown = PlayerData.currentWeapon->fMeleeAttackCooldown;
	pPlayer->stats.fMeleeAttackImmobilityCooldown = PlayerData.currentWeapon->fMeleeAttackImmobilityCooldown;
	pPlayer->stats.fMeleeRange = PlayerData.currentWeapon->fMeleeRange; // nieu�ywane - posta� gracza u�ywa odmiennego sposobu ataku ni� inne stwory
}

void cEngine::ChangeMap(std::string mapName, float _px, float _py)
{
	//usu� gracza z wektora obiekt�w dynamicznych w mapie (je�li jaka� obecnie jest za�adowana)
	if(!(m_currentMap == nullptr))
			m_currentMap->vecDyn.erase(m_currentMap->vecDyn.begin());

	//zmie� map�
	m_currentMap = cData::get().GetMap(mapName);

	//dodaj gracza na samym pocz�tku wektora obiekt�w dynamicznych
	m_currentMap->vecDyn.insert(m_currentMap->vecDyn.begin(), pPlayer);

	//ustaw wsp�rz�dne gracza
	pPlayer->px = _px;
	pPlayer->py = _py;

	// //oddaj graczowi mo�liwo�� sterowania
	// ScriptEngine.bPlayerInControl = true;
	
	//je�li gracz wchodzi do danej mapy pierwszy raz to wykonaj odpowiednie czynno�ci (np. skrypty)
	if (m_currentMap->bHasBeenEntered == false)
		m_currentMap->FirstEnter();
}

bool cEngine::OnUserCreate() 
{
	//ziarno generatora liczb pseudolosowych
	srand((unsigned)time(NULL));

	//�adowanie dialog�w
	cData::get().LoadDialogs();

	//�adowanie grafik
	cData::get().LoadSprites();
	cData::get().LoadItemSprites();

	//gracz
	pPlayer = new cDynamicCreature(this, "player", 4.0f, 4.0f, cData::get().GetSprite("player"), true, true, 0.625f, 1.0f, cDynamicCreature::STATE_STANDING, 15.0f, true);

	//�adowanie map
	cData::get().LoadMaps(this);

	//�adowanie czcionek
	m_sprFont4x4 = new olc::Sprite("data/fonts/font4x4.png");
	m_sprFont4x5 = new olc::Sprite("data/fonts/font4x5.png");
	m_sprFont4x6 = new olc::Sprite("data/fonts/font4x6.png");
	m_sprFont6x8_black = new olc::Sprite("data/fonts/6x8/font6x8_black.png");
	m_sprFont6x8_white = new olc::Sprite("data/fonts/6x8/font6x8_white.png");
	m_sprFont6x8_red = new olc::Sprite("data/fonts/6x8/font6x8_red.png");
	m_sprFont6x8_dark_red = new olc::Sprite("data/fonts/6x8/font6x8_dark_red.png");
	m_sprFont8x12 = new olc::Sprite("data/fonts/font8x12.png");
	m_sprFont16x16_black = new olc::Sprite("data/fonts/font16x16_black.png");
	m_sprFont16x16_white = new olc::Sprite("data/fonts/font16x16_white.png");

	//wymiary p�l z kt�rych sk�ada si� mapa
	nTileWidth = 16;
	nTileHeight = 16;

	//

	fOldHP = pPlayer->fHP; // zrzut HP gracza
	SetPixelMode(olc::Pixel::ALPHA); // domy�lny tryb renderowania

	//za�adowanie mapy
	ChangeMap("intro1", 15.0f, 12.0f); // - fina�owe!

	//zasi�g detekcji kolizji dynamicznej 
	float fCollisionDetectionDistance = 3.0f;
	fCollisionDetectionDistancePow2 = fCollisionDetectionDistance * fCollisionDetectionDistance;

	// inicjalizacja ekwipunku (tymczasowe rozwi�zanie)
	// gracza posiada narazie tylko jeden slot - slot z broni�
	//PlayerData.currentWeapon = new cBasic_Sword;
	PlayerData.currentWeapon = nullptr;
	RecalculatePlayerStats();

	//okres aktualizacji animacji element�w mapy
	m_fStacicAnimInterval = 1.0f;

	//ustawienie pocz�tkowej pozycji kamery - przyklejona do gracza
	fCameraPosX = pPlayer->px;
	fCameraPosY = pPlayer->py;

	//

	return true;
}

bool cEngine::OnUserUpdate(float fElapsedTime) 
{
	switch (GS_gamestate)
	{
	case GS_LOCAL_MAP:
		if (!UpdateLocalMap(fElapsedTime))
			return false;
		break;
	case GS_TITLE_MENU:
		if (!UpdateTitleMenu(fElapsedTime))
			return false;
		break;
	}

	return true;
}

