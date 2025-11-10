#pragma once
#include "SDL3/SDL.h"

class Game
{
public:

	void Init();

	void Start();

	void Stop();

private:

	SDL_Window* window;
	bool isRunning;
	SDL_Event event;

};

