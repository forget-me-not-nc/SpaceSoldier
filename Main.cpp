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

		switch (game.gameState)
		{
			case GameStates::MAIN_MENU:
			{
				if(!game.noRedraw) game.displayStartMenu(false, false);

				break;
			}	

			case GameStates::GAME_OVER:
			{
				if (!game.noRedraw) game.gameOver(false, false);

				break;
			}

			case GameStates::CREATE_PLAYER:
			{
				game.createPlayer();

				break;
			}

			default: break;
		}

		game.render();

		std::this_thread::sleep_for(std::chrono::milliseconds(1)); //to reduce the load on CPU while game is waiting to change state 
	}

	//end program
	return 0;
}

