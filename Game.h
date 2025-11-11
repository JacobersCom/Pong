#pragma once
#include "SDL3/SDL.h"

class Game
{
public:

	Game(SDL_Window* whandler, bool running, SDL_Event eventHandler): window(whandler), isRunning(running), event(eventHandler){}

	int Init();

	void Start_Game();

	void Stop_Game();

private:

	SDL_Window* window;
	bool isRunning;
	SDL_Event event;

};

