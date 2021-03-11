#pragma once

#include "Includes.h"

class SpaceShip
{
private:

	//private variables
	Vector2f speed;
	int health = 0;

public:

	//public variables
	Sprite body;

	//getters & setters
	void setSpeed(Vector2f speed);
	Vector2f getSpeed();
	void setHealth(int health);
	int getHealth();

	//constr & destr
	SpaceShip() = default;
	SpaceShip(const int windowWidth, const int windowHeight);
	~SpaceShip();
};

