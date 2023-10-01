#define SDL_MAIN_HANDLED

#include <iostream>
#include <Windows.h>
#include <SDL.h>

#include "globals.h"
#include "game.h"

#undef main

int main(int argc, char* argv[])
{
	Game game = Game();
	game.Run();

	return 0;
}