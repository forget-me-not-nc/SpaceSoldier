#include <ctime>
#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	cout << "--------------Log--------------\n";

	//init game class
	Game game;

	//game loop
	while (game.isRunning())
	{
		game.update();
		
		game.render();
	}

	//end program
	return 0;
}

