#include "Dynamic.h"
#include "Engine.h"
#include "Data.h"

cDynamic::cDynamic(cEngine* _engine)
{
	sprite = nullptr;
	px = 0.0f;
	py = 0.0f;

	fWidth = 1.0f;
	fHeight = 1.0f;

	vx = 0.0f;
	vy = 0.0f;

	bSolidVsSolid = true;
	bSolidVsDynamic = true;
	engine = _engine;

	fTime = 0.0f;

	nDirection = SOUTH;
	nLayer = 0;

	bFriendly = true;
	bIsProjectile = false;
	bIsKnockbacked = false;
	bInvincible = false;
	bIsRedundant = false;
	
	fKnockbackTimer = 0.0f;
	fProjectileTime = 0.0f;

	bIsMovedByScript = false;
}

cDynamic::cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr)
{
	sName = _name;
	sprite = spr;
	px = _px;
	py = _py;

	if (spr != nullptr)
	{
		fWidth = (spr->width) / 16.0f;
		fHeight = (spr->height) / 16.0f;
	}
	else
	{
		fWidth = 1.0f;
		fHeight = 1.0f;
	}

	vx = 0.0f;
	vy = 0.0f;

	bSolidVsSolid = true;
	bSolidVsDynamic = true;
	engine = _engine;

	fTime = 0.0f;

	nDirection = SOUTH;
	nLayer = 0;

	bFriendly = true;
	bIsProjectile = false;
	bIsKnockbacked = false;
	bInvincible = false;
	bIsRedundant = false;
	fKnockbackTimer = 0.0f;
	fProjectileTime = 0.0f;

	bIsMovedByScript = false;
}

cDynamic::cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic)
{
	sName = _name;
	sprite = spr;
	px = _px;
	py = _py;

	if (spr != nullptr)
	{
		fWidth = (spr->width) / 16.0f;
		fHeight = (spr->height) / 16.0f;
	}
	else
	{
		fWidth = 1.0f;
		fHeight = 1.0f;
	}

	vx = 0.0f;
	vy = 0.0f;

	bSolidVsSolid = _solidvssolid;
	bSolidVsDynamic = _solidvsdynamic;
	bFriendly = true;
	engine = _engine;

	fTime = 0.0f;

	nDirection = SOUTH;
	nLayer = 0;

	bIsProjectile = false;
	bIsKnockbacked = false;
	bInvincible = false;
	bIsRedundant = false;
	fKnockbackTimer = 0.0f;
	fProjectileTime = 0.0f;

	bIsMovedByScript = false;
}

cDynamic::cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, bool _friendly)
{
	sName = _name;
	sprite = spr;
	px = _px;
	py = _py;

	fWidth = (spr->width) / 16.0f;
	fHeight = (spr->height) / 16.0f;

	vx = 0.0f;
	vy = 0.0f;

	bSolidVsSolid = _solidvssolid;
	bSolidVsDynamic = _solidvsdynamic;
	bFriendly = _friendly;
	engine = _engine;

	fTime = 0.0f;

	nDirection = SOUTH;
	nLayer = 0;

	bIsProjectile = false;
	bIsKnockbacked = false;
	bInvincible = false;
	bIsRedundant = false;
	fKnockbackTimer = 0.0f;
	fProjectileTime = 0.0f;

	bIsMovedByScript = false;
}

void cDynamic::DrawSelf(float fOffsetX, float fOffsetY)
{
	engine->DrawSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite);
}

void cDynamic::SlowDown(float& v, float fElapsedTime, float rate = 1.0f)
{
	if (v > 0.0f) 
	{
		if ((v - fElapsedTime * rate) < 0.0f)
			v = 0.0f;
		else
			v -= fElapsedTime * rate;
	}
	if (v < 0.0f)
	{
		if ((v + fElapsedTime * rate) > 0.0f)
			v = 0.0f;
		else
			v += fElapsedTime * rate;
	}
}

cDynamicCreature::cDynamicCreature(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, 
	float _sizex, float _sizey, CREATURE_STATE _state, float _maxHP, bool _friendly, short _layer)
	: cDynamic(_engine, _name, _px, _py, spr, _solidvssolid, _solidvsdynamic, _friendly)
{
	fMaxHP = _maxHP;
	fHP = _maxHP;
	nState = _state;
	fWidth = _sizex;
	fHeight = _sizey;
	nLayer = _layer;
	nDefaultLayer = _layer;
	nFrame = 0;
	fAnimationDefaultInterval = 1.0f;
	fAnimationInterval = fAnimationDefaultInterval;
	fTime2 = 0.0f;
	fAIUpdateInterval = 1.0f;
	fMaxWalkingVel = 2.0f;
	fAIActivationDistance = 5.0f;
	fScalarSpeed = 0.0;
	fWalkAnimationSpeedMultiplier = 1.0f;
	fProneToKnockbackMultiplier = 1.0f;
	stats.fDmg = 1.0f;
	stats.fDmgFluct = 1.0f;
	stats.fKnockbackMultiplier = 1.0f;
	stats.fMeleeRange = 1.1f;
	fTime3 = 0.0f;
	fTime4 = 0.0f;
	fNewvx = 0.0f;
	fNewvy = 0.0f;
	fKnockbackSpeedDeclineMultiplier = 1.0f;
	bIsResistantToKnockback = false;
	fMaxAxisSpeed = fMaxWalkingVel / 1.4142f;
	bWalkAnimationAlwaysOn = false;
}

void cDynamicCreature::SetState(CREATURE_STATE _state)
{
	nState = _state;
}

void cDynamicCreature::ReceiveDamage(float dmg)
{
	fHP -= dmg;
}

void cDynamicCreature::PerformAttack(cDynamic* target)
{
	//lambda obliczaj¹ca obra¿enia zmiennoprzecinkowe z przedzia³u
	auto fRandFromTo = [](float min, float max)
	{
		return rand() / (float)RAND_MAX * (max - min) + min;
	};

	if (fTime3 <= 0.0f) // atak przeprowadŸ tylko jeœli skoñczy³ siê okres odnowienia ataku
	{
		//atak przeprowadŸ tylko jeœli obiekt nie jest nietykalny
		if (!target->bInvincible)
		{
			//nadaj obra¿enia
			target->ReceiveDamage(fRandFromTo(stats.fDmg, stats.fDmg + stats.fDmgFluct));
			//oblicz odrzut
			float fTargetX = target->px - px;
			float fTargetY = target->py - py;
			float fDist = sqrtf(fTargetX * fTargetX + fTargetY * fTargetY);
			target->Knockback((fTargetX / fDist) * stats.fKnockbackMultiplier * 4.0f, (fTargetY / fDist) * stats.fKnockbackMultiplier * 4.0f, stats.fKnockbackTimer);
			//czas odnowienia ataku podstawowego
			fTime3 = stats.fMeleeAttackCooldown;
			//czas odnowienia bezruchu po ataku podstawowym
			fTime4 = stats.fMeleeAttackImmobilityCooldown;
		}
	}
}

void cDynamicCreature::PerformInstantAttack(cDynamic* target)
{
	//lambda obliczaj¹ca obra¿enia zmiennoprzecinkowe z przedzia³u
	auto fRandFromTo = [](float min, float max)
	{
		return rand() / (float)RAND_MAX * (max - min) + min;
	};

	//atak przeprowadŸ tylko jeœli obiekt nie jest nietykalny
	if (!target->bInvincible)
	{
		//nadaj obra¿enia
		target->ReceiveDamage(fRandFromTo(stats.fDmg, stats.fDmg + stats.fDmgFluct));
		//oblicz odrzut
		float fTargetX = target->px - px;
		float fTargetY = target->py - py;
		float fDist = sqrtf(fTargetX * fTargetX + fTargetY * fTargetY);
		target->Knockback((fTargetX / fDist) * stats.fKnockbackMultiplier * 4.0f, (fTargetY / fDist) * stats.fKnockbackMultiplier * 4.0f, stats.fKnockbackTimer);
	}
}

void cDynamicCreature::AI_SimpleFollow(float fElapsedTime, cDynamic* player) // proste AI - zbli¿anie siê do gracza (OUTDATED!)
{
	//jeœli gracz nie jest martwy
	if (dynamic_cast<cDynamicCreature*>(player)->nState != STATE_DEAD)
	{
		//aktywuj tylko jeœli obiekt nie jest obecnie w powietrzu
		if (bIsKnockbacked)
			return;

		// jeœli odleg³oœæ miêdzy œrodkami obiektu i gracza jest mniejsza ni¿ dystans aktywacji 
		// to zacznij pod¹¿aæ za graczem
		if (engine->DistanceBetweenDynCenterPow2(this, player) < (fAIActivationDistance * fAIActivationDistance))
		{
			//ró¿nica pomiêdzy koordynatami gracza a potwora
			float fTargetX = player->px - px;
			float fTargetY = player->py - py;
			//odleg³oœæ miêdzy graczem a potworem
			float fDist = sqrtf(fTargetX * fTargetX + fTargetY * fTargetY);

			//odœwie¿ ruch tylko jeœli czas od ostatniej aktualizacji ruchu jest równy lub wiêkszy od okresu aktualizacji AI
			if (fTime2 < fAIUpdateInterval)
				return;

			//nadaj prêdkoœæ w kierunku po³o¿enia gracza
			fNewvx = (fTargetX / fDist) * fMaxWalkingVel;
			fNewvy = (fTargetY / fDist) * fMaxWalkingVel;
		}
		else // je¿eli gracz jest poza dystansem aktywacji AI to zaprzestañ ruchu 
		{
			SlowDown(fNewvx, fElapsedTime);
			SlowDown(fNewvy, fElapsedTime);
		}
	}
	else // je¿eli gracz jest martwy to zaprzestañ ruchu
	{
		//aktywuj tylko jeœli obiekt nie jest obecnie w powietrzu
		if (bIsKnockbacked)
			return;

		SlowDown(fNewvx, fElapsedTime);
		SlowDown(fNewvy, fElapsedTime);
	}

	// zresetuj licznik czasu od ostatniej aktualizacji AI
	fTime2 = 0.0f;
}

void cDynamicCreature::AI_SimpleFollowHostile(float fElapsedTime, cDynamic* player) // proste AI - zbli¿anie siê do gracza (wersja wroga)
{
	//jeœli obiekt jest poruszany przez skrypt to nie aktualizuj AI tylko przeka¿ dalej prêdkoœci
	if (bIsMovedByScript)
	{
		fNewvx = vx;
		fNewvy = vy;
		return;
	}

	//jeœli gracz nie jest martwy
	if (dynamic_cast<cDynamicCreature*>(player)->nState != STATE_DEAD)
	{
		//aktywuj tylko jeœli obiekt nie jest obecnie w powietrzu
		if (bIsKnockbacked)
			return;

		// jeœli odleg³oœæ miêdzy œrodkami obiektu i gracza jest mniejsza ni¿ dystans aktywacji 
		// to zacznij pod¹¿aæ za graczem
		if (engine->DistanceBetweenDynCenterPow2(this, player) < (fAIActivationDistance * fAIActivationDistance))
		{
			//ró¿nica pomiêdzy koordynatami gracza a potwora
			float fTargetX = player->px - px;
			float fTargetY = player->py - py;
			//odleg³oœæ miêdzy graczem a potworem
			float fDist = sqrtf(fTargetX * fTargetX + fTargetY * fTargetY);

			// WA¯NE: zasiêg ataku obliczany jest na podstawie odleg³oœci pomiêdzy œrodkami potwora i gracza
			// wiêc wraz ze wzrostem wymiarów potwora nale¿y zwiêkszaæ jego zasiêg ataku aby otrzymaæ taki sam zasiêg liczony od krawêdzi obiektów
			if (fDist <= stats.fMeleeRange) //jeœli gracz jest w zasiêgu i min¹³ czas odnowienia ataku to zaatakuj 
				if(!bFriendly)
					PerformAttack(player);

			//odœwie¿ ruch tylko jeœli czas od ostatniej aktualizacji ruchu jest równy lub wiêkszy od okresu aktualizacji AI
			if (fTime2 < fAIUpdateInterval)
				return;
			
			//nadaj prêdkoœæ w kierunku po³o¿enia gracza
			fNewvx = (fTargetX / fDist) * fMaxWalkingVel;
			fNewvy = (fTargetY / fDist) * fMaxWalkingVel;
		}
		else // je¿eli gracz jest poza dystansem aktywacji AI to zaprzestañ ruchu 
		{
			SlowDown(fNewvx, fElapsedTime);
			SlowDown(fNewvy, fElapsedTime);
		}
	}
	else // je¿eli gracz jest martwy to zaprzestañ ruchu
	{
		//aktywuj tylko jeœli obiekt nie jest obecnie w powietrzu
		if (bIsKnockbacked)
			return;

		SlowDown(fNewvx, fElapsedTime);
		SlowDown(fNewvy, fElapsedTime);
	}

	// zresetuj licznik czasu od ostatniej aktualizacji AI
	fTime2 = 0.0f;
}

void cDynamicCreature::AI_Default(float fElapsedTime, cDynamic* player)
{
	//jeœli obiekt jest poruszany przez skrypt to nie aktualizuj AI tylko przeka¿ dalej prêdkoœci
	if (bIsMovedByScript)
	{
		fNewvx = vx;
		fNewvy = vy;
		return;
	}

	//aktywuj tylko jeœli obiekt nie jest obecnie w powietrzu
	if (bIsKnockbacked)
		return;

	//spowalniaj obiekt
	SlowDown(fNewvx, fElapsedTime);
	SlowDown(fNewvy, fElapsedTime);

}

void cDynamicCreature::DrawSelf(float fOffsetX, float fOffsetY)
{
	//rysowanie animacji stworzenia dynamicznego

	if (nState == STATE_SLEEPING)
	{
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, (int)(48 * fHeight),
			(int)(fWidth * 16), (int)(fHeight * 16));
		return;
	}

	if (nState == STATE_DEAD || nState == STATE_UNCONSCIOUS)	// zw³oki i stwory nieprzytomne mog¹ (ale nie musz¹) mieæ podwójn¹ szerokoœæ, chocia¿ hitbox pozostaje taki sam
	{
		engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(fWidth * 16), (int)(48 * fHeight),
			(int)(fWidth * 32), (int)(fHeight * 16));
		return;
	}

	switch (nDirection)
	{
		case NORTH:
		{
			if (nState == STATE_STANDING)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, 0, 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_WALKING)
			{
				if(nFrame == 0)
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, (int)(fHeight * 16), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				else
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, (int)(fHeight * 32), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_MELEE_ATTACK)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, 0, (int)(64 * fHeight),
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}

			break;
		}
		case EAST:
		{
			if (nState == STATE_STANDING)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(16 * fWidth), 0, 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_WALKING)
			{
				if (nFrame == 0)
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(16 * fWidth), (int)(fHeight * 16), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				else
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(16 * fWidth), (int)(fHeight * 32), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_MELEE_ATTACK)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(16 * fWidth), (int)(64 * fHeight),
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}

			break;
		}
		case SOUTH:
		{
			if (nState == STATE_STANDING)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(32 * fWidth), 0, 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_WALKING)
			{
				if (nFrame == 0)
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(32 * fWidth), (int)(fHeight * 16), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				else
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(32 * fWidth), (int)(fHeight * 32), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_MELEE_ATTACK)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(32 * fWidth), (int)(64 * fHeight),
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}

			break;
		}
		case WEST:
		{
			if (nState == STATE_STANDING)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(48 * fWidth), 0, 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_WALKING)
			{
				if (nFrame == 0)
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(48 * fWidth), (int)(fHeight * 16), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				else
					engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(48 * fWidth), (int)(fHeight * 32), 
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}
			if (nState == STATE_MELEE_ATTACK)
			{
				engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(48 * fWidth), (int)(64 * fHeight),
					(int)(fWidth * 16), (int)(fHeight * 16));
				return;
			}

			break;
		}
	}
}

void cDynamicCreature::Update(float fElapsedTime, cDynamic* player)
{
	// jeœli HP osi¹gnie 0 to obiekt umiera
	if (fHP <= 0.0f)
	{
		nState = STATE_DEAD;
		// ustaw obiekt "na ziemii" i wy³¹cz z nim kolizjê dynamiczn¹
		nLayer = 1;
		bSolidVsDynamic = false;
	}

	if (nState == STATE_WALKING || nState == STATE_STANDING || nState == STATE_MELEE_ATTACK)
	{
		fTime2 += fElapsedTime; // aktualizacja czasu odœwie¿enia AI

		fTime3 -= fElapsedTime; // atkualizacje czasu odnowienia ataku podstawowego
		if (fTime3 < 0.0f) // jeœli czas odnowienia min¹³ to nie aktualizuj ju¿ wiêcej timera
			fTime3 = 0.0f;

		fTime4 -= fElapsedTime; // atkualizacje czasu odnowienia bezruchu po ataku podstawowym
		if (fTime4 < 0.0f) // jeœli czas odnowienia min¹³ to nie aktualizuj ju¿ wiêcej timera
			fTime4 = 0.0f;

		// aktualizacja AI - funkcja ta powinna zmieniaæ wartoœæ proponowanych prêdkoœci 
		// fNewvx i fNewvy tylko przy aktualizacji AI zgodnie z czasem odœwie¿ania
		UpdateAI(fElapsedTime, player);
		if (!bIsKnockbacked) // obiekt nie jest ju¿ w bezruchu po ataku wiêc nadaj mu prêdkoœci które mia³ po ostatnim odœwie¿eniu AI
		{
			// sprawdzenie, czy obiekt jest w trakcie czasu odnowienia po ataku podstawowym
			if (fTime4 == 0.0f)
			{
				vx = fNewvx;
				vy = fNewvy;
			}
			else
			{
				//jeœli obiekt jest w trakcie bezruchu po wykonaniu ataku podstawowego to zatrzymaj go w miejscu
				vx = 0.0f;
				vy = 0.0f;
			}
		}
	}

	if (nState == STATE_MELEE_ATTACK)
	{
		//jeœli obiekt by³ w trakcie animacji ataku, a timer bezruchu po wykonaniu ataku siê skoñczy³, to zmieñ animacjê
		if (fTime4 == 0.0f)
			if (!bWalkAnimationAlwaysOn)
				nState = STATE_STANDING;
			else
				nState = STATE_WALKING;
	}

	// jeœli obiekt nie jest obecnie w powietrzu to aktualizuj jego normalne poruszanie
	// WA¯NE: warto zauwa¿yæ ¿e w trakcie odrzutu nie jest aktualizowany status animacji obiektu
	if (!bIsKnockbacked)
	{
		//ograniczenie maskymalnej prêdkoœci i ustawienie jego skalarnej wartoœci prêdkoœci

		//jeœli obiekt jest poruszany przez skrypt to nie ograniczaj jego prêdkoœci
		if(bIsMovedByScript == false)
			ClampWalkingVel();
		else // jeœli jest poruszany przez skrypt to oblicz jedynie jego skalarn¹ wartoœæ prêdkoœci
			fScalarSpeed = sqrtf((vx * vx) + (vy * vy));


		if (nState == STATE_WALKING || nState == STATE_STANDING)
			// je¿eli obiekt jest martwy, wykonuje animacje ataku lub œpi, nie sprawdzaj czy jego ruch mo¿e wp³ywaæ na animacje
		{
			//obliczanie kierunku ka¿dej postaci dynamicznej
			if (fScalarSpeed != 0.0f) //sprawdŸ czy obiekty siê poruszaj¹
			{
				nState = STATE_WALKING; // stan animacji - obiekt w ruchu
				if (abs(vx) > abs(vy)) // obiekt porusza siê szybciej w osi X
				{
					if (vx > 0.3f)
						nDirection = EAST;
					else if (vx < -0.3f)
						nDirection = WEST;
				}
				else // obiekt porusza siê szybciej w osi Y
				{
					if (vy > 0.3f)
						nDirection = SOUTH;
					else if (vy < -0.3f)
						nDirection = NORTH;
				}

				//szybkoœæ aktualizaji animacji jest zale¿na od szybkoœci
				fAnimationInterval = ((0.6f / fWalkAnimationSpeedMultiplier) / fScalarSpeed);
			}
			else
			{
				if (!bWalkAnimationAlwaysOn)
					nState = STATE_STANDING; // stan animacji - obiekt stoi
				else
					nState = STATE_WALKING;
				fAnimationInterval = fAnimationDefaultInterval; // okres animacji - wartoœæ domyœlna
			}
		}
		else // obiekt jest martwy, wykonuje animacjê ataku lub œpi - ustaw okres animacji na wartoœæ podstawow¹
		{
			if (nState == STATE_DEAD || nState == STATE_UNCONSCIOUS || nState == STATE_SLEEPING) // obiekt jest martwy, œpi, lub jest nieprzytomny, wiêc po prostu zmniejszaj jego prêdkoœæ
			{
				SlowDown(vx, fElapsedTime, 1.6f);
				SlowDown(vy, fElapsedTime, 1.6f);
			}

			fAnimationInterval = fAnimationDefaultInterval;	 // okres animacji - wartoœæ domyœlna
		}
	}
	else // obiekt jest w powietrzu
	{
		fKnockbackTimer -= fElapsedTime;
		fAnimationInterval = fAnimationDefaultInterval; // okres animacji - wartoœæ domyœlna

		//jeœli obiekt jest obecnie odrzucany to zmniejsz jego prêdkoœc z ka¿d¹ aktualizajc¹ ruchu

		if (!bIsMovedByScript) // jeœli nie jest poruszany przez skrypt
		{
			//zanikanie prêdkoœci odrzutu
			vx /= ((4.0f * fKnockbackSpeedDeclineMultiplier * fElapsedTime) + 1.0f);
			vy /= ((4.0f * fKnockbackSpeedDeclineMultiplier * fElapsedTime) + 1.0f);
		}

		if (fKnockbackTimer <= 0.0f) // obiekt skoñczy³ byæ w powietrzu
		{
			bIsKnockbacked = false;
			fKnockbackTimer = 0.0f;

			//possible to be changed - patrz cDynamicCreature::Knockback()
			bInvincible = false;
			//bSolidVsDynamic = bDefaultSolidVsDynamic;
		}
	}

	//aktualizacja czasu od ostatniej aktualizacji klatki animacji
	fTime += fElapsedTime;

	// zaktualizuj klatkê jeœli od ostatniej aktualizacji minê³o wystarczaj¹co czasu
	// jeœli obiekt siê nie porusza to jest to wartoœæ sta³a, jeœli siê porusza
	// to zale¿y ona od jego szybkoœci
	if (fTime >= fAnimationInterval)
	{
		// aktualizuj animacjê tylko jeœli obiekt nie jest w powietrzu
		if (!bIsKnockbacked)
		{
			fTime = 0.0f;
			nFrame++;
			if (nFrame != 0 && nFrame != 1)
				nFrame = 0;
		}
	}
}

void cDynamicCreature::ClampWalkingVel()
{
	// oblicz maksymaln¹ wartoœæ prêdkoœci w osi X i Y
	fMaxAxisSpeed = fMaxWalkingVel / 1.4142f;

	//oblicz wartoœæ prêdkoœci obiektu
	fScalarSpeed = sqrtf((vx * vx) + (vy * vy));

	//je¿eli wartoœæ prêdkoœci jest za du¿a
	if (fScalarSpeed > fMaxWalkingVel)
	{
		if (vx > fMaxWalkingVel)	vx = fMaxWalkingVel;
		if (vx < -fMaxWalkingVel) vx = -fMaxWalkingVel;
		if (vy > fMaxWalkingVel)	vy = fMaxWalkingVel;
		if (vy < -fMaxWalkingVel) vy = -fMaxWalkingVel;

		// ruch po skosie
		if (abs(vx) > fMaxAxisSpeed && abs(vy) > fMaxAxisSpeed)
		{
			// ogranicz prêdkoœci w osiach X i Y jeœli konieczne
			if (vx > fMaxAxisSpeed)	vx = fMaxAxisSpeed;
			if (vx < -fMaxAxisSpeed) vx = -fMaxAxisSpeed;
			if (vy > fMaxAxisSpeed)	vy = fMaxAxisSpeed;
			if (vy < -fMaxAxisSpeed) vy = -fMaxAxisSpeed;
		}
	}

}

void cDynamicCreature::Knockback(float x, float y, float time)
{
	//sprawdŸ czy obiekt jest odporny na odrzut
	if (bIsResistantToKnockback)
		return;

	bIsKnockbacked = true;
	fKnockbackTimer = time;
	vx = x * fProneToKnockbackMultiplier;
	vy = y * fProneToKnockbackMultiplier;

	if(nState != STATE_DEAD && nState != STATE_UNCONSCIOUS && nState != STATE_SLEEPING)
		nState = STATE_WALKING; // w trakcie odrzutu ustaw animacjê na "bardziej dynamicznie wygl¹daj¹ce" chodzenie
								// status ten nie jest aktualizowany w trakcie odrzutu (patrz: cDynamicCreature::Update())

	// possible to be changed: obiekt w powietrzu jest chwilowo nieœmiertelny 
	bInvincible = true;
}

c3FrameAnimatedDynamic::c3FrameAnimatedDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, float _frametime) 
	: cDynamic(_engine, _name,_px, _py, spr)
{
	nFrame = 0;
	fFrameTime = _frametime;
	fWidth = 1.0f;
	fHeight = 1.0f;
}

c3FrameAnimatedDynamic::c3FrameAnimatedDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, float _frametime) 
	: cDynamic(_engine, _name, _px, _py, spr, _solidvssolid, _solidvsdynamic)
{
	nFrame = 0;
	fFrameTime = _frametime;
	fWidth = 1.0f;
	fHeight = 1.0f;
}

void c3FrameAnimatedDynamic::Update(float fElapsedTime, cDynamic* player)
{
	fTime += fElapsedTime;

	if (fTime >= 0.0f && fTime < fFrameTime)
		nFrame = 0;
	else if (fTime >= fFrameTime && fTime < 2 * fFrameTime)
		nFrame = 1;
	else if (fTime >= 2 * fFrameTime && fTime < 3 * fFrameTime)
		nFrame = 2;
	else if (fTime >= 3 * fFrameTime)
	{
		nFrame = 2;
		fTime = 0.0f;
	}
}

void c3FrameAnimatedDynamic::DrawSelf(float fOffsetX, float fOffsetY)
{
	engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(nFrame * fWidth * 16), 0,
		(int)(fWidth * 16), (int)(fHeight * 16));
}

cOpenable::cOpenable(cEngine* _engine, float _px, float _py, olc::Sprite* _sprite, std::string _name, bool _solidvssolid, bool _solidvsdynamic, float _frametime)
	: cDynamic(_engine, _name, _px, _py, _sprite, _solidvssolid, _solidvsdynamic)
{
	fWidth = 1.0f;
	fHeight = 1.0f;
	nFrame = 0;
	bOpen = false;
	bAnimOpening = false;
	bAnimClosing = false;
	fFrameTime = _frametime;
	bHasBeenYetOpened = false;
}

bool cOpenable::OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target)
{
	if (target->sName == "player")
	{
		if (nature == TALK)
		{
			if (bOpen && !bAnimClosing)
			{
				bAnimClosing = true;
				fTime = 0.0f;
			}
			else if (!bOpen && !bAnimOpening)
			{
				bAnimOpening = true;
				fTime = 0.0f;
			}
		}
	}
	return false;
}

void cOpenable::Update(float fElapsedTime, cDynamic* player)
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

void cOpenable::DrawSelf(float fOffsetX, float fOffsetY)
{
	engine->DrawPartialSprite((int)((px - fOffsetX) * engine->nTileWidth), (int)((py - fOffsetY) * engine->nTileHeight), sprite, (int)(nFrame * fWidth * 16), 0,
		(int)(fWidth * 16), (int)(fHeight * 16));
}