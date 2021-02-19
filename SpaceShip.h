#pragma once

#define _USE_MATH_DEFINES

#include "SFML/Graphics.hpp"

#include <cmath>
#include <iostream>

using sf::Vector2f;
using sf::Sprite;

class SpaceShip
{
private:

	//private variables
	float speed;
	int health;

	//private func

public:

	//public variables
	Sprite body;

	//getters & setters
	void setSpeed(float speed);
	float getSpeed();
	void setHealth(int health);
	int getHealth();
	//public func

	//constr & destr
	SpaceShip() = default;
	SpaceShip(const int windowWidth, const int windowHeight);
	~SpaceShip();
};

