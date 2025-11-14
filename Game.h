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

	vector2 player1Pos;
	vector2 player2Pos;

	float player1Dir;
	float player2Dir;


	vector2 ballPos;
	vector2 ballVel;

	Uint64 ticksCount;

	bool GameStart;
	bool isRunning;
};

