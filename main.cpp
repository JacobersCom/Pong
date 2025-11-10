#include "SDL3/SDL.h"

//Create a rendering service and a game loop. Make then in singletons
//Then Create a defines file which will hold things like types and #defines
//Then go into create a controller service.
//Everything should be a service.

int main() {

	bool isRunning = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR:Failed to init SDL: %s\n", SDL_GetError);
		return 1;
	};

	int result = SDL_CreateWindowAndRenderer("Pong", 400, 600, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0F, 0xF0, 0xFF);
	SDL_RenderLine(renderer, 0,0, 400, 600);
	SDL_RenderPresent(renderer);

	while (isRunning) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
				break;;
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();


	return 0;
}