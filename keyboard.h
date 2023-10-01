#pragma once

#include <SDL.h>
#include <map>

class Keyboard
{
public:
	static std::map<long long, bool> keys;

	Keyboard();

	static bool IsKeyDown(int key);
	static bool IsKeyUp(int key);
};