#include "Game.h"

////////////////
//private func
////////////////

void Game::initWindow()
{
	this->videoMode = VideoMode(1700, 900);

	this->renderWindow = new RenderWindow(this->videoMode, "Space Soldier", sf::Style::Titlebar | sf::Style::Close);

	this->renderWindow->setFramerateLimit(144);
}

void Game::handleEvents()
{
	if (this->renderWindow->pollEvent(this->event))
	{
		//always check for this events
		switch (this->event.type)
		{
			case sf::Event::Closed:
			{
				cout << "Closing window...\n";

				this->renderWindow->close();

				break;
			}

			default: break;
		}

		//make decisions according to game state
		switch (this->gameState)
		{
			case GameStates::MAIN_MENU:
			{
				switch (this->event.type)
				{
					case sf::Event::MouseMoved:
					{
						Vector2i mousePos = sf::Mouse::getPosition(*this->renderWindow);
					
						//return to main menu click
						if (isMouseInTextRegion(mousePos, this->startGameText))
						{
							this->displayStartMenu(true, false);

							this->noRedraw = true;
						}
						//exit game click
						else if (isMouseInTextRegion(mousePos, this->exitGameText))
						{
							this->displayStartMenu(false, true);
					
							this->noRedraw = true;
						}
						else
						{
							this->noRedraw = false;
						}
					
						break;
					}
					
					case sf::Event::MouseButtonPressed:
					{
						Vector2i mousePos = sf::Mouse::getPosition(*this->renderWindow);
					
						//start game click
						if (isMouseInTextRegion(mousePos, this->startGameText))
						{
							this->gameState = GameStates::RENDER;

							this->changeHint();
						}
						//exit game click
						else if (isMouseInTextRegion(mousePos, this->exitGameText))
						{
							cout << "Closing window...\n";
					
							this->renderWindow->close();
						}
					
						break;
					}
					
					default: break;
				}

				break;
			}	
			
			case GameStates::PAUSE:
			{
				if (this->event.key.code == sf::Keyboard::Enter)
				{
					this->gameState = GameStates::RENDER;
				}

				break;
			}

			case GameStates::RENDER:
			{
				switch (this->event.type)
				{
					case sf::Event::MouseButtonPressed:
					{
						Bullet bullet(Vector2f(this->spaceShip.body.getPosition()), static_cast<float>(this->rotation));
					
						bullet.bullet.move(static_cast<float>(bullet.speed.x * cos(bullet.angle * M_PI / 180)),
							static_cast<float>(bullet.speed.y * sin(bullet.angle * M_PI / 180)));
					
						this->bullets.push_back(bullet);
					
						break;
					}
					
					default: break;
				}
					
				//keyboards events
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					this->gameState = GameStates::PAUSE;

					//display pause hint;
					this->renderWindow->draw(this->hintText);
					this->renderWindow->display();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
				{
					this->spaceShip.body.move(static_cast<float>(this->spaceShip.getSpeed().x * cos(this->rotation * M_PI / 180)),
						static_cast<float>(this->spaceShip.getSpeed().y * sin(this->rotation * M_PI / 180)));
					
					//cout << "Current Ship Pos--> x:" << this->spaceShip.body.getPosition().x << " y: " << this->spaceShip.body.getPosition().y << endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				{
					this->spaceShip.body.rotate(-4);
					this->rotation -= 4;
					this->rotation = this->rotation % 360;
					
					//cout << "Current rotation: " << this->rotation << endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				{
					this->spaceShip.body.rotate(4);
					this->rotation += 4;
					this->rotation = this->rotation % 360;
					
					//cout << "Current rotation: " << this->rotation << endl;
				}
					
				this->validatePosition();

				break;
			}

			case GameStates::GAME_OVER:
			{
				switch (this->event.type)
				{
					case sf::Event::MouseMoved:
					{
						Vector2i mousePos = sf::Mouse::getPosition(*this->renderWindow);

						//return to main menu click
						if (isMouseInTextRegion(mousePos, this->gameOverText))
						{
							this->gameOver(true, false);

							this->noRedraw = true;
						}
						//click on "Game over text"
						else if (isMouseInTextRegion(mousePos, this->returnToMainMenuText))
						{
							this->gameOver(false, true);

							this->noRedraw = true;
						}
						else
						{
							this->noRedraw = false;
						}

						break;
					}

					case sf::Event::MouseButtonPressed:
					{
						Vector2i mousePos = sf::Mouse::getPosition(*this->renderWindow);

						//return to main menu click
						if (isMouseInTextRegion(mousePos, this->returnToMainMenuText))
						{
							this->restartGame();
						}
						//click on "Game over text"
						else if (isMouseInTextRegion(mousePos, this->gameOverText))
						{
							cout << "Closing window...\n";

							this->renderWindow->close();
						}

						break;
					}	
						
					default: break;
				}

				break;
			}

			case GameStates::CREATE_PLAYER:
			{
				switch (this->event.type)
				{
					case sf::Event::TextEntered:
					{
						if (this->event.text.unicode == 8)//if BackSpace
						{
							if (this->nickname.getSize() > static_cast<size_t>(0)) this->nickname.erase(this->nickname.getSize() - 1, 1);
						}
						else if (this->event.text.unicode == 13)
						{
							if (this->nickname.getSize() > 0)
							{
								this->player.setName(this->nickname);

								this->gameState = GameStates::MAIN_MENU;

								this->changeHint();
							}
						}
						else if(this->event.text.unicode != 9 && this->event.text.unicode != 32) //if not Tab and Space
						{
							if(this->nickname.getSize() < 12) this->nickname += this->event.text.unicode;
						}

						break;
					}

					default: break;
				}

				break;
			}

			default: break;
		}
	}	
}

/////////////////
//rating handling
/////////////////

void Game::loadRating()
{
	std::ifstream data;
	data.open("..\\data.bin", std::ios::in | std::ios::binary);

	if (!data.is_open())
	{
		cout << "Failed to load rating.." << endl;

		this->ratingIsLoaded = false;
	}
	else
	{
		char info[255 + 1];

		string line;

		Player tempPlayer;

		while (data.getline(info, 255, '\n'))
		{
			line = info;
			
			line = binToString(line);

			tempPlayer.setName(line.substr(0, line.find_last_of(':')));
			tempPlayer.setPoints(atoi(line.substr(line.find_last_of(':') + 1).c_str()));

			this->rating.push_back(Player(tempPlayer));
		}

		data.close();
	}
}

void Game::updateRating()
{
	bool isInserted = false;

	for (vector<Player>::iterator iter = this->rating.begin(); iter != this->rating.end();)
	{
		if (*iter == this->player)
		{
			if(iter->getPoints() < this->player.getPoints()) iter->setPoints(this->player.getPoints());

			isInserted = true;

			break;
		}

		++iter;
	}

	if(!isInserted) this->rating.push_back(Player(this->player));

	//sort vector
	Player tempPlayer;

	int step = this->rating.size() / 2;

	while (step > 0)
	{
		for (unsigned int i = step; i < this->rating.size(); i++)
		{
			tempPlayer = this->rating[i];

			int j;

			for (j = i; j >= step && this->rating[j - step].getPoints() < tempPlayer.getPoints(); j -= step)
			{
				this->rating[j] = this->rating[j - step];
			}

			this->rating[j] = tempPlayer;
		}

		step /= 2;
	}

	if (this->rating.size() == 16) this->rating.pop_back();

	//rewrite rating
	string line = "";

	std::ofstream data;
	data.open("..\\data.bin", std::ios::out | std::ios::trunc | std::ios::binary);

	if (!data.is_open())
	{
		cout << "Failed to rewrite rating" << endl;
	}
	else
	{
		for (vector<Player>::iterator iter = this->rating.begin(); iter != this->rating.end(); )
		{
			line = iter->getName().toAnsiString();
			line += ":";
			line += std::to_string(iter->getPoints());

			line = stringToBin(line);
			line += '\n';

			data.write(line.c_str(), line.size());
			data.flush();

			line = "";

			++iter;
		}
	}

}

void Game::showRating()
{
	String board = "Top Player`s: \n";
	
	for (unsigned int iter = 0; iter < this->rating.size(); iter++)
	{
		board += std::to_string(iter + 1);
		board += ". ";
		board += this->rating[iter].getName();
		board += " ---> ";
		board += std::to_string(this->rating[iter].getPoints());
		board += "\n";
	}

	this->leaderboard.setString(board);

	this->renderWindow->draw(leaderboard);
}

/////////////////
//position validating
/////////////////

void Game::validatePosition()
{
	if (this->spaceShip.body.getPosition().x <= (0 - this->spaceShip.body.getOrigin().x / 2))
	{
		this->spaceShip.body.setPosition(static_cast<float>(this->renderWindow->getSize().x), 
									     static_cast<float>(this->renderWindow->getSize().y - this->spaceShip.body.getPosition().y));
	}
	if (this->spaceShip.body.getPosition().x >= (this->renderWindow->getSize().x + this->spaceShip.body.getOrigin().x / 2))
	{
		this->spaceShip.body.setPosition(0, static_cast<float>(this->renderWindow->getSize().y - this->spaceShip.body.getPosition().y));
	}
	if (this->spaceShip.body.getPosition().y <= (0 - this->spaceShip.body.getOrigin().y / 2))
	{
		this->spaceShip.body.setPosition(static_cast<float>(this->renderWindow->getSize().x - this->spaceShip.body.getPosition().x),
										 static_cast<float>(this->renderWindow->getSize().y));
	}
	if (this->spaceShip.body.getPosition().y >= (this->renderWindow->getSize().y + this->spaceShip.body.getOrigin().y / 2))
	{
		this->spaceShip.body.setPosition(static_cast<float>(this->renderWindow->getSize().x - this->spaceShip.body.getPosition().x), 0);
	}
}

/////////////////
//bulets logic
/////////////////

void Game::moveBullets()
{
	if (!this->bullets.empty())
	{
		for (unsigned int iter = 0; iter < this->bullets.size(); iter++)
		{
			this->bullets[iter].bullet.move(static_cast<float>(this->bullets[iter].speed.x * cos(this->bullets[iter].angle * M_PI / 180)),
				static_cast<float>(this->bullets[iter].speed.y * sin(this->bullets[iter].angle * M_PI / 180)));
		}
	}
}

void Game::drawBullets()
{
	this->deleteBullets();

	if (!this->bullets.empty())
	{
		for (Bullet object : this->bullets)
		{
			this->renderWindow->draw(object.bullet);
		}
	}
}

void Game::deleteBullets()
{
	if (!this->bullets.empty())
	{
		for (unsigned int iter = 0; iter < this->bullets.size(); iter++)
		{
			if(this->bullets[iter].bullet.getPosition().x <= 0 || this->bullets[iter].bullet.getPosition().x >= this->renderWindow->getSize().x ||
			   this->bullets[iter].isDestoyed)
			{
				this->bullets.erase(this->bullets.begin() + iter);
			}
			else if (this->bullets[iter].bullet.getPosition().y <= 0 || this->bullets[iter].bullet.getPosition().y >= this->renderWindow->getSize().y)
			{
				this->bullets.erase(this->bullets.begin() + iter);
			}
		}
	}
}

/////////////////
//asteroid logic
/////////////////

void Game::moveAsteroids()
{
	if (!this->asteroids.empty())
	{
		for (unsigned int iter = 0; iter < this->asteroids.size(); iter++)
		{
			this->asteroids[iter].meteorite.move(this->asteroids[iter].speed);
		}
	}
}

void Game::drawAsteroids()
{
	this->deleteAsteroids();

	if (!this->asteroids.empty())
	{
		for (Asteroid object : this->asteroids)
		{
			this->renderWindow->draw(object.meteorite);
		}
	}

	this->drawDestroyedAsteroids();
}

void Game::addAsteroids()
{
	if (rand() % 101 == 50 && this->asteroids.size() <= 6)
	{
		Asteroid tempAsteroid = Asteroid(this->renderWindow);

		tempAsteroid.meteorite.setTexture(this->asteroidTextures[rand() % this->asteroidTextures.size()]);
		tempAsteroid.meteorite.setOrigin(static_cast<float>(tempAsteroid.meteorite.getTexture()->getSize().x / 2),
			static_cast<float>(tempAsteroid.meteorite.getTexture()->getSize().y / 2));
		this->asteroids.push_back(tempAsteroid);
	}
}

void Game::drawDestroyedAsteroids()
{
	if (!this->destroyedAsteroids.empty())
	{
		for (unsigned int i = 0; i < this->destroyedAsteroids.size(); i++)
		{
			this->renderWindow->draw(this->destroyedAsteroids[i].meteorite);

			if (this->destroyedAsteroids[i].meteorite.getTexture() == &this->explosions[0]) this->destroyedAsteroids[i].meteorite.setTexture(this->explosions[1]);
			else if (this->destroyedAsteroids[i].meteorite.getTexture() == &this->explosions[1]) this->destroyedAsteroids[i].meteorite.setTexture(this->explosions[2]);
			else if (this->destroyedAsteroids[i].meteorite.getTexture() == &this->explosions[2]) this->destroyedAsteroids[i].meteorite.setTexture(this->explosions[3]);
			else if (this->destroyedAsteroids[i].meteorite.getTexture() == &this->explosions[3]) this->destroyedAsteroids[i].meteorite.setTexture(this->explosions[4]);
			else if (this->destroyedAsteroids[i].meteorite.getTexture() == &this->explosions[4])
			{
				this->destroyedAsteroids.erase(this->destroyedAsteroids.begin() + i);
			}
		}
	}
}

void Game::deleteAsteroids()
{
	if (!this->asteroids.empty())
	{
		for (unsigned int iter = 0; iter < this->asteroids.size(); iter++)
		{
			if (this->asteroids[iter].meteorite.getPosition().x < 0 || this->asteroids[iter].meteorite.getPosition().x > this->renderWindow->getSize().x ||
				this->asteroids[iter].health <= 0)
			{
				this->asteroids.erase(this->asteroids.begin() + iter);
			}
			else if (this->asteroids[iter].meteorite.getPosition().y < 0 || this->asteroids[iter].meteorite.getPosition().y > this->renderWindow->getSize().y)
			{
				this->asteroids.erase(this->asteroids.begin() + iter);
			}
		}
	}
}

/////////////////
//collision
/////////////////

void Game::collisionCheck()
{
	//ship part
	if (!this->asteroids.empty())
	{
		for (vector<Asteroid>::iterator aIter = this->asteroids.begin(); aIter != this->asteroids.end();)
		{
			if (shipAndAsteroidIntersect(aIter->meteorite, this->spaceShip.body))
			{
				aIter->health = 0;
				aIter->meteorite.setTexture(this->explosions[0]);
				aIter->meteorite.setTextureRect(sf::IntRect(0, 0, 90, 90));

				this->destroyedAsteroids.push_back(*aIter);

				this->totalPoints -= aIter->points;

				if (this->totalPoints < 0) this->totalPoints = 0;

				this->spaceShip.setHealth(this->spaceShip.getHealth() - aIter->damage);
				
				this->hpBarRect.setFillColor(sf::Color::Red);
				
				if (this->spaceShip.getHealth() <= 0)
				{
					std::cout << "Game over..." << std::endl;

					this->player.setPoints(this->totalPoints);

					this->updateRating();

					this->gameState = GameStates::GAME_OVER;
				}
				else
				{
					this->hpBarRect.setSize(Vector2f(static_cast<float>(this->spaceShip.getHealth()), 15.f));
				}
			}

			aIter++;
		}
	}

	//bullets part
	if (!this->bullets.empty() && !this->asteroids.empty())
	{
		for (vector<Bullet>::iterator bIter = this->bullets.begin(); bIter != this->bullets.end(); )
		{
			for (vector<Asteroid>::iterator aIter = this->asteroids.begin(); aIter != this->asteroids.end();)
			{
				if (bulletAndAsteroidIntersect(aIter->meteorite, bIter->bullet))
				{
					aIter->health -= bIter->damage;

					//destroy asteroid if health <= 0
					if (aIter->health <= 0)
					{
						aIter->meteorite.setTexture(this->explosions[0]);
						aIter->meteorite.setTextureRect(sf::IntRect(0, 0, 90, 90));
						aIter->meteorite.setOrigin(Vector2f(45.f, 45.f));
						this->destroyedAsteroids.push_back(*aIter);
					
						this->totalPoints += aIter->points;
					}

					//destory bullet
					bIter->bullet.setRadius(16);
					bIter->bullet.setTexture(&this->explosions[this->explosions.size() - 1]);
					this->renderWindow->draw(bIter->bullet);
					bIter->isDestoyed = true;
				}
				++aIter;
			}
			++bIter;
		}
	}
}

/////////////////
//change hint according to state
/////////////////

void Game::changeHint()
{
	switch (this->gameState)
	{
		case GameStates::CREATE_PLAYER:
		{
			this->hintText.setString(String("--- 1 <-> 12 nickname length\n--- Press 'Enter' to continue"));
			this->hintText.setCharacterSize(18);
			this->hintText.setFillColor(sf::Color(255, 255, 255, 230));
			this->hintText.setPosition(
				Vector2f(this->creatingPlayerText.getGlobalBounds().left + this->creatingPlayerText.getGlobalBounds().width,
						 this->creatingPlayerText.getGlobalBounds().top + this->creatingPlayerText.getGlobalBounds().height + 20));

			break;
		}

		case GameStates::MAIN_MENU:
		{
			this->hintText.setString(String("Player: " + this->nickname));
			this->hintText.setCharacterSize(30);
			this->hintText.setFillColor(sf::Color::Green);
			this->hintText.setPosition(20.f, 20.f);

			break;
		}

		case GameStates::RENDER:
		{
			this->hintText.setString(String("--------PAUSE--------\nPress 'Enter' to continue"));
			this->hintText.setCharacterSize(40);
			this->hintText.setFillColor(sf::Color::White);
			this->hintText.setPosition(
				static_cast<float>(this->renderWindow->getSize().x / 2 - this->hintText.getGlobalBounds().width / 2.f),
				static_cast<float>(this->renderWindow->getSize().y / 2 - this->hintText.getGlobalBounds().height / 2.f));

			break;
		}

		default: break;
	}
}

/////////////////
//init texts
/////////////////

void Game::initTexts()
{
	//start game text
	this->startGameText.setFont(this->textFont);
	this->startGameText.setString(String("Start Game"));
	this->startGameText.setCharacterSize(50);
	this->startGameText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2 - startGameText.getGlobalBounds().width / 2.f),
		static_cast<float>(this->renderWindow->getSize().y / 2 - startGameText.getGlobalBounds().height / 2.f - 100.f)
	);

	//exit game text
	this->exitGameText.setFont(this->textFont);
	this->exitGameText.setString(String("Exit Game"));
	this->exitGameText.setCharacterSize(35);
	this->exitGameText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2 - exitGameText.getGlobalBounds().width / 2.f),
		static_cast<float>(this->renderWindow->getSize().y / 2 - exitGameText.getGlobalBounds().height / 2.f + 100.f)
	);

	//return to menu text
	this->returnToMainMenuText.setFont(this->textFont);
	this->returnToMainMenuText.setString(String("Return"));
	this->returnToMainMenuText.setCharacterSize(40);
	this->returnToMainMenuText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x - exitGameText.getGlobalBounds().width - 30.f),
		static_cast<float>(this->renderWindow->getSize().y - exitGameText.getGlobalBounds().height - 50.f)
	);

	//game over text
	this->gameOverText.setString(String("GAME OVER"));
	this->gameOverText.setFont(this->textFont);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2 - this->gameOverText.getGlobalBounds().width / 2.f),
		static_cast<float>(this->renderWindow->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2.f)
	);

	//creating player text
	this->creatingPlayerText.setString(String("Enter Players Nickname: "));
	this->creatingPlayerText.setFont(this->textFont);
	this->creatingPlayerText.setCharacterSize(40);
	this->creatingPlayerText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2 - this->creatingPlayerText.getGlobalBounds().width),
		static_cast<float>(this->renderWindow->getSize().y / 2 - this->creatingPlayerText.getGlobalBounds().height / 2.f)
	);
	this->creatingPlayerText.setStyle(sf::Text::Style::Underlined);

	//creating text to show user input
	this->playersName.setString(this->nickname);
	this->playersName.setFont(this->textFont);
	this->playersName.setCharacterSize(30);
	this->playersName.setFillColor(sf::Color::Red);
	this->playersName.setPosition(
		static_cast<float>(this->creatingPlayerText.getGlobalBounds().left + this->creatingPlayerText.getGlobalBounds().width + 20),
		static_cast<float>(this->creatingPlayerText.getGlobalBounds().top + 5)
	);

	//create text to display leaderboard
	this->leaderboard.setString(String(""));
	this->leaderboard.setFont(this->textFont);
	this->leaderboard.setCharacterSize(25);
	this->leaderboard.setFillColor(sf::Color(38, 111, 255));
	this->leaderboard.setPosition(20.f, 20.f);

	//init first state hint
	this->hintText.setString(String("--- 1 <-> 12 nickname length\n--- Press 'Enter' to continue"));
	this->hintText.setFont(this->textFont);
	this->hintText.setCharacterSize(18);
	this->hintText.setFillColor(sf::Color(255, 255, 255, 230));
	this->hintText.setPosition(
		Vector2f(this->creatingPlayerText.getGlobalBounds().left + this->creatingPlayerText.getGlobalBounds().width,
				 this->creatingPlayerText.getGlobalBounds().top + this->creatingPlayerText.getGlobalBounds().height + 20));
}

/////////////////
//load textures
/////////////////

void Game::loadTextures()
{
	//ship texture
	if (!this->spriteTexture.loadFromFile("..\\Images\\Ship\\SpaceShip.png"))
	{
		std::cout << "Failed to load Texture\n";

		this->renderWindow->close();
	}

	//background image
	if (!this->backgroundTexture.loadFromFile("..\\Images\\Background\\Background.jpg"))
	{
		std::cout << "Failed to load background texture";
	}

	//asteroids images
	Texture tempTexture;

	if (!tempTexture.loadFromFile("..\\Images\\Asteroid\\Asteroid1.png"))
	{
		std::cout << "Failed to load asteroid_1 texture";
	}

	this->asteroidTextures.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Asteroid\\Asteroid2.png"))
	{
		std::cout << "Failed to load asteroid_2 texture";
	}

	this->asteroidTextures.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Asteroid\\Asteroid3.png"))
	{
		std::cout << "Failed to load asteroid_3 texture";
	}

	this->asteroidTextures.push_back(Texture(tempTexture));

	//explosion images

	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\Stage0.png"))
	{
		std::cout << "Failed to load explosion 1 texture";
	}

	this->explosions.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\Stage1.png"))
	{
		std::cout << "Failed to load explosion 1 texture";
	}

	this->explosions.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\Stage2.png"))
	{
		std::cout << "Failed to load explosion 2 texture";
	}

	this->explosions.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\Stage3.png"))
	{
		std::cout << "Failed to load explosion 3 texture";
	}

	this->explosions.push_back(Texture(tempTexture));

	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\Stage4.png"))
	{
		std::cout << "Failed to load explosion 4 texture";
	}

	this->explosions.push_back(Texture(tempTexture));

	//bullets explosion will be last texture in vector
	if (!tempTexture.loadFromFile("..\\Images\\Explosion\\BulletsHit.png"))
	{
		std::cout << "Failed to load explosion bullets explosion texture";
	}

	this->explosions.push_back(Texture(tempTexture));
}

/////////////////
//updating HUD
/////////////////

void Game::updateHpBar()
{
	this->hpBarRect.setSize(Vector2f(static_cast<float>(this->spaceShip.getHealth()), 15.f));
	
	this->renderWindow->draw(this->hpBarRect);
	
	this->hpBarRect.setFillColor(sf::Color::Green);

	RectangleShape borderRect;

	borderRect.setSize(Vector2f(202.f, 17.f));
	borderRect.setOutlineColor(sf::Color::White);
	borderRect.setFillColor(sf::Color::Transparent);
	borderRect.setOutlineThickness(1.f);
	borderRect.setPosition(static_cast<float>(this->renderWindow->getSize().x - 251), 19.f);

	this->renderWindow->draw(borderRect);
}

void Game::updatePoints()
{
	Text points;
	points.setFont(this->textFont);
	points.setString(sf::String("Score: " + std::to_string(this->totalPoints)));
	points.setPosition(10.f, 10.f);

	this->renderWindow->draw(points);
}

/////////////////
//updating game states 
/////////////////

void Game::restartGame()
{
	//reinit ship pos and settings
	this->spaceShip.setHealth(200);
	this->spaceShip.body.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2),
		static_cast<float>(this->renderWindow->getSize().y / 2));
	this->spaceShip.body.setRotation(90);

	//reinit vars
	this->rotation = 0;
	this->totalPoints = 0;

	this->noRedraw = false;

	//set first game state
	this->gameState = GameStates::CREATE_PLAYER;

	this->changeHint();

	//clear entiti vectors 
	this->destroyedAsteroids.clear();
	this->asteroids.clear();
	this->bullets.clear();
}

////////////////
//public func
////////////////

void Game::gameOver(bool gameOverHover, bool returnHover)
{
	this->renderWindow->clear(sf::Color::Black);
	this->renderWindow->draw(this->background);

	this->renderWindow->draw(this->gameOverText);
	this->renderWindow->draw(this->returnToMainMenuText);

	if (gameOverHover)
	{
		RectangleShape borders;
		borders.setSize(
			Vector2f(this->gameOverText.getGlobalBounds().width + 8,
				this->gameOverText.getGlobalBounds().height + 16));
		borders.setPosition(
			Vector2f(this->gameOverText.getPosition().x - 4,
				this->gameOverText.getPosition().y - 1));
		borders.setOutlineThickness(1.5f);
		borders.setFillColor(sf::Color::Transparent);

		this->renderWindow->draw(borders);
	}

	if (returnHover)
	{
		RectangleShape borders;
		borders.setSize(
			Vector2f(this->returnToMainMenuText.getGlobalBounds().width + 8,
				this->returnToMainMenuText.getGlobalBounds().height + 16));
		borders.setPosition(
			Vector2f(this->returnToMainMenuText.getPosition().x - 4,
				this->returnToMainMenuText.getPosition().y - 1));
		borders.setOutlineThickness(1.5f);
		borders.setFillColor(sf::Color::Transparent);

		this->renderWindow->draw(borders);
	}

	this->showRating();

	this->renderWindow->display();
}

void Game::displayStartMenu(bool startGameHover, bool exitGameHover)
{
	this->renderWindow->clear(sf::Color::Black);
	this->renderWindow->draw(this->background);

	//draw texts
	this->renderWindow->draw(this->startGameText);
	this->renderWindow->draw(this->exitGameText);
	this->renderWindow->draw(this->hintText);

	if (startGameHover)
	{
		RectangleShape borders;
		borders.setSize(
			Vector2f(this->startGameText.getGlobalBounds().width + 8, 
					 this->startGameText.getGlobalBounds().height + 16));
		borders.setPosition(
			Vector2f(this->startGameText.getPosition().x - 4,
					 this->startGameText.getPosition().y - 1));
		borders.setOutlineThickness(1.5f);
		borders.setFillColor(sf::Color::Transparent);

		this->renderWindow->draw(borders);
	}

	if (exitGameHover)
	{
		RectangleShape borders;
		borders.setSize(
			Vector2f(this->exitGameText.getGlobalBounds().width + 8,
					this->exitGameText.getGlobalBounds().height + 16));
		borders.setPosition(
			Vector2f(this->exitGameText.getPosition().x - 4,
					this->exitGameText.getPosition().y - 1));
		borders.setOutlineThickness(1.5f);
		borders.setFillColor(sf::Color::Transparent);

		this->renderWindow->draw(borders);
	}

	this->renderWindow->display();
}

void Game::createPlayer()
{
	this->renderWindow->clear(sf::Color::Black);
	this->renderWindow->draw(this->background);

	this->playersName.setString(this->nickname);

	this->renderWindow->draw(this->creatingPlayerText);
	this->renderWindow->draw(this->inputRect);
	this->renderWindow->draw(this->playersName);
	this->renderWindow->draw(this->hintText);

	this->renderWindow->display();
}

/////////////////
//main update loop
/////////////////

void Game::update()
{
	this->handleEvents();

	if (this->gameState == GameStates::RENDER) this->addAsteroids();
}

/////////////////
//main render loop
/////////////////

void Game::render()
{
	if (this->gameState == GameStates::RENDER)
	{
		this->renderWindow->clear(sf::Color::Black);
		this->renderWindow->draw(this->background);

		//redraw ship
		this->renderWindow->draw(this->spaceShip.body);

		//bullets logic
		this->moveBullets();

		//asteroid logic
		this->moveAsteroids();

		this->collisionCheck();

		//draw entities
		this->drawBullets();
		this->drawAsteroids();

		//update and draw hpBar
		this->updateHpBar();

		//update points
		this->updatePoints();

		//display all objects
		this->renderWindow->display();
	}
}

/////////////////
//return true if window is still running
/////////////////

bool Game::isRunning()
{
	return this->renderWindow->isOpen();
}

////////////////
//constr & destr
////////////////

Game::Game()
{
	//load rating
	this->loadRating();

	//init window
	this->initWindow();

	//load textures
	this->loadTextures();

	//create ship
	this->spaceShip = SpaceShip(this->videoMode.width, this->videoMode.height);

	//ship settings
	this->spaceShip.body.setTexture(this->spriteTexture);
	this->spaceShip.body.setOrigin(
		Vector2f(static_cast<float>(this->spriteTexture.getSize().x / 2.f), 
			     static_cast<float>(this->spriteTexture.getSize().y / 2.f))
	);
	this->spaceShip.body.setRotation(90);

	//background texture
	this->background.setTexture(this->backgroundTexture);

	//hp bar settings
	this->hpBarRect.setSize(Vector2f(static_cast<float>(this->spaceShip.getHealth()), 15.f));
	this->hpBarRect.setFillColor(sf::Color::Green);
	this->hpBarRect.setPosition(static_cast<float>(this->renderWindow->getSize().x - 250.f), 20.f);

	//start variables
	this->rotation = 0;
	this->totalPoints = 0;

	this->nickname = "";

	this->noRedraw = false;

	//set first game state
	this->gameState = GameStates::CREATE_PLAYER;

	//load font
	this->textFont.loadFromFile("..\\Font\\Hello Jones Free Trial.ttf");
	
	//set navigation texts
	this->initTexts();

	//init input rect
	this->inputRect.setSize(
		Vector2f(this->creatingPlayerText.getGlobalBounds().width / 1.25f,
				 this->creatingPlayerText.getGlobalBounds().height)
	);
	this->inputRect.setFillColor(sf::Color::Black);
	this->inputRect.setOutlineThickness(2.f);
	this->inputRect.setPosition(
		Vector2f(this->creatingPlayerText.getGlobalBounds().left + this->creatingPlayerText.getGlobalBounds().width + 10,
				 this->creatingPlayerText.getGlobalBounds().top)
	);
}

Game::~Game()
{
	delete this->renderWindow;
}