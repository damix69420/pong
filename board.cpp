#include "board.h"
#include "game.h"
#include "keyboard.h"
#include <math.h>

Board::Board(int y, BoardSide side)
{
	this->y = y;
	this->side = side;
}

Board::Board(BoardSide side)
{
	Game* game = Game::GetInstance();
	SDL_Window* window = game->GetWindow();

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	this->width = w;
	this->height = h;

	Board::Board(std::floor(w / 2), side);
}

Board::Board()
{
	Board::Board(0, LEFT);
}

void Board::Init()
{
	Game* game = Game::GetInstance();
	SDL_Window* window = game->GetWindow();

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	this->width = w;
	this->height = h;
}

void Board::Render()
{
	Game* game = Game::GetInstance();
	SDL_Renderer* renderer = game->GetRenderer();

	int w, h;
	SDL_GetWindowSize(game->GetWindow(), &w, &h);

	SDL_Rect rect;
	rect.w = 10;
	rect.h = 100;
	rect.x = this->side == LEFT ? 0 : w - rect.w;
	rect.y = this->y - rect.h / 2;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Board::Move(int y)
{
	if (y - 50 < 0) this->y = 50;
	else if (y + 50 > this->height) this->y = this->height - 50;
	else this->y = y;
}

void Board::Update()
{
	if (this->side == LEFT)
	{
		if (Keyboard::IsKeyDown(SDLK_w)) this->Move(y - this->speed);
		else if (Keyboard::IsKeyDown(SDLK_s)) this->Move(y + this->speed);
	}
	else
	{
		if (Keyboard::IsKeyDown(SDLK_UP)) this->Move(y - this->speed);
		else if (Keyboard::IsKeyDown(SDLK_DOWN)) this->Move(y + this->speed);
	}
}

void Board::OnResize(int w, int h)
{
	std::cout << "resize" << std::endl;

	this->width = w;
	this->height = h;
}