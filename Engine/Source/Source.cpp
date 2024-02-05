#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	// Static Function - Can Run Without Instance
	// Create Game
	Game::GetGame()->Run();
	// Destroy Game
	Game::DestroyGame();

	return 0;
}