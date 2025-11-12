#include "Game.h"
#include "Defines.h"

Game::Game() {

	window = nullptr;
	isRunning = true;
}

bool Game::Init() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR: Failed to init SDL video %s\n", SDL_GetError());
		return false;
	};

	window = SDL_CreateWindow("Pong", screenW, screenH, 0);

	if (!window) {
		SDL_Log("ERROR: Failed to create window %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
	{
		SDL_Log("ERROR: Failed to init renderer %s\n", SDL_GetError());
		return false;
	}

	return true;

}

void Game::GameLoop()
{

	while (isRunning) {

		ProcessInput();
		//UpdateGame();
		GenerateOutPut();
	}
}

void Game::ShutDown()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) 
		{
			case SDL_EVENT_QUIT:
			{
				isRunning = false;
				break;

			}
			case SDL_EVENT_KEY_DOWN:
			{
				const bool* keyState = SDL_GetKeyboardState(NULL);

				if (keyState[SDL_SCANCODE_ESCAPE])
				{
					isRunning = false;
				}
				
			}
			

		}
	}
}

void Game::GenerateOutPut()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//Clears backbuffer for the current draw color
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
