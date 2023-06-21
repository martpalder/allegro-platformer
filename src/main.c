#include "./game.h"

int main(int argc, char** argv)
{
	// Game variable
	Game game;

	// Initialize the game
	game = initGame();

	// Run the game
	runGame(game);
	
	// Quit the game
	quitGame(game);
	return 0;
}
