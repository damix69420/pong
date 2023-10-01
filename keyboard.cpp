#include "keyboard.h"
#include <SDL.h>
#include <iostream>
#include <map>

std::map<long long, bool> Keyboard::keys;

Keyboard::Keyboard() {}

bool Keyboard::IsKeyDown(int key)
{
	return keys[key];
}

bool Keyboard::IsKeyUp(int key)
{
	return !keys[key];
}