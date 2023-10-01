#include "ball.h"
#include "game.h"
#include "graphics.h"

Ball::Ball()
{
	// Set the ball's position to the center of the screen
	this->x = 50;
	this->y = 50;
	// Set the ball's velocity to 0
	this->xVel = 0;
	this->yVel = 0;
}

void Ball::Init()
{
	Game* game = Game::GetInstance();

	int x, y;
	SDL_GetWindowSize(Game::GetInstance()->GetWindow(), &x, &y);

	this->screenWidth = x;
	this->screenHeight = y;

	this->x = x / 2;
	this->y = y / 2;

	this->xVel = 0;
	this->yVel = 0;
}

void Ball::Update()
{
	if (this->xVel == 0 || this->yVel == 0)
	{
		this->xVel = this->speed * (rand() % 2 == 0 ? 1 : -1);
		this->yVel = this->speed * (rand() % 2 == 0 ? 1 : -1);
	}

	// Update the ball's position
	this->x += this->xVel;
	this->y += this->yVel;

	Game* game = Game::GetInstance();

	// Check if the ball is colliding with the top or bottom of the screen
	if (this->y < 0 || this->y > 600)
	{
		// If it is, reverse the y velocity
		this->yVel *= -1;
	}

	// Check if the ball is colliding with the left paddle
	if (this->x < 21 && this->y > game->left.y - 50 && this->y < game->left.y + 50)
	{
		// If it is, reverse the x velocity
		this->xVel *= -1;
	}

	// Check if the ball is colliding with the right paddle
	if (this->x > this->screenWidth - 19 && this->y > game->right.y - 50 && this->y < game->right.y + 50)
	{
		// If it is, reverse the x velocity
		this->xVel *= -1;
	}

	// Check if the ball is colliding with the left or right of the screen
	else if (this->x < 0)
	{
		std::cout << "gex\n";
		// If it is, reset the ball
		this->Reset();

		game->right.score++;
	}

	else if (this->x > screenWidth)
	{
		std::cout << "yex\n";
		this->Reset();

		game->left.score++;
	}
}

void Ball::Render()
{
	// Get the game's renderer
	SDL_Renderer* renderer = Game::GetInstance()->GetRenderer();

	// Create a rectangle to represent the ball
	SDL_Rect rect;
	rect.w = 15;
	rect.h = 15;
	rect.x = this->x - rect.w / 2;
	rect.y = this->y - rect.h / 2;

	// Set the renderer's draw color to white
	SDL_SetRenderDrawColor(renderer, 86, 19, 209, 255);
	// Draw the ball
	// SDL_RenderFillRect(renderer, &rect);
	Graphics::DrawCircle(renderer, this->x, this->y, 7);
}

void Ball::Reset()
{
	std::cout << "reset" << std::endl;

	// Reset the ball's position to the center of the screen
	this->x = this->screenWidth / 2;
	this->y = this->screenHeight / 2;
	// Reset the ball's velocity to 0
	this->xVel = 0;
	this->yVel = 0;
}