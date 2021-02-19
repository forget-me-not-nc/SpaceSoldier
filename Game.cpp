#include "Game.h"

//private func

void Game::initWindow()
{
	this->videoMode = VideoMode(1000, 800);

	this->renderWindow = new RenderWindow(this->videoMode, "Space Soldier", sf::Style::Titlebar | sf::Style::Close);
}

void Game::handleEvents()
{
	while (this->renderWindow->pollEvent(this->event))
	{
		this->mousePos = static_cast<Vector2f>(sf::Mouse::getPosition(*this->renderWindow));

		switch (this->event.type)
		{
			case sf::Event::Closed:
			{
				cout << "Closing window...\n";

				this->renderWindow->close();

				break;
			}
			case sf::Event::MouseMoved:
			{
				Vector2f difference = mousePos - this->spaceShip.body.getPosition();			

				this->spaceShip.body.setRotation((atan2(difference.y, difference.x) * 180.f / 3.14159265f) + 90);

				break;
			}


			default: break;
		}
	}
}

void Game::validateSpeed()
{
	this->distanceToMouse = sqrt(pow(mousePos.x - this->spaceShip.body.getPosition().x, 2) + pow(mousePos.y - this->spaceShip.body.getPosition().y, 2));

	if (this->distanceToMouse >= 10)
	{
		this->spaceShip.setSpeed(Vector2f(this->distanceToMouse * 0.00055f, this->distanceToMouse * 0.00055f));
		this->movingVector = this->mousePos - this->spaceShip.body.getPosition();

		if (this->movingVector.x < 0)
		{
			if(this->spaceShip.getSpeed().x > 0) this->spaceShip.setSpeed(Vector2f(this->spaceShip.getSpeed().x * -1, this->spaceShip.getSpeed().y));
		}
		else if(this->movingVector.x > 0)
		{
			if (this->spaceShip.getSpeed().x < 0) this->spaceShip.setSpeed(Vector2f(this->spaceShip.getSpeed().x * -1, this->spaceShip.getSpeed().y));
		}

		if (this->movingVector.y < 0)
		{
			if (this->spaceShip.getSpeed().y > 0) this->spaceShip.setSpeed(Vector2f(this->spaceShip.getSpeed().x, this->spaceShip.getSpeed().y * -1));
		}
		else if(this->movingVector.y > 0)
		{
			if (this->spaceShip.getSpeed().y < 0) this->spaceShip.setSpeed(Vector2f(this->spaceShip.getSpeed().x, this->spaceShip.getSpeed().y * -1));
		}
		this->spaceShip.body.move(this->spaceShip.getSpeed());
	}
}

//public func

void Game::update()
{
	this->handleEvents();
}

void Game::render()
{
	this->renderWindow->clear(sf::Color::Black);

	this->validateSpeed();

	//redraw
	this->renderWindow->draw(this->spaceShip.body);

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

	if (!this->spriteTexture.loadFromFile("..\\SpaceShip.png"))
	{
		std::cout << "Failed Load Texture\n";

		this->renderWindow->close();
	}

	this->spaceShip.body.setTexture(this->spriteTexture);
	this->spaceShip.body.setOrigin(Vector2f(static_cast<float>(this->spriteTexture.getSize().x / 2), static_cast<float>(this->spriteTexture.getSize().y / 2)));

	this->distanceToMouse = 0;
	this->mousePos = Vector2f(0.f, 0.f);
}

Game::~Game()
{
	delete this->renderWindow;
}
