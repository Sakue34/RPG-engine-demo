#pragma once
#include <string>
#include <vector>

class cItem;
class cWeapon;

class cCreatureStats 
{
private:

public:
	// wahanie obra¿eñ: wartoœæ od zera do dowolnej liczby
	// ostateczne obra¿enia bêd¹ mia³y wartoœæ z zakresu od
	// fDmg do fDmg + fDmgFluct
	////////////////////////////////////////////////////////////////////
	float fDmg; // obra¿enia minimalne (domyœlnie 0.0f, dla cDynamicCreature 1.0f)
	float fDmgFluct; // maksymalne obra¿enia bonusowe, wahanie obra¿eñ (domyœlnie 0.0f, dla cDynamicCreature 1.0f)
	float fKnockbackMultiplier; // mno¿nik prêdkoœci odrzutu z jakim odleci cel (domyœlnie 1.0f)
	float fMeleeRange; // zasiêg ataku (uwzglêdniæ rozmiar stwora!) (domyœlnie 1.1f dla stwora ~1.0x1.0)
	float fMeleeAttackCooldown;	// cooldown ataku wrêcz (domyœlnie 1.0f)
	float fMeleeAttackImmobilityCooldown;	// cooldown bezruchu po ataku wrêcz (domyœlnie 0.0f)
	float fKnockbackTimer;	// czas jaki spêdzi w powietrzu cel po zostaniu zaatakowanym wrêcz (domyœlnie 0.3f)
	////////////////////////////////////////////////////////////////////

	cCreatureStats(float _dmg, float _dmgFluct, float _knockback, float _knockbacktimer, float _meleerange, float _meleeattackspeed, float _meleeattackimmobilitycooldown);
	cCreatureStats(float _dmg, float _dmgFluct);
	cCreatureStats();
};

class cPlayerData
{
public:
	float fStamina; // obecna wytrzyma³oœæ
	float fMaxStamina; // maksymalna wytrzyma³oœæ
	float fStaminaTimer; // timer czasu po którym zacznie regenerowaæ siê wytrzyma³oœæ 
	float fStaminaRegenDelay; // czas po którym zacznie regenerowaæ siê stamina
	float fStaminaDashCost; // koszt punktów wytrzyma³oœci potrzebny do wykonania doskoku
	float fStaminaRegenPerSecond; // regeneracja punktów wytrzyma³oœci w ci¹gu jednej sekundy 
	float fDashVelocityMultiplier; // mno¿nik prêdkoœci doskoków
	float fDashExecutionTime; // jak d³ugo trwa doskok gracza ( wa¿ne:  1. gracz jest nieœmiertelny w trakcie doskoku 2. im krótszy czas tym krótszy doskok )
public:
	cWeapon* currentWeapon = nullptr;

public:
	cPlayerData();
};