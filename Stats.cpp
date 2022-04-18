#include "Stats.h"
#include "All_Items.h"

cCreatureStats::cCreatureStats(float _dmg, float _dmgFluct, float _knockback, float _knockbacktimer, float _meleerange, float _meleeattackspeed, float _meleeattackimmobilitycooldown)
{
	fDmg = _dmg;
	fDmgFluct = _dmgFluct;
	fKnockbackMultiplier = _knockback;
	fKnockbackTimer = _knockbacktimer;
	fMeleeRange = _meleerange;
	fMeleeAttackCooldown = _meleeattackspeed;
	fMeleeAttackImmobilityCooldown = _meleeattackimmobilitycooldown;
}

cCreatureStats::cCreatureStats(float _dmg, float _dmgFluct)
{
	fDmg = _dmg;
	fDmgFluct = _dmgFluct;
	fKnockbackMultiplier = 1.0f;
	fKnockbackTimer = 0.3f;
	fMeleeRange = 1.1f;
	fMeleeAttackCooldown = 1.0f;
	fMeleeAttackImmobilityCooldown = 0.0f;
}

cCreatureStats::cCreatureStats()
{
	fDmg = 0.0f;
	fDmgFluct = 0.0f;
	fKnockbackMultiplier = 1.0f;
	fKnockbackTimer = 0.3f;
	fMeleeRange = 1.1f;
	fMeleeAttackCooldown = 1.0f;
	fMeleeAttackImmobilityCooldown = 0.0f;
}

cPlayerData::cPlayerData()
{
	fStaminaTimer = 0.0f;
	currentWeapon = nullptr;

	// modyfikowalne:
	fMaxStamina = 10.0f;
	fStamina = 10.0f;
	fStaminaRegenDelay = 2.0f;
	fStaminaDashCost = 5.0f;
	fStaminaRegenPerSecond = 5.0f;
	fDashVelocityMultiplier = 1.0f;
	fDashExecutionTime = 0.5f;
}
