#include "Game.h"

int Game::Init() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR:Failed to init SDL: %s\n", SDL_GetError);
		return 1;
	};

}

void Game::Start_Game()
{
	window = SDL_CreateWindow("Pong", 600, 400, NULL);

	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR:Failed to create window: %s\n", SDL_GetError);
	}

	while (isRunning) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
				break;
			}
		}
	}
}

void Game::Stop_Game()
{
	if (!isRunning) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}
