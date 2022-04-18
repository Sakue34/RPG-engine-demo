#pragma once

#include <string>
#include <map>
#include <vector>

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
	//std::string sName;
	int nLevelWidth;
	int nLevelHeight;

	//std::vector<cDynamic*> vecDyn;

	//void RemoveDynamic(unsigned x);

	//olc::Sprite* sprite;

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
			return false;
	};

	bool GetIsAnimated(int x, int y)
	{
		if (WithinBoundaries(x, y))
			return m_bIsAnimated[y * nLevelWidth + x];
		else
			return false;
	}

	bool SetIndex(int x, int y, int with)
	{
		if (WithinBoundaries(x, y))
			m_nIndices[y * nLevelWidth + x] = with;
		else
			return false;

		return true;
	};

	bool SetIndex2(int x, int y, int with)
	{
		if (WithinBoundaries(x, y))
			m_nIndices2[y * nLevelWidth + x] = with;
		else
			return false;

		return true;
	};

	bool SetIndex3(int x, int y, int with)
	{
		if (WithinBoundaries(x, y))
			m_nIndices3[y * nLevelWidth + x] = with;
		else
			return false;

		return true;
	};

	bool SetSolid(int x, int y, bool with)
	{
		if (WithinBoundaries(x, y))
			m_bSolids[y * nLevelWidth + x] = with;
		else
			return false;

		return true;
	};

	bool SetAnimated(int x, int y, bool with)
	{
		if (WithinBoundaries(x, y))
			m_bIsAnimated[y * nLevelWidth + x] = with;
		else
			return false;

		return true;
	};

	void New(int width, int height, int _1, int _2, int _3, bool _4, bool _5);

	//bool Create(std::wstring filepath, std::string name, olc::Sprite* sprite);

	//virtual void PopulateDynamics()
	//{
	//	return;
	//}

	//cEngine* engine;

	//cMap(cEngine* _engine);

	cMap();
	
	~cMap();

	bool Load(std::wstring filepath);
	bool Save(std::wstring filepath);
};