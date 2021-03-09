#include <ctime>
#include <thread>

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
		
		if (game.startMenu) game.displayStartMenu();
		else if(!game.isPaused && !game.isOver) game.render();

		std::this_thread::sleep_for(std::chrono::milliseconds(1)); //to reduce the load on CPU while game is waiting to change state 
	}

	//end program
	return 0;
}

