#pragma once

#include <fstream>
#include <vector>
#include "Data.h"

namespace olc
{ 
	class Sprite;
}

class cEngine;
class cDynamic;

class cMap
{
protected:

	int* m_nIndices;
	int* m_nIndices2;
	int* m_nIndices3;
	bool* m_bSolids;
	bool* m_bIsAnimated;

	bool WithinBoundaries(int x, int y)
	{
		if (x < 0 || y < 0 || x > nLevelWidth - 1 || y > nLevelHeight - 1)
			return false;

		return true;
	}

public:
	std::string sName;
	int nLevelWidth;
	int nLevelHeight;

	bool bHasBeenEntered;

	std::vector<cDynamic*> vecDyn;

	void RemoveDynamic(unsigned x);

	olc::Sprite* sprite;

	int GetIndex(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_nIndices[y * nLevelWidth + x];
		else
			return 0;
	};

	int GetIndex2(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_nIndices2[y * nLevelWidth + x];
		else
			return 0;
	};

	int GetIndex3(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_nIndices3[y * nLevelWidth + x];
		else
			return 0;
	};

	bool GetSolid(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_bSolids[y * nLevelWidth + x];
		else
			return true;
	};

	bool GetIsAnimated(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_bIsAnimated[y * nLevelWidth + x];
		else
			return false;
	}

	bool Create(std::wstring filepath, std::string name, olc::Sprite* sprite);

	virtual void PopulateDynamics()
	{
		return;
	}

	virtual void FirstEnter() { bHasBeenEntered = true; }

	cEngine* engine;

	cMap(cEngine* _engine);

	~cMap();
};

