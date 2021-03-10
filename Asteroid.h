#pragma once

#include "Includes.h"

struct Asteroid
{
public:
	Sprite meteorite;
	Vector2f speed;
	int damage;
	int health;
	int points;

	Asteroid(sf::RenderWindow* window);
	~Asteroid();
};