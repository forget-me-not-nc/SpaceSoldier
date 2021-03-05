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
	if(this->renderWindow->pollEvent(this->event))
	{
		switch (this->event.type)
		{
			case sf::Event::Closed:
			{
				cout << "Closing window...\n";

				this->renderWindow->close();

				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				Bullet leftBullet(Vector2f(this->spaceShip.body.getPosition() - this->spaceShip.body.getOrigin()), static_cast<float>(this->rotation));

				leftBullet.bullet.move(static_cast<float>(leftBullet.speed.x * cos(leftBullet.angle * M_PI / 180)),
									   static_cast<float>(leftBullet.speed.y * sin(leftBullet.angle * M_PI / 180)));

				this->bullets.push_back(leftBullet);

				Bullet rightBullet(Vector2f(this->spaceShip.body.getPosition() + this->spaceShip.body.getOrigin()), static_cast<float>(this->rotation));

				rightBullet.bullet.move(static_cast<float>(rightBullet.speed.x * cos(rightBullet.angle * M_PI / 180)),
									   static_cast<float>(rightBullet.speed.y * sin(rightBullet.angle * M_PI / 180)));

				this->bullets.push_back(rightBullet);

				break;
			}

			default: break;
		}

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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->spaceShip.body.rotate(3);
			this->rotation += 3;
			this->rotation = this->rotation % 360;

			//cout << "Current rotation: " << this->rotation << endl;
		}

		this->validatePosition();
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
			if(this->bullets[iter].bullet.getPosition().x <= 0 || this->bullets[iter].bullet.getPosition().x >= this->renderWindow->getSize().x)
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
}

void Game::deleteAsteroids()
{
	if (!this->asteroids.empty())
	{
		for (unsigned int iter = 0; iter < this->asteroids.size(); iter++)
		{
			if (this->asteroids[iter].meteorite.getPosition().x < 0 || this->asteroids[iter].meteorite.getPosition().x > this->renderWindow->getSize().x)
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
//public func

void Game::update()
{
	this->handleEvents();

	if (rand() % 101 == 50 && this->asteroids.size() <= 6)
	{
		this->asteroids.push_back(Asteroid(this->renderWindow));
	}
}

void Game::render()
{
	this->renderWindow->clear(sf::Color::Black);

	//redraw ship
	this->renderWindow->draw(this->spaceShip.body);

	//bullets logic
	this->moveBullets();
	this->drawBullets();

	//asteroid logic
	this->moveAsteroids();
	this->drawAsteroids();

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

	this->spaceShip = SpaceShip(this->videoMode.width, this->videoMode.height);

	if (!this->spriteTexture.loadFromFile("..\\Images\\Ship\\SpaceShip.png"))
	{
		std::cout << "Failed Load Texture\n";

		this->renderWindow->close();
	}

	this->spaceShip.body.setTexture(this->spriteTexture);
	this->spaceShip.body.setOrigin(Vector2f(static_cast<float>(this->spriteTexture.getSize().x / 2), static_cast<float>(this->spriteTexture.getSize().y / 2)));
	this->spaceShip.body.setRotation(90);

}

Game::~Game()
{
	delete this->renderWindow;
}

