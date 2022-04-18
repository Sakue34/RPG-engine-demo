#pragma once
#include <string>
#include "Dynamic.h"

class cItem
{
public:
	std::string sName;
	std::string sDescription;
	olc::Sprite* sprite;
	bool KeyItem = false;
	bool bEquipable = false;

	virtual bool OnUse(cDynamic* object) { return false; }
	virtual bool OnInteract(cDynamic* object) { return false; }

	cItem(std::string name);
	cItem();
};

class cWeapon : public cCreatureStats, public cItem
{
public:
	cWeapon();
};