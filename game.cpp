#include "game.h"

Game* Game::instance = NULL;

Game::Game() {
	instance = this;
}

Game::~Game() {}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		this->window = SDL_CreateWindow("Latinary Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (!this->window)
		{
			std::cout << "SDL failed to create window" << std::endl;
			throw std::exception("SDL failed to create window");
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, 0);

		if (!this->renderer)
		{
			std::cout << "SDL failed to create renderer" << std::endl;
			throw std::exception("SDL failed to create renderer");
		}
	}
	else
	{
		std::cout << "SDL failed to initialize" << std::endl;
		throw std::exception("SDL failed to initialize");
	}
}

void Game::Run()
{
	if (this->running) return;

	this->running = true;

	this->Init();
}