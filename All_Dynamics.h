#pragma once

#include "Dynamic.h"
#include <vector>

class cScript;

class cPlayerMelee : public cDynamic
{
public:
	cPlayerMelee(cEngine* _engine, float _px, float _py);

	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	void DrawSelf(float fOffsetX, float fOffsetY);
};

class cEmoteBubble : public cDynamic
{
public:
	enum EMOTE_BUBBLE
	{
		EMOTE_BUBBLE_LOVE,
		EMOTE_BUBBLE_SILENCE,
		EMOTE_BUBBLE_ALERT,
		EMOTE_BUBBLE_CONFUSION,
		EMOTE_BUBBLE_E
	};
private:
	short nFrame;
	cDynamic* parent;
	EMOTE_BUBBLE nEmote;
	bool bLoopAnimation;
public:
	cEmoteBubble(cEngine* engine, cDynamic* _parent, EMOTE_BUBBLE _type, bool _loopanimation, float _lifetime);
	void Update(float fElapsedTime, cDynamic* player = nullptr);
	void DrawSelf(float fOffsetX, float fOffsetY);
};

class cTeleporter : public cDynamic
{
public:
	std::string sTargetMap;
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	float fToX;
	float fToY;

	cTeleporter(cEngine* _engine, float _px, float _py, std::string map, float _x, float _y);
};


class cMap_Intro1_ScriptActivator1 : public cDynamic
{
private:
	bool bActivated;
public:
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	cMap_Intro1_ScriptActivator1(cEngine* _engine, float _px, float _py);
};

class cMap_Intro1_ScriptActivator2 : public cDynamic
{
private:
	bool bActivated;
public:
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	cMap_Intro1_ScriptActivator2(cEngine* _engine, float _px, float _py);
};

class cMap_Intro6_ScriptActivator1 : public cDynamic
{
private:
	bool bActivated;
public:
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	cMap_Intro6_ScriptActivator1(cEngine* _engine, float _px, float _py);
};

class cSpikes : public cDynamic
{
private:
	int nFrame;
public:
	bool bDanger;
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr);
	void DrawSelf(float fOffsetX, float fOffsetY);
	cSpikes(cEngine* _engine, float _px, float _py);
};

class cTorch : public c3FrameAnimatedDynamic
{
public:
	cTorch(cEngine* _engine, float _px, float _py);
};

class cIronDoor : public cOpenable
{
public:
	cIronDoor(cEngine* _engine, float _px, float _py);
	cIronDoor(cEngine* _engine, float _px, float _py, std::string _name);
	void Update(float fElapsedTime, cDynamic* player = nullptr);
};

class cLockedIronDoor : public cOpenable
{
public:
	cLockedIronDoor(cEngine* _engine, float _px, float _py);
	cLockedIronDoor(cEngine* _engine, float _px, float _py, std::string _name);
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	void Update(float fElapsedTime, cDynamic* player = nullptr);
};

class cChest : public cOpenable
{
private:
	std::vector<cScript*> vecScripts;
public:
	cChest(cEngine* _engine, float _px, float _py);
	cChest(cEngine* _engine, float _px, float _py, std::vector<cScript*> _scripts);
	cChest(cEngine* _engine, float _px, float _py, std::vector<cScript*> _scripts, std::string _name);
	void FirstOpen() override;
};

class cSkeleton : public cDynamicCreature
{
private:
	void UpdateAI(float fElapsedTime, cDynamic* player);
public:
	cSkeleton(cEngine* engine, float _px, float _py);
};

class cBat : public cDynamicCreature
{
private:
	void UpdateAI(float fElapsedTime, cDynamic* player);
public:
	cBat(cEngine* engine, float _px, float _py);
};

class cSignpost : public cDynamic
{
private:
	std::vector<std::string> vecText;
public:
	cSignpost(cEngine* engine, float _px, float _py, std::vector<std::string> _vecText);
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
};

class cFemale : public cDynamicCreature
{
private:
	void UpdateAI(float fElapsedTime, cDynamic* player);
	std::vector<std::string> vecText;
	bool bHasSthToSay;
public:
	cFemale(cEngine* engine, float _px, float _py);
	cFemale(cEngine* engine, float _px, float _py, std::vector<std::string> _vecText);
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
};

class cSlime : public cDynamicCreature
{
private:
	void UpdateAI(float fElapsedTime, cDynamic* player);
public:
	cSlime(cEngine* engine, float _px, float _py);
};

class cStairwayDown : public cDynamic
{
private:
	std::string sTargetMap;
	float fToX;
	float fToY;
public:
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	cStairwayDown(cEngine* engine, float _px, float _py, std::string map, float _x, float _y);
};

class cStairwayUp : public cDynamic
{
private:
	std::string sTargetMap;
	float fToX;
	float fToY;
public:
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	cStairwayUp(cEngine* engine, float _px, float _py, std::string map, float _x, float _y);
};