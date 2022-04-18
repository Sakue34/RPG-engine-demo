#include "Map.h"
#include <fstream>

void cMap::New(int width, int height, int _1, int _2, int _3, bool solid, bool animated)
{
	delete[] m_nIndices;
	delete[] m_nIndices2;
	delete[] m_nIndices3;
	delete[] m_bSolids;
	delete[] m_bIsAnimated;

	nLevelWidth = width;
	nLevelHeight = height;

	m_nIndices = new int[nLevelWidth * nLevelHeight];
	m_nIndices2 = new int[nLevelWidth * nLevelHeight];
	m_nIndices3 = new int[nLevelWidth * nLevelHeight];
	m_bSolids = new bool[nLevelWidth * nLevelHeight];
	m_bIsAnimated = new bool[nLevelWidth * nLevelHeight];

	for (int y = 0; y < nLevelHeight; y++)
	{
		for (int x = 0; x < nLevelWidth; x++)
		{
			int index = y * nLevelWidth + x;
			m_nIndices[index] = _1;
			m_nIndices2[index] = _2;
			m_nIndices3[index] = _3;
			m_bSolids[index] = solid;
			m_bIsAnimated[index] = animated;
		}
	}

}

cMap::cMap()
{
	m_nIndices = nullptr;
	m_nIndices2 = nullptr;
	m_nIndices3 = nullptr;
	m_bSolids = nullptr;
	m_bIsAnimated = nullptr;
	nLevelWidth = 0;
	nLevelHeight = 0;
};

cMap::~cMap()
{
	delete[] m_nIndices;
	delete[] m_nIndices2;
	delete[] m_nIndices3;
	delete[] m_bSolids;
	delete[] m_bIsAnimated;
}

bool cMap::Load(std::wstring filepath)
{
	std::ifstream ifs;
	ifs.open(filepath, std::ios::in);

	if (ifs.good())
	{
		delete[] m_nIndices;
		delete[] m_nIndices2;
		delete[] m_nIndices3;
		delete[] m_bSolids;
		delete[] m_bIsAnimated;

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

bool cMap::Save(std::wstring filepath)
{
	std::ofstream ofs;
	ofs.open(filepath, std::ios::out);

	if (ofs.good())
	{
		ofs << nLevelWidth;
		ofs << " ";
		ofs << nLevelHeight;

		for (int i = 0; i < (nLevelWidth * nLevelHeight); i++)
		{
			if(i % nLevelWidth == 0)
				ofs << std::endl;

			ofs << m_nIndices[i];
			ofs << " ";
			ofs << m_nIndices2[i];
			ofs << " ";
			ofs << m_nIndices3[i];
			ofs << " ";
			ofs << m_bSolids[i];
			ofs << " ";
			ofs << m_bIsAnimated[i];
			ofs << " ";
		}

		ofs.close();
	}
	else
		return false;

	return true;

}