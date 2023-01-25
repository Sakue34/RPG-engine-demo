#pragma once
#include <string>
#include <vector>

class cItem;
class cWeapon;

class cCreatureStats 
{
private:

public:
	// wahanie obra�e�: warto�� od zera do dowolnej liczby
	// ostateczne obra�enia b�d� mia�y warto�� z zakresu od
	// fDmg do fDmg + fDmgFluct
	////////////////////////////////////////////////////////////////////
	float fDmg; // obra�enia minimalne (domy�lnie 0.0f, dla cDynamicCreature 1.0f)
	float fDmgFluct; // maksymalne obra�enia bonusowe, wahanie obra�e� (domy�lnie 0.0f, dla cDynamicCreature 1.0f)
	float fKnockbackMultiplier; // mno�nik pr�dko�ci odrzutu z jakim odleci cel (domy�lnie 1.0f)
	float fMeleeRange; // zasi�g ataku (uwzgl�dni� rozmiar stwora!) (domy�lnie 1.1f dla stwora ~1.0x1.0)
	float fMeleeAttackCooldown;	// cooldown ataku wr�cz (domy�lnie 1.0f)
	float fMeleeAttackImmobilityCooldown;	// cooldown bezruchu po ataku wr�cz (domy�lnie 0.0f)
	float fKnockbackTimer;	// czas jaki sp�dzi w powietrzu cel po zostaniu zaatakowanym wr�cz (domy�lnie 0.3f)
	////////////////////////////////////////////////////////////////////

	cCreatureStats(float _dmg, float _dmgFluct, float _knockback, float _knockbacktimer, float _meleerange, float _meleeattackspeed, float _meleeattackimmobilitycooldown);
	cCreatureStats(float _dmg, float _dmgFluct);
	cCreatureStats();
};

class cPlayerData
{
public:
	float fStamina; // obecna wytrzyma�o��
	float fMaxStamina; // maksymalna wytrzyma�o��
	float fStaminaTimer; // timer czasu po kt�rym zacznie regenerowa� si� wytrzyma�o�� 
	float fStaminaRegenDelay; // czas po kt�rym zacznie regenerowa� si� stamina
	float fStaminaDashCost; // koszt punkt�w wytrzyma�o�ci potrzebny do wykonania doskoku
	float fStaminaRegenPerSecond; // regeneracja punkt�w wytrzyma�o�ci w ci�gu jednej sekundy 
	float fDashVelocityMultiplier; // mno�nik pr�dko�ci doskok�w
	float fDashExecutionTime; // jak d�ugo trwa doskok gracza ( wa�ne:  1. gracz jest nie�miertelny w trakcie doskoku 2. im kr�tszy czas tym kr�tszy doskok )
public:
	cWeapon* currentWeapon = nullptr;

public:
	cPlayerData();
};