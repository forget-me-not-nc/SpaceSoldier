#include "Asteroid.h"

/////////////////
//constr & destr
/////////////////

Asteroid::Asteroid(sf::RenderWindow* window)
{
	float offsetX = static_cast<float>((rand() % 8 + 1) * 0.5f);
	float offsetY = static_cast<float>((rand() % 8 + 1) * 0.5f);

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

	this->damage = rand() % 30 + 15;
	this->health = 100;
	this->points = rand() % 150 + 50;
}

Asteroid::~Asteroid()
{

}
