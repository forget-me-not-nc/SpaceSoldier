#include "Game.h"

//private func

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

		if (this->event.key.code == sf::Keyboard::Escape)
		{
			this->isPaused = true;
		}

		if (this->isOver)
		{
			this->gameOver();
		}
		else if (this->isPaused)
		{
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->isPaused = true;
			}
			if (this->event.key.code == sf::Keyboard::Enter)
			{
				this->isPaused = false;
			}
		}
		else if(!this->isPaused)
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				this->spaceShip.body.move(static_cast<float>(this->spaceShip.getSpeed().x * cos(this->rotation * M_PI / 180)),
										  static_cast<float>(this->spaceShip.getSpeed().y * sin(this->rotation * M_PI / 180)));

				//cout << "Current Ship Pos--> x:" << this->spaceShip.body.getPosition().x << " y: " << this->spaceShip.body.getPosition().y << endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				this->spaceShip.body.rotate(-3);
				this->rotation -= 3;
				this->rotation = this->rotation % 360;

				//cout << "Current rotation: " << this->rotation << endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				this->spaceShip.body.rotate(3);
				this->rotation += 3;
				this->rotation = this->rotation % 360;

				//cout << "Current rotation: " << this->rotation << endl;
			}

			this->validatePosition();
			
		}
	}	
}

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

void Game::validateSpeed()
{

}

//bulets logic

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
		for(Bullet object : this->bullets)
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

//asteroid logic

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

//collision

void Game::collisionCheck()
{
	//ship part
	if (!this->asteroids.empty())
	{
		for (vector<Asteroid>::iterator aIter = this->asteroids.begin(); aIter != this->asteroids.end();)
		{
			if (this->shipAndAsteroidIntersect(aIter->meteorite))
			{
				aIter->health = 0;
				aIter->meteorite.setTexture(this->explosions[0]);
				this->destroyedAsteroids.push_back(*aIter);

				this->spaceShip.setHealth(this->spaceShip.getHealth() - aIter->damage);
				
				this->hpBarRect.setFillColor(sf::Color::Red);
				
				if (this->spaceShip.getHealth() <= 0)
				{
					std::cout << "Game over..." << std::endl;

					this->isOver = true;
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
				if (this->bulletAndAsteroidIntersect(aIter->meteorite, bIter->bullet))
				{
					aIter->health -= bIter->damage;

					//destroy asteroid if health <= 0
					if (aIter->health <= 0)
					{
						aIter->meteorite.setTexture(this->explosions[0]);
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

bool Game::bulletAndAsteroidIntersect(const Sprite &asteroid, const CircleShape &bullet)
{
	float dX = asteroid.getPosition().x - bullet.getPosition().x;
	float dY = asteroid.getPosition().y - bullet.getPosition().y;

	float spriteRadius = static_cast<float>((asteroid.getTexture()->getSize().x + asteroid.getTexture()->getSize().y) / 4);

	return sqrt(dX * dX + dY * dY) <= (spriteRadius + bullet.getRadius());
}

bool Game::shipAndAsteroidIntersect(const Sprite& asteroid)
{
	float dX = asteroid.getPosition().x - this->spaceShip.body.getPosition().x;
	float dY = asteroid.getPosition().y - this->spaceShip.body.getPosition().y;

	float spriteRadius = static_cast<float>((asteroid.getTexture()->getSize().x + asteroid.getTexture()->getSize().y) / 4);
	float shipRadius = static_cast<float>((this->spaceShip.body.getTexture()->getSize().x + this->spaceShip.body.getTexture()->getSize().y) / 4);

	return sqrt(dX * dX + dY * dY) <= (spriteRadius + shipRadius);
}

//load textures

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
	points.setString(sf::String(std::to_string(this->totalPoints)));
	points.setPosition(10.f, 10.f);

	this->renderWindow->draw(points);
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

void Game::gameOver()
{
	this->renderWindow->clear(sf::Color::Black);
	this->renderWindow->draw(this->background);

	Text gameOverText;
	gameOverText.setString(sf::String("GAME OVER"));
	gameOverText.setFont(this->textFont);
	gameOverText.setCharacterSize(40);
	gameOverText.setPosition(
		static_cast<float>(this->renderWindow->getSize().x / 2 - gameOverText.getGlobalBounds().width / 2),
		static_cast<float>(this->renderWindow->getSize().y / 2 - gameOverText.getGlobalBounds().height / 2));

	this->renderWindow->draw(gameOverText);

	this->renderWindow->display();
}

//public func

void Game::update()
{
	this->handleEvents();

	if (!this->isPaused) this->addAsteroids();
}

//main render loop
void Game::render()
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

bool Game::isRunning()
{
	return this->renderWindow->isOpen();
}

//constr & destr

Game::Game()
{
	this->initWindow();

	this->loadTextures();

	this->spaceShip = SpaceShip(this->videoMode.width, this->videoMode.height);

	this->spaceShip.body.setTexture(this->spriteTexture);
	this->spaceShip.body.setOrigin(Vector2f(static_cast<float>(this->spriteTexture.getSize().x / 2), static_cast<float>(this->spriteTexture.getSize().y / 2)));
	this->spaceShip.body.setRotation(90);

	this->background.setTexture(this->backgroundTexture);

	this->hpBarRect.setSize(Vector2f(static_cast<float>(this->spaceShip.getHealth()), 15));
	this->hpBarRect.setFillColor(sf::Color::Green);
	this->hpBarRect.setPosition(static_cast<float>(this->renderWindow->getSize().x - 250), 20.f);

	this->rotation = 0;
	this->totalPoints = 0;

	this->isPaused = false;
	this->isOver = false;

	this->textFont.loadFromFile("..\\Font\\Hello Jones Free Trial.ttf");
}

Game::~Game()
{
	delete this->renderWindow;
}

