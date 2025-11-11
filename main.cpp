#include "SDL3/SDL.h"
#include "Game.h"
//Create a rendering service and a game loop. Make then in singletons
//Then Create a defines file which will hold things like types and #defines
//Then go into create a controller service.
//Everything should be a service.

int main() {
	


	Game game();

	game.Init();
	

	game.Start_Game();
	game.Stop_Game();

	return 0;
}