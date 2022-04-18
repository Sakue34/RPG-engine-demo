#include "Editor.h"
#include "Map.h"

bool cMapEditor::OnUserCreate()
{
	m_sprFont6x8_white = new olc::Sprite("data/font6x8_white.png");
	m_sprFont6x8_black = new olc::Sprite("data/font6x8_black.png");
	m_sprFont6x8_red = new olc::Sprite("data/font6x8_red.png");
	m_sprFont6x8_dark_red = new olc::Sprite("data/font6x8_dark_red.png");

	sprTileSet = new olc::Sprite("data/tileset.png");
	sprSelection = new olc::Sprite("data/selection.png");
	sprSelection2 = new olc::Sprite("data/selection2.png");
	sprSelection3 = new olc::Sprite("data/selection3.png");
	sprSelection4 = new olc::Sprite("data/selection4.png");

	sprSolid = new olc::Sprite("data/solid.png");
	sprSolid2 = new olc::Sprite("data/solid2.png");
	sprAnimated = new olc::Sprite("data/animated.png");

	m_currentMap = new cMap();
	m_currentMap->Load(L"map/map.txt");

	//obliczanie liczby widocznych pól edytora na ekranie
	nVisibleTilesX = (ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT) / nTileWidth;
	nVisibleTilesY = ScreenHeight() / nTileHeight;

	fCameraSpeed = 7.0f;

	std::cout << "Crtl + Shift + N - Kreator nowej mapy" << std::endl;
	std::cout << "Crtl +  N - Nowej mapa 30x30" << std::endl;

	return true;
}

void cMapEditor::DrawText(std::string sText, int x, int y, TEXT_COLOUR colour)
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

bool cMapEditor::OnUserUpdate(float fElapsedTime)
{
	bool bUserHoldsFlagKey = false;
	bool bMouseHeldDraw = false;
	bool bMousePressedTileSelect = false;

	if (GetMouseX() > ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT && GetMouseY() > 63)
		bUserNavigatesTileSet = true;
	else
		bUserNavigatesTileSet = false;

	if (IsFocused())
	{
		// input
		if (GetKey(olc::Key::W).bHeld)
		{
			fCameraPosY -= fElapsedTime * fCameraSpeed;
		}
		if (GetKey(olc::Key::A).bHeld)
		{
			fCameraPosX -= fElapsedTime * fCameraSpeed;
		}
		if (GetKey(olc::Key::S).bHeld)
		{
			fCameraPosY += fElapsedTime * fCameraSpeed;
		}
		if (GetKey(olc::Key::D).bHeld)
		{
			fCameraPosX += fElapsedTime * fCameraSpeed;
		}
		if (GetKey(olc::Key::F5).bPressed)
		{
			m_currentMap->Save(L"map/new.txt");
		}
		if (GetKey(olc::Key::F6).bPressed)
		{
			m_currentMap->Load(L"map/map.txt");
		}
		if (GetKey(olc::Key::E).bPressed)
		{
			nTool = TOOL_PENCIL;
		}
		if (GetKey(olc::Key::Z).bPressed)
		{
			nID = 0;
		}
		if (GetKey(olc::Key::X).bPressed)
		{
			nID = 87;
		}
		if (GetKey(olc::Key::Q).bPressed)
		{
			nTool = TOOL_FLAGS;
		}
		if (GetKey(olc::Key::Q).bHeld)
		{
			fTimePressedFlagKey += fElapsedTime;
			if (fTimePressedFlagKey >= 0.3f)
			{
				bUserHoldsFlagKey = true;
				fTimePressedFlagKey = 0.3f;
			}
		}
		else
		{
			bUserHoldsFlagKey = false;
			fTimePressedFlagKey = 0.0f;
		}
		if (GetKey(olc::Key::CTRL).bHeld)
		{
			if (!GetKey(olc::SHIFT).bHeld)
			{
				if (GetKey(olc::Key::N).bPressed)
				{
					m_currentMap = new cMap();
					m_currentMap->New(30, 30, 001, 000, 000, false, false);
				}
			}
			else
			{
				if (GetKey(olc::Key::N).bPressed)
				{
					system("cls");

					FillRect(20, (ScreenHeight() / 2) - 4, 168, 8, olc::WHITE);
					DrawText("Waiting for console input...", 20, (ScreenHeight() / 2) - 4, TXT_DARK_RED);

					std::cout << "Kreator nowej mapy:" << std::endl;

					int width = 0;
					while (1)
					{
						std::cout << "Podaj szerokosc mapy >";
						
						std::cin >> width;
						if (std::cin.bad())
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					int height = 0;
					while (1)
					{
						std::cout << "Podaj wysokosc mapy >";
						
						std::cin >> height;
						if (std::cin.bad())
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					int _ID1 = 0;
					while (1)
					{
						std::cout << "Podaj ID warstwy pierwszej >";
						std::cin >> _ID1;
						if (std::cin.bad())
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					int _ID2 = 0;
					while (1)
					{
						std::cout << "Podaj ID warstwy drugiej >";
						std::cin >> _ID2;
						if (std::cin.bad())
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					int _ID3 = 0;
					while (1)
					{
						std::cout << "Podaj ID warstwy trzeciej >";
						std::cin >> _ID3;
						if (std::cin.bad())
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					bool _solid = false;
					while (1)
					{
						std::cout << "Sciana? (Y/N) >";
						char _c1;
						std::cin >> _c1;
						if (_c1 == 'Y' || _c1 == 'y')
							_solid = true;
						else if (_c1 == 'N' || _c1 == 'n')
							_solid = false;
						else
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}
						//std::cout << std::endl;
						break;
					}

					bool _animated = false;
					while (1)
					{
						std::cout << "Pole animowane? (animacja dotyczy tylko pierwszej warstwy) (Y/N) >";
						char _c2;
						std::cin >> _c2;
						if (_c2 == 'Y' || _c2 == 'y')
							_animated = true;
						else if (_c2 == 'N' || _c2 == 'n')
							_animated = false;
						else
						{
							std::cout << "Niepoprawne wprowadzenie!";
							std::cout << std::endl;
							continue;
						}

						//std::cout << std::endl;
						break;
					}
					
					m_currentMap = new cMap();
					m_currentMap->New(width, height, _ID1, _ID2, _ID3, _solid, _animated);
				}
			}
		}
		if (GetMouse(0).bHeld)
		{
			if(bUserNavigatesTileSet == false)
				if(GetMouseX() < ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT)
					bMouseHeldDraw = true;
		}
		if (GetMouse(0).bPressed)
		{
			if (bUserNavigatesTileSet)
				bMousePressedTileSelect = true;
		}
		if (nTool == TOOL_PENCIL)
		{
			if (GetKey(olc::Key::K1).bPressed)
			{
				nLayer = 1;
			}
			if (GetKey(olc::Key::K2).bPressed)
			{
				nLayer = 2;
			}
			if (GetKey(olc::Key::K3).bPressed)
			{
				nLayer = 3;
			}
		}
		if (nTool == TOOL_FLAGS)
		{
			if (GetKey(olc::Key::K4).bPressed)
			{
				if (bFlagIsSolid)
					bFlagIsSolid = false;
				else
					bFlagIsSolid = true;
			}
			if (GetKey(olc::Key::K5).bPressed)
			{
				if (bFlagIsAnimated)
					bFlagIsAnimated = false;
				else
					bFlagIsAnimated = true;
			}
		}
		if (bUserNavigatesTileSet)
		{
			if (GetMouseWheel() > 0)
			{
				nTileSelectOffset--;
			}
			if (GetMouseWheel() < 0)
			{
				nTileSelectOffset++;
			}

			if (nTileSelectOffset < 0)
				nTileSelectOffset = 0;

			if (nTileSelectOffset > (sprTileSet->height / nTileHeight) - ((ScreenHeight() - 64) / nTileHeight))
				nTileSelectOffset = (sprTileSet->height / nTileHeight) - ((ScreenHeight() - 64) / nTileHeight);
		}

		nSelectedX = (int)(GetMouseX() / nTileWidth);
		nSelectedY = (int)(GetMouseY() / nTileHeight);
	}

	if (nSelectedX > nVisibleTilesX - 1)
		nSelectedX = nVisibleTilesX - 1;

	if (nSelectedY > nVisibleTilesY)
		nSelectedY = nVisibleTilesY;

	//aktualizacja timera animacji elementów mapy
	m_fStaticAnimTime -= fElapsedTime;

	if (m_fStaticAnimTime < 0.0f)
		m_fStaticAnimTime = 0.0f;

	if (m_fStaticAnimTime == 0.0f)
	{
		if (m_nStaticAnimFrame == 0)
			m_nStaticAnimFrame = 1;
		else
			m_nStaticAnimFrame = 0;

		m_fStaticAnimTime = m_fStacicAnimInterval;
	}

	// rysowanie mapy

	//czyszczenie ekranu
	Clear(olc::BLACK);

	//obliczanie offsetu
	int nOffsetX = (int)(fCameraPosX - (float)nVisibleTilesX / 2.0f);
	int nOffsetY = (int)(fCameraPosY - (float)nVisibleTilesY / 2.0f);

	//domyœlny tryb renderowania
	SetPixelMode(olc::Pixel::NORMAL);

	//rysowanie mapy warstwa pierwsza
	for (int x = 0; x < nVisibleTilesX; x++)
	{
		for (int y = 0; y < nVisibleTilesY; y++)
		{
			int index = m_currentMap->GetIndex((int)(x + nOffsetX), (int)(y + nOffsetY));
			if (index != 0)
			{
				// sprawdzenie czy mamy do czynienia z animowanym polem i jeœli tak to któr¹ klatkê nale¿y wyœwietliæ
				if (m_currentMap->GetIsAnimated(x + nOffsetX, y + nOffsetY) == 1)
					if (m_nStaticAnimFrame == 1)
						index++;	// jeœli nale¿y wyœwietliæ drug¹ klatkê animacji to wyœwietl grafikê o ID zwiêkszonym o jeden

				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix = index % 10;
				int iy = index / 10;
				DrawPartialSprite(x * nTileWidth, y * nTileHeight,
					sprTileSet, ix * nTileWidth, iy * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// druga i trzecia warstwa obs³uguje przeŸroczystoœæ
	SetPixelMode(olc::Pixel::ALPHA);

	//rysowanie mapy warstwa druga
	for (int x = 0; x < nVisibleTilesX; x++)
	{
		for (int y = 0; y < nVisibleTilesY; y++)
		{
			int index2 = m_currentMap->GetIndex2(x + nOffsetX, y + nOffsetY);
			if (index2 != 0)
			{
				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix2 = index2 % 10;
				int iy2 = index2 / 10;
				DrawPartialSprite(x * nTileWidth, y * nTileHeight,
					sprTileSet, ix2 * nTileWidth, iy2 * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// rysowanie mapy warstwa trzecia: warstwa która zawsze rysowana jest nad obiektami dynamicznymi
	// np. górne czêœci filarów które s¹ "przed" stworami
	for (int x = 0; x < nVisibleTilesX; x++)
	{
		for (int y = 0; y < nVisibleTilesY; y++)
		{
			int index3 = m_currentMap->GetIndex3(x + nOffsetX, y + nOffsetY);
			if (index3 != 0)
			{
				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix3 = index3 % 10;
				int iy3 = index3 / 10;
				DrawPartialSprite(x* nTileWidth, y* nTileHeight,
					sprTileSet, ix3* nTileWidth, iy3* nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	if (nTool == TOOL_FLAGS)
	{
		olc::Sprite* temp_sprSolid = nullptr;
		if (bUserHoldsFlagKey)
			temp_sprSolid = sprSolid2;
		else
			temp_sprSolid = sprSolid;

		//graficzna flaga oznaczaj¹ca obiekt wywo³uj¹cy kolizjê statyczn¹
		for (int x = 0; x < nVisibleTilesX; x++)
		{
			for (int y = 0; y < nVisibleTilesY; y++)
			{
				if (m_currentMap->GetSolid(x + nOffsetX, y + nOffsetY))
				{
					DrawSprite(x * nTileWidth, y * nTileHeight, temp_sprSolid);
				}
			}
		}

		//graficzna flaga oznaczaj¹ca obiekt animowany
		for (int x = 0; x < nVisibleTilesX; x++)
		{
			for (int y = 0; y < nVisibleTilesY; y++)
			{
				if (m_currentMap->GetIsAnimated(x + nOffsetX, y + nOffsetY))
				{
					DrawSprite(x * nTileWidth, y * nTileHeight, sprAnimated);
				}
			}
		}
	}

	//rysowanie oznaczenia wybranego pola
	if (bUserNavigatesTileSet == false)
	{
		if(nLayer == 1)
			DrawSprite(nSelectedX * nTileWidth, nSelectedY * nTileHeight, sprSelection);
		else if(nLayer == 2)
			DrawSprite(nSelectedX* nTileWidth, nSelectedY* nTileHeight, sprSelection3);
		else if(nLayer == 3)
			DrawSprite(nSelectedX* nTileWidth, nSelectedY* nTileHeight, sprSelection4);
	}
	
	//linia oddzielaj¹ca UI
	DrawLine(ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT, 0, ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT, ScreenHeight(), olc::WHITE);

	if (!bUserNavigatesTileSet)
	{
		//koordynaty wybranego pola
		FillRect(0, ScreenHeight() - 9, 90, 9, olc::Pixel(0, 0, 0, 155));
		DrawText("X: " + std::to_string(nSelectedX + nOffsetX) + " | Y: " + std::to_string(nSelectedY + nOffsetY), 0, ScreenHeight() - 8, TXT_WHITE);
	}

	//klawiszologia
	DrawText("F5 - Save   F6 - Load", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 1, TXT_WHITE);
	DrawText("1 2 3 - Layer selection", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 10, TXT_WHITE);
	DrawText("4 - Solid?   5 - Animated?", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 19, TXT_WHITE);
	DrawText("E - Pencil (Layer: ", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 28, nTool == TOOL_PENCIL ? TXT_DARK_RED : TXT_WHITE);
	DrawText(std::to_string(nLayer), ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 115, 28, nLayer == 3 ? TXT_RED : (nTool == TOOL_PENCIL ? TXT_DARK_RED : TXT_WHITE));
	DrawText(")", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 121, 28, nTool == TOOL_PENCIL ? TXT_DARK_RED : TXT_WHITE);
	DrawText("Q - Flags:", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 37, nTool == TOOL_FLAGS ? TXT_DARK_RED : TXT_WHITE);
	if (nTool == TOOL_FLAGS)
	{
		if (bFlagIsSolid)
			DrawText("Solid!", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 46, TXT_RED);
		else
			DrawText("Not solid", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 46, TXT_WHITE);

		if (bFlagIsAnimated)
			DrawText("Animated!", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 55, TXT_RED);
		else
			DrawText("Not animated", ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 55, TXT_WHITE);
	}

	//kreska oddzielaj¹ca tekst interfejsu od podgl¹du tilesetu
	DrawLine(ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 63, ScreenWidth(), 63);

	//rysowanie ca³ego tilesetu
	DrawPartialSprite(ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1, 64, sprTileSet, 0, 16 * nTileSelectOffset, 160, ScreenHeight() - 64);

	if (bMouseHeldDraw)
	{
		if (nTool == TOOL_PENCIL)
			switch (nLayer)
			{
			case 1:
				m_currentMap->SetIndex(nSelectedX + nOffsetX, nSelectedY + nOffsetY, nID);
				break;
			case 2:
				m_currentMap->SetIndex2(nSelectedX + nOffsetX, nSelectedY + nOffsetY, nID);
				break;
			case 3:
				m_currentMap->SetIndex3(nSelectedX + nOffsetX, nSelectedY + nOffsetY, nID);
				break;
			default:
				break;
			}
		if (nTool == TOOL_FLAGS)
		{
			m_currentMap->SetSolid(nSelectedX + nOffsetX, nSelectedY + nOffsetY, bFlagIsSolid);
			m_currentMap->SetAnimated(nSelectedX + nOffsetX, nSelectedY + nOffsetY, bFlagIsAnimated);
		}

		bMouseHeldDraw = false;
	}

	if (bUserNavigatesTileSet)
	{
		int nTileMouseX = (int)((GetMouseX() - (ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT) - 1) / nTileWidth);
		int nTileMouseY = (int)((GetMouseY() - 64) / nTileHeight);

		DrawSprite((ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1) + nTileWidth * nTileMouseX, 64 + nTileMouseY * nTileHeight, sprSelection2);

		if (bMousePressedTileSelect)
		{
			nID = (nTileMouseY + nTileSelectOffset) * 10 + nTileMouseX;
		}
	}

	// Z - alfa (ID 0)
	// X - blank (ID 87)
	DrawText("Z - 0 X - 87" + std::to_string(nID), ScreenWidth() - 73, 46, TXT_WHITE);

	//wyœwietlenie ID wybranego kafelka
	DrawText("ID: " + std::to_string(nID), ScreenWidth() - 48, 55, TXT_WHITE);

	//rysowanie obramówki wybranego kafelka do rysowania
	int nTempY = ((int)(nID / 10) * nTileHeight) + 64 - (nTileSelectOffset * nTileHeight);
	if(nTempY >= 64 && nTempY < ScreenHeight())
		DrawSprite(((nID % 10)* nTileWidth) + (ScreenWidth() - UI_ADDITIONAL_PIXELS_RIGHT + 1), nTempY, sprSelection);

	return true;
}
