#include "game.h"
#include "keyboard.h"
#include <thread>

Game* Game::instance = NULL;

Game::Game()
{
	instance = this;
	this->config = GameConfig();
}

Game::~Game() {}

Game* Game::GetInstance()
{
	return instance;
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		this->window = SDL_CreateWindow("Latinary Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

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

		std::cout << "SDL successfully initialized" << std::endl;

		this->Begin();
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

	try
	{
		this->Init();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		this->running = false;
	}
}

void Game::Quit()
{
	this->running = false;

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();

	std::cout << "Game quit" << std::endl;
}

void Game::Update()
{
	this->PollEvents();
	this->Render();
}

void Game::PollEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->Quit();
			break;
		case SDL_KEYDOWN:
			Keyboard::keys[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			Keyboard::keys[event.key.keysym.sym] = false;
			break;
		case SDL_WINDOWEVENT_RESIZED:
			std::cout << "resize" << std::endl;
			this->left.OnResize(event.window.data1, event.window.data2);
			this->right.OnResize(event.window.data1, event.window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			this->left.OnResize(event.window.data1, event.window.data2);
			this->right.OnResize(event.window.data1, event.window.data2);
			break;
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	this->left.Render();
	this->right.Render();

	this->ball.Render();

	SDL_RenderPresent(this->renderer);
}

void Game::RunTick()
{
	this->left.Update();
	this->right.Update();
	this->ball.Update();
}

void TickThread()
{
	Game* game = Game::GetInstance();

	int tps = game->config.TICKS_PER_SECOND;

	while (game->IsRunning())
	{
		game->RunTick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / tps));
	}
}

bool Game::IsRunning()
{
	return this->running;
}

void Game::Begin()
{
	this->running = true;

	this->left = Board(50, LEFT);
	this->right = Board(50, RIGHT);
	this->ball = Ball();

	this->left.Init();
	this->right.Init();

	this->ball.Init();

	// Create thread for ticks
	std::thread tickThread(TickThread);
	tickThread.detach();

	while (this->running)
	{
		this->Update();
	}
}

SDL_Renderer* Game::GetRenderer()
{
	return this->renderer;
}

SDL_Window* Game::GetWindow()
{
	return this->window;
}