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
			this->spaceShip.body.move(static_cast<float>(this->spaceShip.getSpeed().x * cos(this->rotation * M_PI / 180)),
									  static_cast<float>(this->spaceShip.getSpeed().y * sin(this->rotation * M_PI / 180)));

			cout << "Current Ship Pos--> x:" << this->spaceShip.body.getPosition().x << " y: " << this->spaceShip.body.getPosition().y << endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->spaceShip.body.rotate(-5);
			this->rotation -= 5;
			this->rotation = this->rotation % 360;

			this->spaceShip.body.move(static_cast<float>(this->spaceShip.getSpeed().x * cos(this->rotation / 1.3 * M_PI / 180)),
									  static_cast<float>(this->spaceShip.getSpeed().y * sin(this->rotation / 1.3 * M_PI / 180)));

			cout << "Current rotation: " << this->rotation << endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->spaceShip.body.rotate(5);
			this->rotation += 5;
			this->rotation = this->rotation % 360;

			this->spaceShip.body.move(static_cast<float>(this->spaceShip.getSpeed().x * cos(this->rotation / 1.3 * M_PI / 180)),
									  static_cast<float>(this->spaceShip.getSpeed().y * sin(this->rotation / 1.3 * M_PI / 180)));

			cout << "Current rotation: " << this->rotation << endl;
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
