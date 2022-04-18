#include "Editor.h"

int main()
{
	cMapEditor MapEditor;
	if (MapEditor.Construct(224 + UI_ADDITIONAL_PIXELS_RIGHT, 192, 4, 4))
		MapEditor.Start();

	return 0;
}