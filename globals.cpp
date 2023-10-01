#include "globals.h"
#include "color.h"

Color Globals::LATINARY_COLOR;

void Globals::Init()
{
	Globals::LATINARY_COLOR = Color(86, 19, 209);
}

Globals::Globals()
{
}