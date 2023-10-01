#pragma once

class Ball
{
private:
	int x, y;
	int xVel, yVel;
	int speed = 5;
	int screenWidth, screenHeight;

public:
	Ball();
	void Init();
	void Update();
	void Render();
	void Reset();
};