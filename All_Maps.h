#pragma once

#include "Map.h"

class cMap1 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap1(cEngine* _engine);

};

class cMap2 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap2(cEngine* _engine);

};

class cMap_Test : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Test(cEngine* _engine);
};

class cMap_Intro1 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Intro1(cEngine* _engine);
};

class cMap_Intro2 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Intro2(cEngine* _engine);
};

class cMap_Intro3 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Intro3(cEngine* _engine);
};

class cMap_Intro4 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Intro4(cEngine* _engine);
};

class cMap_Intro5 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Intro5(cEngine* _engine);
};

class cMap_Intro6 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Intro6(cEngine* _engine);
};

class cMap_Plains1 : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Plains1(cEngine* _engine);
};

class cMap_Dungeon1 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Dungeon1(cEngine* _engine);
};

class cMap_Village1 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Village1(cEngine* _engine);
};

class cMap_Plains2 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Plains2(cEngine* _engine);
};

class cMap_Cave1 : public cMap
{
public:
	void PopulateDynamics() override;
	cMap_Cave1(cEngine* _engine);
};

class cMap_Cep : public cMap
{
public:
	void PopulateDynamics() override;
	void FirstEnter() override;
	cMap_Cep(cEngine* _engine);
};