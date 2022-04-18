#include "Engine.h"

/// RPG Tech Demo by Sakue, 16.08.2019
/// Development time: ~ 2 months
/// Using numerous CC assets credited
/// in separete credits.txt file.

/// Using OLC Pixel Game Engine
/// All credits goes to javidx9
/// Gtihub:
/// https://github.com/OneLoneCoder
/// WWW:
/// https://onelonecoder.com/

int main()
{
	cEngine engine;
	//if (engine.Construct(256, 240, 4, 4))
	if (engine.Construct(224, 192, 5, 5))
		engine.Start();

	return 0;
}