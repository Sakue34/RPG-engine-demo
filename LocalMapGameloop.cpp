#include "Engine.h"
#include "Dynamic.h"
#include "Map.h"
#include "All_Dynamics.h"

bool cEngine::UpdateLocalMap(float fElapsedTime) // tryb gry 1 - mapa lokalna
{
	//obs�uga sterowania
	bool bHasPlayerAcceleratedX = false;
	bool bHasPlayerAcceleratedY = false;

	bool bKeyPressedInteract = false;
	bool bKeyPressedAttack = false;

	//pobieranie sterowania tylko je�li okno gry jest aktywne
	if (IsFocused())
	{
		// je�li silnik uznaje �e gracz ma kontrol� (nie dzia�a �aden skrypt itp) to zezw�l na sterowanie
		if (ScriptEngine.bPlayerInControl)
		{
			if (!bPause) // je�li gra nie jest spauzowana
			{
				if (pPlayer->nState != cDynamicCreature::STATE_DEAD) // zezw�l na sterowanie tylko je�li gracz nie jest martwy
				{
					if (!m_bShowMessage) // je�li nie wy�wietla si� komunikat
					{
						// poruszanie, atak i interakcja gracza mo�liwa tylko je�li ten nie jest obecnie odrzucany (knockback) 
						// ani nie jest w trakcie bezruchu po wykonaniu ataku podstawowego
						if (!pPlayer->bIsKnockbacked && pPlayer->fTime4 == 0.0f)
						{
							if (pPlayer->nState != cDynamicCreature::STATE_SLEEPING && pPlayer->nState != cDynamicCreature::STATE_UNCONSCIOUS)
							{
								if (GetKey(olc::Key::W).bHeld) // W
								{
									pPlayer->vy -= 26.0f * fElapsedTime;
									bHasPlayerAcceleratedY = true;
									pPlayer->nDirection = cDynamic::NORTH;
								}

								if (GetKey(olc::Key::A).bHeld) // A
								{
									pPlayer->vx -= 26.0f * fElapsedTime;
									bHasPlayerAcceleratedX = true;
									pPlayer->nDirection = cDynamic::WEST;
								}

								if (GetKey(olc::Key::S).bHeld) // S
								{
									pPlayer->vy += 26.0f * fElapsedTime;
									bHasPlayerAcceleratedY = true;
									pPlayer->nDirection = cDynamic::SOUTH;
								}

								if (GetKey(olc::Key::D).bHeld) // D
								{
									pPlayer->vx += 26.0f * fElapsedTime;
									bHasPlayerAcceleratedX = true;
									pPlayer->nDirection = cDynamic::EAST;
								}
								if (GetKey(olc::Key::E).bPressed) // E - interakcja z otoczeniem
								{
									if (m_bShowDialog == false && m_bShowMessage == false) // je�li nie wy�wietla si� �aden dialog ani komunikat
										bKeyPressedInteract = true;
								}
								if (GetKey(olc::Key::SPACE).bPressed) // spacja - atak
								{
									bKeyPressedAttack = true;
								}
								if (GetKey(olc::Key::ENTER).bPressed) // enter - odskok
								{
									if (PlayerData.fStamina >= PlayerData.fStaminaDashCost) // je�li gracz ma wystarczaj�co wytrzyma�o�ci
									{
										if (abs(pPlayer->vx) > 0.2f || abs(pPlayer->vy) > 0.2f) // je�li nie stoi w miejscu przed wykonaniem doskoku
										{
											pPlayer->Knockback(pPlayer->vx * 3.0f * PlayerData.fDashVelocityMultiplier,
												pPlayer->vy * 3.0f * PlayerData.fDashVelocityMultiplier, PlayerData.fDashExecutionTime);
										}
										else // je�li gracz stoi w miejscu to odskok wykonaj w kierunku zgodnym z kierunkiem jego sprite'a
										{
											switch (pPlayer->nDirection)
											{
											case cDynamic::NORTH:
												pPlayer->Knockback(0.0f, pPlayer->fMaxWalkingVel * -3.0f * PlayerData.fDashVelocityMultiplier,
													PlayerData.fDashExecutionTime);
												break;
											case cDynamic::EAST:
												pPlayer->Knockback(pPlayer->fMaxWalkingVel * 3.0f * PlayerData.fDashVelocityMultiplier, 0.0f,
													PlayerData.fDashExecutionTime);
												break;
											case cDynamic::SOUTH:
												pPlayer->Knockback(0.0f, pPlayer->fMaxWalkingVel * 3.0f * PlayerData.fDashVelocityMultiplier,
													PlayerData.fDashExecutionTime);
												break;
											case cDynamic::WEST:
												pPlayer->Knockback(pPlayer->fMaxWalkingVel * -3.0f * PlayerData.fDashVelocityMultiplier, 0.0f,
													PlayerData.fDashExecutionTime);
												break;
											default:
												break;
											}
										}

										PlayerData.fStamina -= PlayerData.fStaminaDashCost;
										PlayerData.fStaminaTimer = PlayerData.fStaminaRegenDelay;
									}
								}
							}
							// sterowanie niezale�ne od tego, �e posta� gracza �pi lub jest nieprzytomna
							// ...
						}
						// sterowanie niezale�ne od bycia w powietrzu
						// ...
					}

					//sterowanie niezale�ne od tego, �e wy�wietla si� komunikat
					if (GetKey(olc::Key::E).bPressed) // E - pomini�cie obecnego dialogu je�li nie wy�wietla si� �aden komunikat ani �aden skrypt nie oczekuje na pomini�cie
					{
						if (!m_bShowMessage)
							if(!ScriptEngine.bWaitForManualSkip)
								if (m_bShowDialog)
									NextDialog();
						
					}
				}
				//sterowanie nezale�ne od bycia martwym
				// ...
			}
			// sterowanie niezale�ne od pauzy i bycia martwym
			// ...
		}
		//sterowanie niezale�ne od tego, �e silnik skrypt�w nie zezwala na sterowanie
		if (GetKey(olc::Key::E).bPressed) // E - pomini�cie obecnego komunikatu, a je�li �adnego nie ma, to pomini�cie obecnego skryptu czekaj�cego na manualne pomini�cie
		{
			if (m_bShowMessage)
				NextMessage();
			else
			{
				if (ScriptEngine.bWaitForManualSkip)
					if (!bPause) // pod warunkiem �e gra nie zosta�a spauzowana
						ScriptEngine.bWaitForManualSkip = false;
			}
		}

		if (GetKey(olc::Key::O).bPressed) // prze��czanie ustawie� graficznych - czy silnik ma obs�ugiwa� cz�ciow� prze�roczysto�� sprite'�w
		{
			if (bGfxHighSettings)
				bGfxHighSettings = false;
			else
				bGfxHighSettings = true;
		}

		if (GetKey(olc::Key::P).bPressed) // pauza
		{
			if (bPause)
				bPause = false;
			else
				bPause = true;
		}

		//dev:
		if (GetKey(olc::Key::M).bPressed) // dev
		{
		}
		if (GetKey(olc::Key::L).bPressed) // dev
		{
		}
	}

	if (!bPause) //je�li gra nie jest zpauzowana
	{
		if (!m_bShowMessage) //je�li nie wy�wietla si� �aden komunikat
		{
			//obs�uga skrypyt�w
			ScriptEngine.UpdateScripts(fElapsedTime);

			//je�li �aden skrypt nie zamrozi� czasu
			if (!ScriptEngine.bTimeIsFreezed)
			{
				//przekalkulowanie statystyk gracza
				RecalculatePlayerStats();

				//timer czasu od ostatniego u�ycia akcji wymagaj�cej wytrzyma�o�ci
				PlayerData.fStaminaTimer -= fElapsedTime;
				if (PlayerData.fStaminaTimer < 0.0f)
					PlayerData.fStaminaTimer = 0.0f;

				// regeneracja wytrzyma�o�ci
				if (PlayerData.fStaminaTimer == 0.0f)
				{
					PlayerData.fStamina += fElapsedTime * PlayerData.fStaminaRegenPerSecond;
					if (PlayerData.fStamina > PlayerData.fMaxStamina)
						PlayerData.fStamina = PlayerData.fMaxStamina;
				}

				if (bKeyPressedAttack) // atak gracza
				{
					if (pPlayer->fTime3 == 0.0f) // czas odnowienia ataku podstawowego
					{
						if (PlayerData.currentWeapon != nullptr) // je�li gracz posiada za�o�on� bro�
						{
							//ustawienie statusu gracza jako w trakcie wykonywania ataku
							pPlayer->nState = cDynamicCreature::STATE_MELEE_ATTACK;
							//ustawienie czasu odnowienia ataku podstawowego
							pPlayer->fTime3 = pPlayer->stats.fMeleeAttackCooldown;
							//ustawienie czasu odnowienia bezruchu po ataku podstawowym
							pPlayer->fTime4 = pPlayer->stats.fMeleeAttackImmobilityCooldown;

							switch (pPlayer->nDirection)
							{
							case cDynamic::NORTH:
								m_currentMap->vecDyn.push_back(new cPlayerMelee(this, (pPlayer->px - 0.125f), (pPlayer->py - 0.875f)));
								break;
							case cDynamic::EAST:
								m_currentMap->vecDyn.push_back(new cPlayerMelee(this, (pPlayer->px + pPlayer->fWidth), (pPlayer->py + 0.125f)));
								break;
							case cDynamic::SOUTH:
								m_currentMap->vecDyn.push_back(new cPlayerMelee(this, (pPlayer->px - 0.125f), (pPlayer->py + pPlayer->fHeight)));
								break;
							case cDynamic::WEST:
								m_currentMap->vecDyn.push_back(new cPlayerMelee(this, (pPlayer->px - 0.875f), (pPlayer->py + 0.0625f)));
								break;
							}
						}
					}
				}

				//obliczanie ruchu wszystkich obiekt�w dynamicznych
				for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
				{
					//obs�uga "pocisk�w" - aktualizacja czasu i statusu przestarza�ego
					if (m_currentMap->vecDyn[i]->bIsProjectile)
					{
						m_currentMap->vecDyn[i]->fProjectileTime -= fElapsedTime;
						if (m_currentMap->vecDyn[i]->fProjectileTime <= 0.0f)
							m_currentMap->vecDyn[i]->bIsRedundant = true;
					}

					// modyfikacje ruchu gracza
					if (m_currentMap->vecDyn[i]->sName == "player")
					{
						// je�li gracz w�a�nie nie jest odrzucany i nie podlega w�a�nie skryptowi
						if (m_currentMap->vecDyn[i]->bIsKnockbacked == false && pPlayer->bIsMovedByScript == false)
						{
							//spowolnienie
							if (!bHasPlayerAcceleratedX)
							{
								float decelerationX = -16.0f * m_currentMap->vecDyn[i]->vx * fElapsedTime;

								//zabezpieczenie przed spowolnieniem powoduj�cym zmian� zwrotu kierunku wektora pr�dko�ci gracza
								//przy niskiej warto�ci klatek na sekund�
								if (abs(decelerationX) > m_currentMap->vecDyn[i]->vx)
									decelerationX = -m_currentMap->vecDyn[i]->vx;

								m_currentMap->vecDyn[i]->vx += decelerationX;
							}
							if (!bHasPlayerAcceleratedY)
							{
								float decelerationY = -16.0f * m_currentMap->vecDyn[i]->vy * fElapsedTime;

								//zabezpieczenie przed spowolnieniem powoduj�cym zmian� zwrotu kierunku wektora pr�dko�ci gracza
								//przy niskiej warto�ci klatek na sekund�
								if (abs(decelerationY) > m_currentMap->vecDyn[i]->vy)
									decelerationY = -m_currentMap->vecDyn[i]->vy;

								m_currentMap->vecDyn[i]->vy += decelerationY;
							}
						}
					}

					//aktualizacja stanu, animacji, odrzutu i AI ka�dego obiektu dynamicznego
					m_currentMap->vecDyn[i]->Update(fElapsedTime, pPlayer);

					// je�li po aktualizacji obiekt�w dynamicznych zmieni�a si� pr�dko�� gracza i nie stoi on ju� w miejscu
					// (grafika miecza i gracza nie pokrywa�aby si�)
					// to wtedy usu� miecz gracza
					if (m_currentMap->vecDyn[i]->sName == "player melee")
						if (pPlayer->vx != 0.0f || pPlayer->vy != 0.0f)
							m_currentMap->vecDyn[i]->bIsRedundant = true;

					//ustawienie pr�dko�ci ka�dego cia�a jako zero przy pr�dko�ciach bliskich zeru
					if (abs(m_currentMap->vecDyn[i]->vx) < 0.005f)	m_currentMap->vecDyn[i]->vx = 0.0f;
					if (abs(m_currentMap->vecDyn[i]->vy) < 0.005f)	m_currentMap->vecDyn[i]->vy = 0.0f;

					//potencjalne nowe po�o�enie
					float fNewpx = m_currentMap->vecDyn[i]->px + (m_currentMap->vecDyn[i]->vx * fElapsedTime);
					float fNewpy = m_currentMap->vecDyn[i]->py + (m_currentMap->vecDyn[i]->vy * fElapsedTime);

					//kraw�d� kolizji statycznej
					float fBorder = 0.1f;

					//kolizja statyczna
					if (m_currentMap->vecDyn[i]->bSolidVsSolid)
					{
						if (m_currentMap->vecDyn[i]->vx <= 0)	// ruch w lewo
						{
							if (m_currentMap->vecDyn[i]->fWidth > 1.0f) // sprawdzenie czy obiekt jest szerszy ni� szeroko�� jednej kafelki i obs�uga kolizji w odpowiedni spos�b
							{
								//sprawdzenie czy wierzcho�ki koliduj� z map�
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									bCollision = true;
								}

								if (!bCollision) // je�li wierzcho�ki nie koliduj�, sprawd� punkty po�o�one na kraw�dziach pokrywaj�ce ca�y bok prostok�ta w r�wnych odst�pach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + z)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpx = (int)fNewpx + 1.0f;
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
							else // szeroko�� obiektu jest mniejsza lub r�wna 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									fNewpx = (int)fNewpx + 1.0f;
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
						}
						else						// ruch w prawo
						{
							if (m_currentMap->vecDyn[i]->fWidth > 1.0f) // sprawdzenie czy obiekt jest szerszy ni� szeroko�� jednej kafelki i obs�uga kolizji w odpowiedni spos�b
							{
								//sprawdzenie czy wierzcho�ki koliduj� z map�
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									bCollision = true;
								}

								if (!bCollision) // je�li wierzcho�ki nie koliduj�, sprawd� punkty po�o�one na kraw�dziach pokrywaj�ce ca�y bok prostok�ta w r�wnych odst�pach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + z)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpx = (int)fNewpx + (int)m_currentMap->vecDyn[i]->fWidth - m_currentMap->vecDyn[i]->fWidth;
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
							else // szeroko�� obiektu jest mniejsza lub r�wna 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									fNewpx = (int)fNewpx + (1.0f - m_currentMap->vecDyn[i]->fWidth);
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
						}

						if (m_currentMap->vecDyn[i]->vy <= 0)	// ruch w g�r�
						{
							if (m_currentMap->vecDyn[i]->fHeight > 1.0f) // sprawdzenie czy obiekt jest wy�szy ni� wysoko�� jednej kafelki i obs�uga kolizji w odpowiedni spos�b
							{
								//sprawdzenie czy wierzcho�ki koliduj� z map�
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy)) || m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy)))
								{
									bCollision = true;
								}

								if (!bCollision) // je�li wierzcho�ki nie koliduj�, sprawd� punkty po�o�one na kraw�dziach pokrywaj�ce ca�y bok prostok�ta w r�wnych odst�pach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + z), (int)(fNewpy)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpy = (int)fNewpy + 1.0f;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
							else // wysoko�� obiektu jest mniejsza lub r�wna 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy)) || m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy)))
								{
									fNewpy = (int)fNewpy + 1.0f;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
						}
						else						// ruch w d�
						{
							if (m_currentMap->vecDyn[i]->fHeight > 1.0f) // sprawdzenie czy obiekt jest wy�szy ni� wysoko�� jednej kafelki i obs�uga kolizji w odpowiedni spos�b
							{
								//sprawdzenie czy wierzcho�ki koliduj� z map�
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)))
								{
									bCollision = true;
								}

								if (!bCollision) // je�li wierzcho�ki nie koliduj�, sprawd� punkty po�o�one na kraw�dziach pokrywaj�ce ca�y bok prostok�ta w r�wnych odst�pach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + z), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpy = fNewpy = (int)fNewpy + (int)m_currentMap->vecDyn[i]->fHeight - m_currentMap->vecDyn[i]->fHeight;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
							else // wysoko�� obiektu jest mniejsza lub r�wna 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)))
								{
									fNewpy = (int)fNewpy + (1.0f - m_currentMap->vecDyn[i]->fHeight);
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
						}
					}

					//w�a�ciwa kolizja dynamiczna + (INTERACT_NATURE::WALK_ON)
					//kolizja wszystkich obiekt�w dynamicznych...
					for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // z ka�dym innym obiektem dynamicznym,...
					{
						if (i != j) // ...ale nie z samym sob�
						{
							if (DistanceBetweenDynCenterPow2(m_currentMap->vecDyn[i], m_currentMap->vecDyn[j]) < fCollisionDetectionDistancePow2)
								// sprawdzenie kolizji przeprowad� tylko je�eli obiekty sa blisko siebie 
								// (funkcja zwraca odleg�o�� do kwadradu, aby unikn�� zasoboch�onnego pierwiastkowania liczby zmiennoprzecinkowej)
							{
								//sprawdzanie kolizji w osi X
								if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
									m_currentMap->vecDyn[i]->py < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) &&
									(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
									// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to stara pozycja)
								{
									if (m_currentMap->vecDyn[i]->vx <= 0)	// kolizja nast�pi�a przy ruchu w lewo
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nast�puje tylko wetdy 
											//kiedy obydwa obiekty podlegaj� kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vx = 0.0f;
											fNewpx = m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth;
										}

										// je�li zasz�a kolizja wywo�aj interakcj� mi�dzy obiektami
										// je�li funkcja zwr�ci true to przerwij wykowynawie obecnej iteracji p�tli gry i rozpocznij nast�pn�
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
									else						// kolizja nast�pi�a przy ruchu w prawo
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nast�puje tylko wetdy 
											//kiedy obydwa obiekty podlegaj� kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vx = 0.0f;
											fNewpx = m_currentMap->vecDyn[j]->px - m_currentMap->vecDyn[i]->fWidth;
										}

										// je�li zasz�a kolizja wywo�aj interakcj� mi�dzy obiektami
										// je�li funkcja zwr�ci true to przerwij wykowynawie obecnej iteracji p�tli gry i rozpocznij nast�pn�
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
								}

								//sprawdzanie kolizji w osi Y
								if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
									fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
									// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to nowa pozycja)
								{
									if (m_currentMap->vecDyn[i]->vy <= 0)	// kolizja nast�pi�a przy ruchu w g�r�
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nast�puje tylko wetdy 
											//kiedy obydwa obiekty podlegaj� kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vy = 0.0f;
											fNewpy = m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight;
										}

										// je�li zasz�a kolizja wywo�aj interakcj� mi�dzy obiektami
										// je�li funkcja zwr�ci true to przerwij wykowynawie obecnej iteracji p�tli gry i rozpocznij nast�pn�
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
									else						//kolizja nast�pi�a przy ruchu w d�
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nast�puje tylko wetdy 
											//kiedy obydwa obiekty podlegaj� kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vy = 0.0f;
											fNewpy = m_currentMap->vecDyn[j]->py - m_currentMap->vecDyn[i]->fHeight;
										}

										// je�li zasz�a kolizja wywo�aj interakcj� mi�dzy obiektami
										// je�li funkcja zwr�ci true to przerwij wykowynawie obecnej iteracji p�tli gry i rozpocznij nast�pn�
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
								}

								//koniec sprawdzania w�a�ciwej kolizji
							}
						}
					}



					//je�eli obiekt jest graczem, przeprowad� dodatkow� detekcj� kolizji aktywuj�c� interakcj�
					if (m_currentMap->vecDyn[i]->sName == "player")
					{
						if (bKeyPressedInteract) // je�li gracz wcisn�� klawisz interakcji
						{
							// sprawd� czy podczas pr�by interakcji gracz nie znajduje si� na obiekcie 
							// z kt�rym mo�na wykona� interakcj� (INTERACT_NATURE::INTERACT_KEY)

							for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // sprawd� dla ka�dego obiektu dynamicznego
							{
								if (m_currentMap->vecDyn[i]->vx <= 0) //ruch w lewo
								{
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										m_currentMap->vecDyn[i]->py < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) &&
										(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to stara pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}
								else // ruch w prawo
								{
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										m_currentMap->vecDyn[i]->py < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) &&
										(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to stara pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}

								if (m_currentMap->vecDyn[i]->vy <= 0)//ruch w g�r�
								{
									//sprawdzanie kolizji w osi Y
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to nowa pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}
								else // ruch w d�
								{
									//sprawdzanie kolizji w osi Y
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok�ty si� nak�adaj� (o� Y to nowa pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}
							}

							// sprawd� czy nie zachodzi kolizja punktu testowego z innym obiektem
							// dynamicznym z kt�rym mo�e zaj�� interakcja (INTERACT_NATURE::TALK)
							for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // sprawd� dla ka�dego obiektu dynamicznego
							{
								if (i != j) // ale nie dla samego siebie
								{
									// dla ka�dego kierunku w kt�r� zwr�cony jest gracz
									// ustaw po�o�enie punktu testowego p� pola przed graczem
									switch (m_currentMap->vecDyn[i]->nDirection)
									{
									case cDynamic::NORTH:
									{
										float fTestX = m_currentMap->vecDyn[i]->px + (m_currentMap->vecDyn[i]->fWidth / 2.0f);
										float fTestY = m_currentMap->vecDyn[i]->py - 0.5f;
										// sprawdzenie czy punkt testowy zawarty jest w drugim obiekcie
										if (fTestX < m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth && fTestX > m_currentMap->vecDyn[j]->px &&
											fTestY < m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight && fTestY > m_currentMap->vecDyn[j]->py)
										{
											if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::TALK, m_currentMap->vecDyn[i]))
												return true;
										}
										break;
									}
									case cDynamic::EAST:
									{
										float fTestX = m_currentMap->vecDyn[i]->px + m_currentMap->vecDyn[i]->fWidth + 0.5f;
										float fTestY = m_currentMap->vecDyn[i]->py + (m_currentMap->vecDyn[i]->fHeight / 2.0f);
										// sprawdzenie czy punkt testowy zawarty jest w drugim obiekcie
										if (fTestX < m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth && fTestX > m_currentMap->vecDyn[j]->px &&
											fTestY < m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight && fTestY > m_currentMap->vecDyn[j]->py)
										{
											if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::TALK, m_currentMap->vecDyn[i]))
												return true;
										}
										break;
									}
									case cDynamic::SOUTH:
									{
										float fTestX = m_currentMap->vecDyn[i]->px + (m_currentMap->vecDyn[i]->fWidth / 2.0f);
										float fTestY = m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight + 0.5f;
										// sprawdzenie czy punkt testowy zawarty jest w drugim obiekcie
										if (fTestX < m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth && fTestX > m_currentMap->vecDyn[j]->px &&
											fTestY < m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight && fTestY > m_currentMap->vecDyn[j]->py)
										{
											if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::TALK, m_currentMap->vecDyn[i]))
												return true;
										}
										break;
									}
									case cDynamic::WEST:
									{
										float fTestX = m_currentMap->vecDyn[i]->px - 0.5f;
										float fTestY = m_currentMap->vecDyn[i]->py + (m_currentMap->vecDyn[i]->fHeight / 2.0f);
										// sprawdzenie czy punkt testowy zawarty jest w drugim obiekcie
										if (fTestX < m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth && fTestX > m_currentMap->vecDyn[j]->px &&
											fTestY < m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight && fTestY > m_currentMap->vecDyn[j]->py)
										{
											if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::TALK, m_currentMap->vecDyn[i]))
												return true;
										}
										break;
									}

									}	// switch
								}
							}
						}
						// niezale�nie czy zasz�a kolizja czy nie, po pr�bie wykrycia interakcji ustaw flag�
						// wci�ni�cia klawiszu interakcji u�ytkownika jako nieaktywn�
						bKeyPressedInteract = false;
					}

					//aktualizacja po�o�enia po sprawdzeniu czy nie zajdzie kolizja statyczna i dynamiczna
					m_currentMap->vecDyn[i]->px = fNewpx;
					m_currentMap->vecDyn[i]->py = fNewpy;

					// je�li obiekt jest niepotrzebny (np. jako pocisk trafi� na �cian� lub min�a jego �ywotno��) to go usu�
					if (m_currentMap->vecDyn[i]->bIsRedundant)
						m_currentMap->RemoveDynamic(i);
				}
			}
		}
	}
	
	//aktualizacja timera animacji element�w mapy
	if (!m_bShowMessage && !bPause)
	{
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
	}

	//render!

	//rysowanie mapy z wykorzystaniem przewijania ekranu:

	//pozycja kamery (przyklejonia do gracza) je�li silnik skrypt�w na to zezwala
	if (ScriptEngine.bCameraFollowsPlayer)
	{
		fCameraPosX = pPlayer->px;
		fCameraPosY = pPlayer->py;
	}

	//obliczanie liczby widocznych p�l na ekranie
	int nVisibleTilesX = ScreenWidth() / nTileWidth;
	int nVisibleTilesY = ScreenHeight() / nTileHeight;

	//obliczanie offsetu
	float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
	float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

	//ograniczenie offestu przy kraw�dziach mapy
	if (fOffsetX < 0) fOffsetX = 0.0f;
	if (fOffsetY < 0) fOffsetY = 0.0f;
	if (fOffsetX > m_currentMap->nLevelWidth - nVisibleTilesX) fOffsetX = (float)(m_currentMap->nLevelWidth - nVisibleTilesX);
	if (fOffsetY > m_currentMap->nLevelHeight - nVisibleTilesY) fOffsetY = (float)(m_currentMap->nLevelHeight - nVisibleTilesY);

	//offset pojedy�czego pola do p�ynnego przewijania mapy 
	float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
	float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

	//rysowanie mapy warstwa pierwsza
	for (int x = 0; x < nVisibleTilesX + 1; x++)
	{
		for (int y = 0; y < nVisibleTilesY + 1; y++)
		{
			int index = m_currentMap->GetIndex((int)(x + fOffsetX), (int)(y + fOffsetY));
			if (index != 0)
			{
				// sprawdzenie czy mamy do czynienia z animowanym polem i je�li tak to kt�r� klatk� nale�y wy�wietli�
				if (m_currentMap->GetIsAnimated((int)(x + fOffsetX), (int)(y + fOffsetY)) == 1)
					if (m_nStaticAnimFrame == 1)
						index++;	// je�li nale�y wy�wietli� drug� klatk� animacji to wy�wietl grafik� o ID zwi�kszonym o jeden

				// interpretacja indeksu jako wsp�rz�dnych p�l w ca�ym tile secie
				int ix = index % 10;
				int iy = index / 10;
				DrawPartialSprite((int)(x* nTileWidth - fTileOffsetX), (int)(y* nTileHeight - fTileOffsetY),
					m_currentMap->sprite, ix* nTileWidth, iy* nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// je�li w��czono odpowienie ustawienia
	// ustawienie trybu renderowania na uwzgl�dniaj�cy prze�roczysto�� drugiej i trzeciej warstwy mapy i obiekt�w dynamicznych
	if(bGfxHighSettings)
		SetPixelMode(olc::Pixel::ALPHA);
	else
		SetPixelMode(olc::Pixel::MASK);

	//rysowanie mapy warstwa druga
	for (int x = 0; x < nVisibleTilesX + 1; x++)
	{
		for (int y = 0; y < nVisibleTilesY + 1; y++)
		{
			int index2 = m_currentMap->GetIndex2((int)(x + fOffsetX), (int)(y + fOffsetY));
			if (index2 != 0)
			{
				// interpretacja indeksu jako wsp�rz�dnych p�l w ca�ym tile secie
				int ix2 = index2 % 10;
				int iy2 = index2 / 10;
				DrawPartialSprite((int)(x * nTileWidth - fTileOffsetX), (int)(y * nTileHeight - fTileOffsetY), 
					m_currentMap->sprite, ix2 * nTileWidth, iy2 * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// rysowanie wszystkich obiekt�w dynamicznych

	// najpierw narysuj wszystkie obiekty warstwy 0 (np. po�wiata teleporter�w, przedmioty na ziemii, interaktywne elementy mapy, itp)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 0)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// p�niej narysuj obiekty wartswy 1 (zw�oki)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 1)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// p�niej narysuj obiekty warstwy 2 (wi�kszo�� obiekt�w)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 2)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// rysowanie mapy warstwa trzecia: warstwa kt�ra zawsze rysowana jest nad obiektami dynamicznymi
	// np. g�rne cz�ci filar�w kt�re s� "przed" stworami
	for (int x = 0; x < nVisibleTilesX + 1; x++)
	{
		for (int y = 0; y < nVisibleTilesY + 1; y++)
		{
			int index3 = m_currentMap->GetIndex3((int)(x + fOffsetX), (int)(y + fOffsetY));
			if (index3 != 0)
			{
				// interpretacja indeksu jako wsp�rz�dnych p�l w ca�ym tile secie
				int ix3 = index3 % 10;
				int iy3 = index3 / 10;
				DrawPartialSprite((int)(x * nTileWidth - fTileOffsetX), (int)(y * nTileHeight - fTileOffsetY),
					m_currentMap->sprite, ix3 * nTileWidth, iy3 * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// p�niej narysuj obiekty warstwy 3 (obiekty "lataj�ce", b�d� po�o�one ponad reszt� obiekt�w dynamicznych)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 3)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	//na koniec narysuj obiekty dynamiczne warstwy 4 (ba�ki emotikony)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 4)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	//Interfejs!

	//Dialogi - wy�wietlanie
	if (!m_bShowMessage)
		if (m_bShowDialog)
			DrawFrontDialog(UI_FromScreenBorder, UI_FromScreenBorder);
	
	//HP, wytrzyma�o�� i wygaszenie ekranu
	DrawUI(fElapsedTime);

	//Komunikaty - wy�wietlanie
	if(m_bShowMessage)
		DisplayFrontMessage();

	//komunikat o zapauzowanej grze
	if (bPause)
	{
		FillRect((ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2 - 1, 49, 18, olc::RED);
		DrawText("Pause", (ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2, TXT_WHITE);
		DrawText("Press P", (ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2 + 8, TXT_WHITE);
	}

	// powr�t do domy�lnego trybu renderowania aby zaoszcz�dzi� wydajno��
	SetPixelMode(olc::Pixel::NORMAL);

	return true;
}