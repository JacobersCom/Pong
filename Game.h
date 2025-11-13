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

	SDL_Window* window;
	SDL_Renderer* renderer;
	
	vector2 paddlePos;
	float paddleDir;

	vector2 ballPos;
	
	Uint64 ticksCount;
	
	bool isRunning;
};

