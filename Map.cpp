#include "Map.h"
#include "Dynamic.h"
#include "All_Dynamics.h"

cMap::cMap(cEngine* _engine)
{
	m_nIndices = nullptr;
	m_nIndices2 = nullptr;
	m_nIndices3 = nullptr;
	m_bSolids = nullptr;
	m_bIsAnimated = nullptr;
	sprite = nullptr;
	engine = _engine;
	bHasBeenEntered = false;

	nLevelWidth = 0;
	nLevelHeight = 0;
}

bool cMap::Create(std::wstring filepath, std::string name, olc::Sprite* _sprite)
{
	sName = name;
	sprite = _sprite;
	std::ifstream ifs;
	ifs.open(filepath, std::ios::in);
	if (ifs.good())
	{
		ifs >> nLevelWidth;
		ifs >> nLevelHeight;

		m_nIndices = new int[nLevelWidth * nLevelHeight];
		m_nIndices2 = new int[nLevelWidth * nLevelHeight];
		m_nIndices3 = new int[nLevelWidth * nLevelHeight];
		m_bSolids = new bool[nLevelWidth * nLevelHeight];
		m_bIsAnimated = new bool[nLevelWidth * nLevelHeight];
		for (int i = 0; i < (nLevelWidth * nLevelHeight); i++)
		{
			ifs >> m_nIndices[i];
			ifs >> m_nIndices2[i];
			ifs >> m_nIndices3[i];
			ifs >> m_bSolids[i];
			ifs >> m_bIsAnimated[i];
		}

		ifs.close();
	}
	else
		return false;

	return true;
}

void cMap::RemoveDynamic(unsigned x)
{
	delete vecDyn[x];
	vecDyn.erase(vecDyn.begin() + x);
}

cMap::~cMap()
{
	delete[] m_nIndices;
	delete[] m_nIndices2;
	delete[] m_nIndices3;
	delete[] m_bSolids;
	delete[] m_bIsAnimated;
}
