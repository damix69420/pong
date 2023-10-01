#include "color.h"

Color::Color(int r, int g, int b, int a = 255)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Color::Color()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}