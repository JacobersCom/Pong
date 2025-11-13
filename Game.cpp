#include "Game.h"

Game::Game() {

	window = nullptr;
	renderer = nullptr;
	isRunning = true;

	paddlePos.x = 10;
	paddlePos.y = 225;
	paddleDir = 0.0f;

	ballPos.x = 250;
	ballPos.y = 250;

	ticksCount = 0;
}

bool Game::Init() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR: Failed to init SDL video %s\n", SDL_GetError());
		return false;
	};

	window = SDL_CreateWindow("Pong", screenW, screenH, SDL_WINDOW_RESIZABLE);

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
		UpdateGame();
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
				if (keyState[SDL_SCANCODE_W])
				{
					paddleDir -= 1;
				}
				if (keyState[SDL_SCANCODE_S])
				{
					paddleDir += 1;
				}
				
				
			}
			

		}
	}
}

//Comparing old frames againest new frames in seconds
void Game::UpdateGame()
{
	//Wait 16 ms from the last frame
	
	while (!TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));
	//The difference in ticks from the last frame
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	//Update count for next frame
	ticksCount = SDL_GetTicks();


	//Clamp so time never jumps to far forward
	if (deltaTime > 0.05)
	{
		deltaTime = 0.05;
	}

	if (paddleDir != 0) {
		//moves up at 300 pixels a second
		paddlePos.y = paddleDir * 300.0f * deltaTime;

		//up off the screen
		if (paddlePos.y < (paddleH / 2.0f + paddleW))
		{
			paddlePos.y = paddleH / 2.0f + paddleW;
		}
		//down off the screen
		else if (paddlePos.y > (screenH - paddleH / 2.0f - paddleW))
		{
			paddlePos.y = (screenH - paddleH / 2.0f - paddleW);
		}

	}
}

void Game::GenerateOutPut()
{

	SDL_FRect wall
	{
		paddlePos.x,
		paddlePos.y,
		paddleW,
		paddleH

	};
	SDL_FRect ball
	{
		(ballPos.x - paddleW / 2),
		(ballPos.y - paddleW / 2),
		paddleW,
		paddleW

	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//Clears backbuffer for the current draw color
	SDL_RenderClear(renderer);


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderFillRect(renderer, &wall);
	SDL_RenderFillRect(renderer, &ball);

	SDL_RenderPresent(renderer);
}
