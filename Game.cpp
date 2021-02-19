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

	this->renderWindow->draw(this->spaceShip.getBody());

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
}

Game::~Game()
{
	delete this->renderWindow;
}
