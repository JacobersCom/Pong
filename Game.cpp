#include "Game.h"
#include "Defines.h"

Game::Game() {

	window = nullptr;
	isRunning = true;
}

bool Game::Init() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR:Failed to init SDL video: %s\n", SDL_GetError);
		return false;
	};

	window = SDL_CreateWindow("Pong", screenW, screenH, 0);

	if (window == nullptr) {
		SDL_Log("ERROR:Failed to create window: %s\n", SDL_GetError);
		return false;
	}

	return true;

}

void Game::GameLoop()
{

	while (isRunning) {

		/*ProcessInput();
		UpdateGame();
		GenerateOutPut();*/
	}
}

void Game::ShutDown()
{
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}
