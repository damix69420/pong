#pragma once

#include <SDL.h>
#include <iostream>
#include "board.h"
#include "ball.h"

class GameConfig
{
public:
	int TICKS_PER_SECOND = 64;
};

class Game
{
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
	void Init();
	void PollEvents();
	void Update();
	void Render();
	void Begin(); // Called when the window is created

public:
	Board left, right;
	Ball ball;
	void RunTick();
	Game();
	~Game();
	static Game* GetInstance();
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	void Run();
	void Quit();
	bool IsRunning();
	GameConfig config;
};