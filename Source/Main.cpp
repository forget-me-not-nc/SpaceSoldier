#include "Game.h"


int main()
{
	srand(static_cast<unsigned int>(time(NULL))); //for random

	cout << "--------------Log--------------\n";

	//init game class
	Game game;

	//game loop
	while (game.isRunning())
	{
		game.update(); //update game

		switch (game.gameState)
		{
			case GameStates::MAIN_MENU:
			{
				if(!game.noRedraw) game.displayStartMenu(false, false); //satrt menu

				break;
			}	

			case GameStates::GAME_OVER:
			{
				if (!game.noRedraw) game.gameOver(false, false); //game over event

				break;
			}

			case GameStates::CREATE_PLAYER:
			{
				game.createPlayer(); //player creation menu

				break;
			}

			default: break;
		}

		game.render(); //render game

		std::this_thread::sleep_for(std::chrono::milliseconds(1)); //to reduce the load on CPU while game is waiting to change state 
	}

	//end program
	return 0;
}

