#pragma once

#include <SDL.h>

enum BoardSide { LEFT, RIGHT };

class Board
{
private:
	int width, height;
	int speed = 5;

public:
	int y;
	BoardSide side;
	Board(int y, BoardSide side);
	Board(BoardSide side);
	Board();
	void Render();
	void Update();
	void OnResize(int width, int height);
	void Init();
	void Move(int y);
	long long score = 0;
};