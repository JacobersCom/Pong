#include "Game.h"

Game::Game() {

	window = nullptr;
	renderer = nullptr;
	isRunning = true;

	player1Pos.x = 10;
	player1Pos.y = paddleH / 3.0f + paddleW;
	player2Pos.x = 475;
	player2Pos.y = paddleH / 3.0f + paddleW;

	player1Dir = 0.0f;
	player2Dir = 0.0f;


	ballPos.x = 250;
	ballPos.y = 250;

	//Vel in pixels
	ballVel.x = 100;
	ballVel.y = -100;

	ticksCount = 0;

	GameStart = false;
}

bool Game::Init() {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR: Failed to init SDL video %s\n", SDL_GetError());
		return false;
	};

	window = SDL_CreateWindow("Pong", screenW, screenH, NULL);

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

		}
		
		//up off the screen
		if (player1Pos.y < (paddleH / 3.0f + paddleW))
		{
			player1Pos.y = paddleH / 3.0f + paddleW;
		}
		//down off the screen
		else if (player1Pos.y > (screenH - paddleH / 3.0f - paddleW))
		{
			player1Pos.y = (screenH - paddleH / 3.0f - paddleW);
		}


		if (player2Dir != 0) {
			//moves up at 300 pixels a second
			player2Pos.y = player2Dir * 300.0f * deltaTime;
		}
		//up off the screen
		if (player2Pos.y < (paddleH / 3.0f + paddleW))
		{
			player2Pos.y = paddleH / 3.0f + paddleW;
		}
		//down off the screen
		else if (player2Pos.y > (screenH - paddleH / 2.0f - paddleW))
		{
			player2Pos.y = (screenH - paddleH / 2.0f - paddleW);
		}

		
		float diffPlayer1 = ballPos.y - player1Pos.y;
		diffPlayer1 = (diffPlayer1 > 0) ? diffPlayer1 : -diffPlayer1;

		//If the diff is not great than the paddle's height negate.
		if (diffPlayer1 <= paddleH
			&& ballPos.x < 25.0f
			&& ballPos.x > 20.0f
			&& ballVel.x < 0.0f)
		{
			ballVel.x *= -1.0f;
			
		}
		
		float diffPlayer2 = player2Pos.y - ballPos.y;
		diffPlayer2 = (diffPlayer2 > 0) ? diffPlayer2 : -diffPlayer2;
		
		//If the diff is not great than the paddle's height negate.
		if (diffPlayer2 <= paddleH
			&& ballPos.x < 475.0f
			&& ballPos.x > 470.0f
			&& ballVel.x > 0.0f)
		{
			ballVel.x *= -1.0f;
			
		}
		
		if (ballPos.y >= bottomWall.y) 
		{
			ballVel.y *= -1.0f;
		}

		if (ballPos.y <= topWall.y)
		{
			ballVel.y *= -1.0f;
		}
		
		if (ballPos.x > screenW)
		{
			//player one wins
			//std::cout << "Left paddle wins!" << std::endl;
			//isRunning = false;
		}
		else if(ballPos.x < 0.0f)
		{
			//player two wins
			//std::cout << "Right paddle wins!" << std::endl;
			//isRunning = false;
		}

}

void Game::GenerateOutPut()
{
	

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
