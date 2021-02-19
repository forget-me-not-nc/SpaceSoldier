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
				Vector2f mousePos = static_cast<Vector2f>(sf::Mouse::getPosition(*this->renderWindow));

				Vector2f difference = mousePos - this->spaceShip.body.getPosition();			

				this->spaceShip.body.setRotation((atan2(difference.y, difference.x) * 180.f / 3.14159265f) + 90);

				break;
			}


			default: break;
		}
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
}

Game::~Game()
{
	delete this->renderWindow;
}
