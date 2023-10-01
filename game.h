#pragma once

#include <SDL.h>
#include <iostream>

class Game
{
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
	void Init();

public:
	Game();
	~Game();
	static Game* GetInstance();
	SDL_Renderer* GetRenderer();
	void Run();
	void Quit();
};
