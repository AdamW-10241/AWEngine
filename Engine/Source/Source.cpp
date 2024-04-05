#include <iostream>
#include "Game.h"

int main()
{
	// Randomise
	srand(time(0));
	// Static Function - Can Run Without Instance
	// Create Game
	Game::GetGame()->Run();
	// Destroy Game
	Game::DestroyGame();

	return 0;
}