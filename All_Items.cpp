#include "All_Items.h"
#include "Data.h"

cBasic_Sword::cBasic_Sword()
{
	sName = "Basic sword";
	sDescription = "Simple iron sword";
	sprite = cData::get().GetItemSprite("Basic sword");
	bool KeyItem = false;
	bool bEquipable = true;
	fDmg = 2.0f;
	fDmgFluct = 1.0f;
	fKnockbackMultiplier = 1.0f;
	fKnockbackTimer = 0.3f;
	fMeleeRange = 1.1f;
	fMeleeAttackCooldown = 1.0f;
	fMeleeAttackImmobilityCooldown = 0.3f;
}

cSteel_Sword::cSteel_Sword()
{
	sName = "Steel sword";
	sDescription = "Fancy, steel sword";
	sprite = cData::get().GetItemSprite("Steel sword");
	bool KeyItem = false;
	bool bEquipable = true;
	fDmg = 3.0f;
	fDmgFluct = 1.5f;
	fKnockbackMultiplier = 1.2f;
	fKnockbackTimer = 0.3f;
	fMeleeRange = 1.1f;
	fMeleeAttackCooldown = 0.8f;
	fMeleeAttackImmobilityCooldown = 0.35f;
}