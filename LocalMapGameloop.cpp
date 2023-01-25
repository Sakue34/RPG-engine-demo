#include "Engine.h"
#include "Dynamic.h"
#include "Map.h"
#include "All_Dynamics.h"

bool cEngine::UpdateLocalMap(float fElapsedTime) // tryb gry 1 - mapa lokalna
{
	//obs³uga sterowania
	bool bHasPlayerAcceleratedX = false;
	bool bHasPlayerAcceleratedY = false;

	bool bKeyPressedInteract = false;
	bool bKeyPressedAttack = false;

	//pobieranie sterowania tylko jeœli okno gry jest aktywne
	if (IsFocused())
	{
		// jeœli silnik uznaje ¿e gracz ma kontrolê (nie dzia³a ¿aden skrypt itp) to zezwól na sterowanie
		if (ScriptEngine.bPlayerInControl)
		{
			if (!bPause) // jeœli gra nie jest spauzowana
			{
				if (pPlayer->nState != cDynamicCreature::STATE_DEAD) // zezwól na sterowanie tylko jeœli gracz nie jest martwy
				{
					if (!m_bShowMessage) // jeœli nie wyœwietla siê komunikat
					{
						// poruszanie, atak i interakcja gracza mo¿liwa tylko jeœli ten nie jest obecnie odrzucany (knockback) 
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
									if (m_bShowDialog == false && m_bShowMessage == false) // jeœli nie wyœwietla siê ¿aden dialog ani komunikat
										bKeyPressedInteract = true;
								}
								if (GetKey(olc::Key::SPACE).bPressed) // spacja - atak
								{
									bKeyPressedAttack = true;
								}
								if (GetKey(olc::Key::ENTER).bPressed) // enter - odskok
								{
									if (PlayerData.fStamina >= PlayerData.fStaminaDashCost) // jeœli gracz ma wystarczaj¹co wytrzyma³oœci
									{
										if (abs(pPlayer->vx) > 0.2f || abs(pPlayer->vy) > 0.2f) // jeœli nie stoi w miejscu przed wykonaniem doskoku
										{
											pPlayer->Knockback(pPlayer->vx * 3.0f * PlayerData.fDashVelocityMultiplier,
												pPlayer->vy * 3.0f * PlayerData.fDashVelocityMultiplier, PlayerData.fDashExecutionTime);
										}
										else // jeœli gracz stoi w miejscu to odskok wykonaj w kierunku zgodnym z kierunkiem jego sprite'a
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
							// sterowanie niezale¿ne od tego, ¿e postaæ gracza œpi lub jest nieprzytomna
							// ...
						}
						// sterowanie niezale¿ne od bycia w powietrzu
						// ...
					}

					//sterowanie niezale¿ne od tego, ¿e wyœwietla siê komunikat
					if (GetKey(olc::Key::E).bPressed) // E - pominiêcie obecnego dialogu jeœli nie wyœwietla siê ¿aden komunikat ani ¿aden skrypt nie oczekuje na pominiêcie
					{
						if (!m_bShowMessage)
							if(!ScriptEngine.bWaitForManualSkip)
								if (m_bShowDialog)
									NextDialog();
						
					}
				}
				//sterowanie nezale¿ne od bycia martwym
				// ...
			}
			// sterowanie niezale¿ne od pauzy i bycia martwym
			// ...
		}
		//sterowanie niezale¿ne od tego, ¿e silnik skryptów nie zezwala na sterowanie
		if (GetKey(olc::Key::E).bPressed) // E - pominiêcie obecnego komunikatu, a jeœli ¿adnego nie ma, to pominiêcie obecnego skryptu czekaj¹cego na manualne pominiêcie
		{
			if (m_bShowMessage)
				NextMessage();
			else
			{
				if (ScriptEngine.bWaitForManualSkip)
					if (!bPause) // pod warunkiem ¿e gra nie zosta³a spauzowana
						ScriptEngine.bWaitForManualSkip = false;
			}
		}

		if (GetKey(olc::Key::O).bPressed) // prze³¹czanie ustawieñ graficznych - czy silnik ma obs³ugiwaæ czêœciow¹ przeŸroczystoœæ sprite'ów
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

	if (!bPause) //jeœli gra nie jest zpauzowana
	{
		if (!m_bShowMessage) //jeœli nie wyœwietla siê ¿aden komunikat
		{
			//obs³uga skrypytów
			ScriptEngine.UpdateScripts(fElapsedTime);

			//jeœli ¿aden skrypt nie zamrozi³ czasu
			if (!ScriptEngine.bTimeIsFreezed)
			{
				//przekalkulowanie statystyk gracza
				RecalculatePlayerStats();

				//timer czasu od ostatniego u¿ycia akcji wymagaj¹cej wytrzyma³oœci
				PlayerData.fStaminaTimer -= fElapsedTime;
				if (PlayerData.fStaminaTimer < 0.0f)
					PlayerData.fStaminaTimer = 0.0f;

				// regeneracja wytrzyma³oœci
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
						if (PlayerData.currentWeapon != nullptr) // jeœli gracz posiada za³o¿on¹ broñ
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

				//obliczanie ruchu wszystkich obiektów dynamicznych
				for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
				{
					//obs³uga "pocisków" - aktualizacja czasu i statusu przestarza³ego
					if (m_currentMap->vecDyn[i]->bIsProjectile)
					{
						m_currentMap->vecDyn[i]->fProjectileTime -= fElapsedTime;
						if (m_currentMap->vecDyn[i]->fProjectileTime <= 0.0f)
							m_currentMap->vecDyn[i]->bIsRedundant = true;
					}

					// modyfikacje ruchu gracza
					if (m_currentMap->vecDyn[i]->sName == "player")
					{
						// jeœli gracz w³aœnie nie jest odrzucany i nie podlega w³aœnie skryptowi
						if (m_currentMap->vecDyn[i]->bIsKnockbacked == false && pPlayer->bIsMovedByScript == false)
						{
							//spowolnienie
							if (!bHasPlayerAcceleratedX)
							{
								float decelerationX = -16.0f * m_currentMap->vecDyn[i]->vx * fElapsedTime;

								//zabezpieczenie przed spowolnieniem powoduj¹cym zmianê zwrotu kierunku wektora prêdkoœci gracza
								//przy niskiej wartoœci klatek na sekundê
								if (abs(decelerationX) > m_currentMap->vecDyn[i]->vx)
									decelerationX = -m_currentMap->vecDyn[i]->vx;

								m_currentMap->vecDyn[i]->vx += decelerationX;
							}
							if (!bHasPlayerAcceleratedY)
							{
								float decelerationY = -16.0f * m_currentMap->vecDyn[i]->vy * fElapsedTime;

								//zabezpieczenie przed spowolnieniem powoduj¹cym zmianê zwrotu kierunku wektora prêdkoœci gracza
								//przy niskiej wartoœci klatek na sekundê
								if (abs(decelerationY) > m_currentMap->vecDyn[i]->vy)
									decelerationY = -m_currentMap->vecDyn[i]->vy;

								m_currentMap->vecDyn[i]->vy += decelerationY;
							}
						}
					}

					//aktualizacja stanu, animacji, odrzutu i AI ka¿dego obiektu dynamicznego
					m_currentMap->vecDyn[i]->Update(fElapsedTime, pPlayer);

					// jeœli po aktualizacji obiektów dynamicznych zmieni³a siê prêdkoœæ gracza i nie stoi on ju¿ w miejscu
					// (grafika miecza i gracza nie pokrywa³aby siê)
					// to wtedy usuñ miecz gracza
					if (m_currentMap->vecDyn[i]->sName == "player melee")
						if (pPlayer->vx != 0.0f || pPlayer->vy != 0.0f)
							m_currentMap->vecDyn[i]->bIsRedundant = true;

					//ustawienie prêdkoœci ka¿dego cia³a jako zero przy prêdkoœciach bliskich zeru
					if (abs(m_currentMap->vecDyn[i]->vx) < 0.005f)	m_currentMap->vecDyn[i]->vx = 0.0f;
					if (abs(m_currentMap->vecDyn[i]->vy) < 0.005f)	m_currentMap->vecDyn[i]->vy = 0.0f;

					//potencjalne nowe po³o¿enie
					float fNewpx = m_currentMap->vecDyn[i]->px + (m_currentMap->vecDyn[i]->vx * fElapsedTime);
					float fNewpy = m_currentMap->vecDyn[i]->py + (m_currentMap->vecDyn[i]->vy * fElapsedTime);

					//krawêdŸ kolizji statycznej
					float fBorder = 0.1f;

					//kolizja statyczna
					if (m_currentMap->vecDyn[i]->bSolidVsSolid)
					{
						if (m_currentMap->vecDyn[i]->vx <= 0)	// ruch w lewo
						{
							if (m_currentMap->vecDyn[i]->fWidth > 1.0f) // sprawdzenie czy obiekt jest szerszy ni¿ szerokoœæ jednej kafelki i obs³uga kolizji w odpowiedni sposób
							{
								//sprawdzenie czy wierzcho³ki koliduj¹ z map¹
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									bCollision = true;
								}

								if (!bCollision) // jeœli wierzcho³ki nie koliduj¹, sprawdŸ punkty po³o¿one na krawêdziach pokrywaj¹ce ca³y bok prostok¹ta w równych odstêpach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(m_currentMap->vecDyn[i]->py + z)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpx = (int)fNewpx + 1.0f;
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
							else // szerokoœæ obiektu jest mniejsza lub równa 1
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
							if (m_currentMap->vecDyn[i]->fWidth > 1.0f) // sprawdzenie czy obiekt jest szerszy ni¿ szerokoœæ jednej kafelki i obs³uga kolizji w odpowiedni sposób
							{
								//sprawdzenie czy wierzcho³ki koliduj¹ z map¹
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									bCollision = true;
								}

								if (!bCollision) // jeœli wierzcho³ki nie koliduj¹, sprawdŸ punkty po³o¿one na krawêdziach pokrywaj¹ce ca³y bok prostok¹ta w równych odstêpach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + z)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpx = (int)fNewpx + (int)m_currentMap->vecDyn[i]->fWidth - m_currentMap->vecDyn[i]->fWidth;
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
							else // szerokoœæ obiektu jest mniejsza lub równa 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + 0.0f)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth), (int)(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight - fBorder)))
								{
									fNewpx = (int)fNewpx + (1.0f - m_currentMap->vecDyn[i]->fWidth);
									m_currentMap->vecDyn[i]->vx = 0.0f;
								}
							}
						}

						if (m_currentMap->vecDyn[i]->vy <= 0)	// ruch w górê
						{
							if (m_currentMap->vecDyn[i]->fHeight > 1.0f) // sprawdzenie czy obiekt jest wy¿szy ni¿ wysokoœæ jednej kafelki i obs³uga kolizji w odpowiedni sposób
							{
								//sprawdzenie czy wierzcho³ki koliduj¹ z map¹
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy)) || m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy)))
								{
									bCollision = true;
								}

								if (!bCollision) // jeœli wierzcho³ki nie koliduj¹, sprawdŸ punkty po³o¿one na krawêdziach pokrywaj¹ce ca³y bok prostok¹ta w równych odstêpach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + z), (int)(fNewpy)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpy = (int)fNewpy + 1.0f;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
							else // wysokoœæ obiektu jest mniejsza lub równa 1
							{
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy)) || m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy)))
								{
									fNewpy = (int)fNewpy + 1.0f;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
						}
						else						// ruch w dó³
						{
							if (m_currentMap->vecDyn[i]->fHeight > 1.0f) // sprawdzenie czy obiekt jest wy¿szy ni¿ wysokoœæ jednej kafelki i obs³uga kolizji w odpowiedni sposób
							{
								//sprawdzenie czy wierzcho³ki koliduj¹ z map¹
								bool bCollision = false;
								if (m_currentMap->GetSolid((int)(fNewpx + 0.0f), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)) ||
									m_currentMap->GetSolid((int)(fNewpx + m_currentMap->vecDyn[i]->fWidth - fBorder), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)))
								{
									bCollision = true;
								}

								if (!bCollision) // jeœli wierzcho³ki nie koliduj¹, sprawdŸ punkty po³o¿one na krawêdziach pokrywaj¹ce ca³y bok prostok¹ta w równych odstêpach
									for (int z = 1; z < m_currentMap->vecDyn[i]->fHeight; z++)
										if (m_currentMap->GetSolid((int)(fNewpx + z), (int)(fNewpy + m_currentMap->vecDyn[i]->fHeight)))
											bCollision = true;

								if (bCollision) // egzekucja kolizji
								{
									fNewpy = fNewpy = (int)fNewpy + (int)m_currentMap->vecDyn[i]->fHeight - m_currentMap->vecDyn[i]->fHeight;
									m_currentMap->vecDyn[i]->vy = 0.0f;
								}
							}
							else // wysokoœæ obiektu jest mniejsza lub równa 1
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

					//w³aœciwa kolizja dynamiczna + (INTERACT_NATURE::WALK_ON)
					//kolizja wszystkich obiektów dynamicznych...
					for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // z ka¿dym innym obiektem dynamicznym,...
					{
						if (i != j) // ...ale nie z samym sob¹
						{
							if (DistanceBetweenDynCenterPow2(m_currentMap->vecDyn[i], m_currentMap->vecDyn[j]) < fCollisionDetectionDistancePow2)
								// sprawdzenie kolizji przeprowadŸ tylko je¿eli obiekty sa blisko siebie 
								// (funkcja zwraca odleg³oœæ do kwadradu, aby unikn¹æ zasoboch³onnego pierwiastkowania liczby zmiennoprzecinkowej)
							{
								//sprawdzanie kolizji w osi X
								if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
									m_currentMap->vecDyn[i]->py < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) &&
									(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
									// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to stara pozycja)
								{
									if (m_currentMap->vecDyn[i]->vx <= 0)	// kolizja nast¹pi³a przy ruchu w lewo
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nastêpuje tylko wetdy 
											//kiedy obydwa obiekty podlegaj¹ kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vx = 0.0f;
											fNewpx = m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth;
										}

										// jeœli zasz³a kolizja wywo³aj interakcjê miêdzy obiektami
										// jeœli funkcja zwróci true to przerwij wykowynawie obecnej iteracji pêtli gry i rozpocznij nastêpn¹
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
									else						// kolizja nast¹pi³a przy ruchu w prawo
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nastêpuje tylko wetdy 
											//kiedy obydwa obiekty podlegaj¹ kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vx = 0.0f;
											fNewpx = m_currentMap->vecDyn[j]->px - m_currentMap->vecDyn[i]->fWidth;
										}

										// jeœli zasz³a kolizja wywo³aj interakcjê miêdzy obiektami
										// jeœli funkcja zwróci true to przerwij wykowynawie obecnej iteracji pêtli gry i rozpocznij nastêpn¹
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
								}

								//sprawdzanie kolizji w osi Y
								if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
									fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
									// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to nowa pozycja)
								{
									if (m_currentMap->vecDyn[i]->vy <= 0)	// kolizja nast¹pi³a przy ruchu w górê
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nastêpuje tylko wetdy 
											//kiedy obydwa obiekty podlegaj¹ kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vy = 0.0f;
											fNewpy = m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight;
										}

										// jeœli zasz³a kolizja wywo³aj interakcjê miêdzy obiektami
										// jeœli funkcja zwróci true to przerwij wykowynawie obecnej iteracji pêtli gry i rozpocznij nastêpn¹
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
									else						//kolizja nast¹pi³a przy ruchu w dó³
									{
										if (m_currentMap->vecDyn[i]->bSolidVsDynamic && m_currentMap->vecDyn[j]->bSolidVsDynamic) // Egzekucja kolizji nastêpuje tylko wetdy 
											//kiedy obydwa obiekty podlegaj¹ kolizji dynamicznej
										{
											m_currentMap->vecDyn[i]->vy = 0.0f;
											fNewpy = m_currentMap->vecDyn[j]->py - m_currentMap->vecDyn[i]->fHeight;
										}

										// jeœli zasz³a kolizja wywo³aj interakcjê miêdzy obiektami
										// jeœli funkcja zwróci true to przerwij wykowynawie obecnej iteracji pêtli gry i rozpocznij nastêpn¹
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::WALK_ON, m_currentMap->vecDyn[i]))
											return true;

									}
								}

								//koniec sprawdzania w³aœciwej kolizji
							}
						}
					}



					//je¿eli obiekt jest graczem, przeprowadŸ dodatkow¹ detekcjê kolizji aktywuj¹c¹ interakcjê
					if (m_currentMap->vecDyn[i]->sName == "player")
					{
						if (bKeyPressedInteract) // jeœli gracz wcisn¹³ klawisz interakcji
						{
							// sprawdŸ czy podczas próby interakcji gracz nie znajduje siê na obiekcie 
							// z którym mo¿na wykonaæ interakcjê (INTERACT_NATURE::INTERACT_KEY)

							for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // sprawdŸ dla ka¿dego obiektu dynamicznego
							{
								if (m_currentMap->vecDyn[i]->vx <= 0) //ruch w lewo
								{
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										m_currentMap->vecDyn[i]->py < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) &&
										(m_currentMap->vecDyn[i]->py + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to stara pozycja)
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
										// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to stara pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}

								if (m_currentMap->vecDyn[i]->vy <= 0)//ruch w górê
								{
									//sprawdzanie kolizji w osi Y
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to nowa pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}
								else // ruch w dó³
								{
									//sprawdzanie kolizji w osi Y
									if (fNewpx < (m_currentMap->vecDyn[j]->px + m_currentMap->vecDyn[j]->fWidth) && (fNewpx + m_currentMap->vecDyn[i]->fWidth) > m_currentMap->vecDyn[j]->px &&
										fNewpy < (m_currentMap->vecDyn[j]->py + m_currentMap->vecDyn[j]->fHeight) && (fNewpy + m_currentMap->vecDyn[i]->fHeight) > m_currentMap->vecDyn[j]->py)
										// sprawdzenie czy prostok¹ty siê nak³adaj¹ (oœ Y to nowa pozycja)
									{
										if (m_currentMap->vecDyn[j]->OnInteract(pPlayer, cDynamic::INTERACT_KEY, pPlayer))
											return true;
									}
								}
							}

							// sprawdŸ czy nie zachodzi kolizja punktu testowego z innym obiektem
							// dynamicznym z którym mo¿e zajœæ interakcja (INTERACT_NATURE::TALK)
							for (unsigned int j = 0; j < m_currentMap->vecDyn.size(); j++) // sprawdŸ dla ka¿dego obiektu dynamicznego
							{
								if (i != j) // ale nie dla samego siebie
								{
									// dla ka¿dego kierunku w któr¹ zwrócony jest gracz
									// ustaw po³o¿enie punktu testowego pó³ pola przed graczem
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
						// niezale¿nie czy zasz³a kolizja czy nie, po próbie wykrycia interakcji ustaw flagê
						// wciœniêcia klawiszu interakcji u¿ytkownika jako nieaktywn¹
						bKeyPressedInteract = false;
					}

					//aktualizacja po³o¿enia po sprawdzeniu czy nie zajdzie kolizja statyczna i dynamiczna
					m_currentMap->vecDyn[i]->px = fNewpx;
					m_currentMap->vecDyn[i]->py = fNewpy;

					// jeœli obiekt jest niepotrzebny (np. jako pocisk trafi³ na œcianê lub minê³a jego ¿ywotnoœæ) to go usuñ
					if (m_currentMap->vecDyn[i]->bIsRedundant)
						m_currentMap->RemoveDynamic(i);
				}
			}
		}
	}
	
	//aktualizacja timera animacji elementów mapy
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

	//pozycja kamery (przyklejonia do gracza) jeœli silnik skryptów na to zezwala
	if (ScriptEngine.bCameraFollowsPlayer)
	{
		fCameraPosX = pPlayer->px;
		fCameraPosY = pPlayer->py;
	}

	//obliczanie liczby widocznych pól na ekranie
	int nVisibleTilesX = ScreenWidth() / nTileWidth;
	int nVisibleTilesY = ScreenHeight() / nTileHeight;

	//obliczanie offsetu
	float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
	float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

	//ograniczenie offestu przy krawêdziach mapy
	if (fOffsetX < 0) fOffsetX = 0.0f;
	if (fOffsetY < 0) fOffsetY = 0.0f;
	if (fOffsetX > m_currentMap->nLevelWidth - nVisibleTilesX) fOffsetX = (float)(m_currentMap->nLevelWidth - nVisibleTilesX);
	if (fOffsetY > m_currentMap->nLevelHeight - nVisibleTilesY) fOffsetY = (float)(m_currentMap->nLevelHeight - nVisibleTilesY);

	//offset pojedyñczego pola do p³ynnego przewijania mapy 
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
				// sprawdzenie czy mamy do czynienia z animowanym polem i jeœli tak to któr¹ klatkê nale¿y wyœwietliæ
				if (m_currentMap->GetIsAnimated((int)(x + fOffsetX), (int)(y + fOffsetY)) == 1)
					if (m_nStaticAnimFrame == 1)
						index++;	// jeœli nale¿y wyœwietliæ drug¹ klatkê animacji to wyœwietl grafikê o ID zwiêkszonym o jeden

				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix = index % 10;
				int iy = index / 10;
				DrawPartialSprite((int)(x* nTileWidth - fTileOffsetX), (int)(y* nTileHeight - fTileOffsetY),
					m_currentMap->sprite, ix* nTileWidth, iy* nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// jeœli w³¹czono odpowienie ustawienia
	// ustawienie trybu renderowania na uwzglêdniaj¹cy przeŸroczystoœæ drugiej i trzeciej warstwy mapy i obiektów dynamicznych
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
				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix2 = index2 % 10;
				int iy2 = index2 / 10;
				DrawPartialSprite((int)(x * nTileWidth - fTileOffsetX), (int)(y * nTileHeight - fTileOffsetY), 
					m_currentMap->sprite, ix2 * nTileWidth, iy2 * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// rysowanie wszystkich obiektów dynamicznych

	// najpierw narysuj wszystkie obiekty warstwy 0 (np. poœwiata teleporterów, przedmioty na ziemii, interaktywne elementy mapy, itp)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 0)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// póŸniej narysuj obiekty wartswy 1 (zw³oki)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 1)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// póŸniej narysuj obiekty warstwy 2 (wiêkszoœæ obiektów)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 2)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	// rysowanie mapy warstwa trzecia: warstwa która zawsze rysowana jest nad obiektami dynamicznymi
	// np. górne czêœci filarów które s¹ "przed" stworami
	for (int x = 0; x < nVisibleTilesX + 1; x++)
	{
		for (int y = 0; y < nVisibleTilesY + 1; y++)
		{
			int index3 = m_currentMap->GetIndex3((int)(x + fOffsetX), (int)(y + fOffsetY));
			if (index3 != 0)
			{
				// interpretacja indeksu jako wspó³rzêdnych pól w ca³ym tile secie
				int ix3 = index3 % 10;
				int iy3 = index3 / 10;
				DrawPartialSprite((int)(x * nTileWidth - fTileOffsetX), (int)(y * nTileHeight - fTileOffsetY),
					m_currentMap->sprite, ix3 * nTileWidth, iy3 * nTileHeight, nTileWidth, nTileHeight);
			}
		}
	}

	// póŸniej narysuj obiekty warstwy 3 (obiekty "lataj¹ce", b¹dŸ po³o¿one ponad reszt¹ obiektów dynamicznych)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 3)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	//na koniec narysuj obiekty dynamiczne warstwy 4 (bañki emotikony)
	for (unsigned int i = 0; i < m_currentMap->vecDyn.size(); i++)
		if (m_currentMap->vecDyn[i]->nLayer == 4)
			m_currentMap->vecDyn[i]->DrawSelf(fOffsetX, fOffsetY);

	//Interfejs!

	//Dialogi - wyœwietlanie
	if (!m_bShowMessage)
		if (m_bShowDialog)
			DrawFrontDialog(UI_FromScreenBorder, UI_FromScreenBorder);
	
	//HP, wytrzyma³oœæ i wygaszenie ekranu
	DrawUI(fElapsedTime);

	//Komunikaty - wyœwietlanie
	if(m_bShowMessage)
		DisplayFrontMessage();

	//komunikat o zapauzowanej grze
	if (bPause)
	{
		FillRect((ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2 - 1, 49, 18, olc::RED);
		DrawText("Pause", (ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2, TXT_WHITE);
		DrawText("Press P", (ScreenWidth() - 42) / 2, UI_FromScreenBorder * 2 + 8, TXT_WHITE);
	}

	// powrót do domyœlnego trybu renderowania aby zaoszczêdziæ wydajnoœæ
	SetPixelMode(olc::Pixel::NORMAL);

	return true;
}