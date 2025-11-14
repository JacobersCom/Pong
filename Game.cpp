#include "Game.h"

Game::Game() {

	window = nullptr;
	renderer = nullptr;
	isRunning = true;

	player1Pos.x = 10;
	player1Pos.y = 225;
	player2Pos.x = 475;
	player2Pos.y = 225;

	player1Dir = 0.0f;
	player2Dir = 0.0f;


	ballPos.x = 250;
	ballPos.y = 250;

	//Vel in pixels
	ballVel.x = -60.0f;
	ballVel.y = 60.0f;

	ticksCount = 0;

	GameStart = false;
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

				//Quit
				if (keyState[SDL_SCANCODE_ESCAPE])
				{
					isRunning = false;
				}
				
				//Player 1 movement
				if (keyState[SDL_SCANCODE_W])
				{
					player1Dir -= 1;
				}
				if (keyState[SDL_SCANCODE_S])
				{
					player1Dir += 1;
				}

				//Player 2 movement
				if (keyState[SDL_SCANCODE_I]) 
				{
					player2Dir -= 1;
				}
				if(keyState[SDL_SCANCODE_J])
				{
					player2Dir += 1;
				}
				
				if(keyState[SDL_SCANCODE_1])
				{
					GameStart = true;
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
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	
	
		ballPos.x += ballVel.x * deltaTime;
		ballPos.y += ballVel.y * deltaTime;
		
		//Is the ball calliding with the top of the wall and moving up?
		

		if (player1Dir != 0) {
			//moves up at 300 pixels a second
			player1Pos.y = player1Dir * 300.0f * deltaTime;

			//up off the screen
			if (player1Pos.y < (paddleH / 2.0f + paddleW))
			{
				player1Pos.y = paddleH / 2.0f + paddleW;
			}
			//down off the screen
			else if (player1Pos.y > (screenH - paddleH / 2.0f - paddleW))
			{
				player1Pos.y = (screenH - paddleH / 2.0f - paddleW);
			}

		}

		if (player2Dir != 0) {
			//moves up at 300 pixels a second
			player2Pos.y = player2Dir * 300.0f * deltaTime;

			//up off the screen
			if (player2Pos.y < (paddleH / 2.0f + paddleW))
			{
				player2Pos.y = paddleH / 2.0f + paddleW;
			}
			//down off the screen
			else if (player2Pos.y > (screenH - paddleH / 2.0f - paddleW))
			{
				player2Pos.y = (screenH - paddleH / 2.0f - paddleW);
			}


		}
		
		float diff = player1Pos.y - ballPos.y;
		diff = (diff > 0) ? diff : -diff;

		if (ballPos.y <= wallW)
		{
			ballPos.y = wallW;
		}
		
		else if (ballPos.y > (screenH - paddleH / 2))
		{
			ballPos.y = (screenH - paddleH / 2);
		}
		
		
		
}

void Game::GenerateOutPut()
{
	SDL_FRect topWall
	{
		0,
		0,
		wallW,
		wallH
	};
	SDL_FRect bottomWall
	{
		0,
		500,
		wallW,
		wallH
	};


	SDL_FRect player1
	{
		player1Pos.x,
		player1Pos.y,
		paddleW,
		paddleH

	};

	SDL_FRect player2
	{
			player2Pos.x,
			player2Pos.y,
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
	SDL_RenderFillRect(renderer, &player1);
	SDL_RenderFillRect(renderer, &player2);
	SDL_RenderFillRect(renderer, &ball);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &topWall);
	SDL_RenderFillRect(renderer, &bottomWall);



	SDL_RenderPresent(renderer);
}
