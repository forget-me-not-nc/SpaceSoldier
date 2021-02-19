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
	Vector2f speed;
	int health;

	//private func

public:

	//public variables
	Sprite body;

	//getters & setters
	void setSpeed(Vector2f speed);
	Vector2f getSpeed();
	void setHealth(int health);
	int getHealth();
	//public func

	//constr & destr
	SpaceShip() = default;
	SpaceShip(const int windowWidth, const int windowHeight);
	~SpaceShip();
};

