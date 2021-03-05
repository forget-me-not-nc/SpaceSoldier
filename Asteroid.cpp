#include "Asteroid.h"

//Constr & destr

Asteroid::Asteroid(sf::RenderWindow* window)
{
	if (!this->texture.loadFromFile("..\\Images\\Ship\\SpaceShip.png"))
	{
		std::cout << "Failed to load asteroid texture" << std::endl;
	}

	this->meteorite.setTexture(this->texture);
	this->meteorite.setOrigin(static_cast<float>(this->texture.getSize().x / 2), static_cast<float>(this->texture.getSize().y / 2));

	float offsetX = static_cast<float>((rand() % 10 + 1) * 0.5f);
	float offsetY = static_cast<float>((rand() % 10 + 1) * 0.5f);

	switch (rand() % 4)
	{
		case 0:
		{
			this->meteorite.setPosition(0.f, static_cast<float>(rand() % window->getSize().y));
			
			if ((rand() % 2) == 0) this->speed = Vector2f(offsetX, offsetY);
			else this->speed = Vector2f(offsetX, -offsetY);

			break;
		}

		case 1:
		{
			this->meteorite.setPosition(static_cast<float>(rand() % window->getSize().x), 0.f);

			if ((rand() % 2) == 0) this->speed = Vector2f(offsetX, offsetY);
			else this->speed = Vector2f(-offsetX, offsetY);

			break;
		}

		case 2:
		{
			this->meteorite.setPosition(static_cast<float>(window->getSize().x),
									    static_cast<float>(rand() % window->getSize().y));

			if ((rand() % 2) == 0) this->speed = Vector2f(-offsetX, offsetY);
			else this->speed = Vector2f(-offsetX, -offsetY);

			break;
		}

		default:
		{
			this->meteorite.setPosition(static_cast<float>(rand() % window->getSize().x),
									    static_cast<float>(window->getSize().y));

			if ((rand() % 2) == 0) this->speed = Vector2f(offsetX, -offsetY);
			else this->speed = Vector2f(-offsetX, -offsetY);

			break;
		}
	}
}

Asteroid::~Asteroid()
{

}
