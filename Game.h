#pragma once
#include "SDL3/SDL.h"
#include "Defines.h"



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

	const SDL_FRect wall
	{
		0,
		250,
		thickeness,
		40,
	};

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
};

