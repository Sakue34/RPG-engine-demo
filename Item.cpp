#include "Item.h"

cItem::cItem()
{
	sprite = nullptr;
}

cItem::cItem(std::string name)
{
	sName = name;
}

cWeapon::cWeapon()
{
	fDmg = 0.0f;
	fDmgFluct = 0.0f;
	fKnockbackMultiplier = 1.0f;
	fKnockbackTimer = 0.3f;
	fMeleeRange = 1.1f;
	fMeleeAttackCooldown = 1.0f;
	fMeleeAttackImmobilityCooldown = 0.3f;
}
