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
	while (this->renderWindow->pollEvent(this->event))
	{
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			this->spaceShip.body.move(1.f * cos(this->rotation * M_PI / 180), 1.f * sin(this->rotation * M_PI / 180));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->spaceShip.body.rotate(-5);
			this->rotation -= 5;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->spaceShip.body.rotate(5);
			this->rotation += 5;

		}
	}
}

void Game::validateSpeed()
{
	
}

//public func

void Game::update()
{
	this->handleEvents();
}

void Game::render()
{
	this->renderWindow->clear(sf::Color::Black);

	//this->validateSpeed();

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
	this->spaceShip.body.setRotation(90);
}

Game::~Game()
{
	delete this->renderWindow;
}
