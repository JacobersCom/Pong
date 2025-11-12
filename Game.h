#pragma once
#include "SDL3/SDL.h"


class Game
{
public:

	Game();
	
	bool Init();

	void GameLoop();

	void ShutDown();

private:
	
	void ProcessInput();

	void UpdateGame();

	void GenerateOutPut();


	SDL_Window* window;
	
	bool isRunning;
};

