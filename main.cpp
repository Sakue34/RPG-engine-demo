#include "Engine.h"

/// RPG Framework Demo
/// Szymon Ciszewski 2022
/// --------------------------------
/// Using OLC Pixel Game Engine
/// All credits go to javidx9
/// Gtihub:
/// https://github.com/OneLoneCoder
/// WWW:
/// https://onelonecoder.com/
/// --------------------------------

int main()
{
	cEngine engine;
	if (engine.Construct(224, 192, 5, 5))
		engine.Start();

	return 0;
}