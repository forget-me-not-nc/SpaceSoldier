#pragma once

#include "Includes.h"

struct Asteroid
{
public:

	//public variables
	Sprite meteorite;
	Vector2f speed;
	int damage;
	int health;
	int points;

	//constr & destr
	Asteroid(sf::RenderWindow* window);
	~Asteroid();
};