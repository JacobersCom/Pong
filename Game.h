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
	vector2 ballPos;
	
	bool isRunning;
};

