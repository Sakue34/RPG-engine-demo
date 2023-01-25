#include "Engine.h"
#include "Data.h"

bool cEngine::UpdateTitleMenu(float fElapsedTime)
{
	if (IsFocused())
	{
		if (GetKey(olc::Key::ENTER).bPressed || GetKey(olc::Key::SPACE).bPressed)
			bTitleStart = true;

		if(bTitleStart && fInitialDimmTime != 0.0f)
			if (GetKey(olc::Key::ENTER).bPressed || GetKey(olc::Key::SPACE).bPressed)
				fInitialDimmTime = fStartDimmingDuration;
	}

	if (bTitleStart)
	{
		if(fInitialDimmTime < fStartDimmingDuration)
			fInitialDimmTime += fElapsedTime;
		if (fInitialDimmTime <= fStartDimmingDuration)
			nDimm = (int8_t)((fInitialDimmTime / fStartDimmingDuration) * 255);
		else
			fInitialDimmTime = fStartDimmingDuration;
		fTitleScrollSpeedBG -= 4.0f * fElapsedTime;
		fTitleScrollOffsetForest -= 14.0f * fElapsedTime;
		if (fTitleScrollSpeedBG < 0.0f)	fTitleScrollSpeedBG = 0.0f;
		if (fTitleScrollOffsetForest < 0.0f) fTitleScrollOffsetForest = 0.0f;
		if (fInitialDimmTime == fStartDimmingDuration)
		{
			nDimm = (int8_t)255;
			GS_gamestate = GS_LOCAL_MAP;
		}
	}
	
	fTitleScrollOffsetBG += fElapsedTime * fTitleScrollSpeedBG;
	fTitleScrollOffsetForest += fElapsedTime * fTitleScrollSpeedForest;

	if (fTitleScrollOffsetBG > 384.0f)
		fTitleScrollOffsetBG = 0.0f;

	if (fTitleScrollOffsetForest > 160.0f)
		fTitleScrollOffsetForest = 0.0f;

	DrawPartialSprite(0, 0, cData::get().GetSprite("title background"), (int)fTitleScrollOffsetBG, 0, 224, 192);
	DrawPartialSprite(0, 0, cData::get().GetSprite("title forest"), (int)fTitleScrollOffsetForest, 0, 224, 192);

	Draw16x16Text("RPG DEMO", 16, 32, TXT_WHITE);
	DrawText("by Szymon Ciszewski", 16, 64, TXT_WHITE);	
	DrawText(cData::get().GetDialog("140")[0], ScreenWidth() - (21 + (cData::get().GetDialog("140")[0].length() * 6)), 64, TXT_WHITE);
	DrawText(cData::get().GetDialog("100")[0], 8, ScreenHeight() - 16, TXT_WHITE);

	// wygaszenie ekranu
	if (nDimm != 0)
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0, nDimm));

	return true;
}