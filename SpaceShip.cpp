#include "SpaceShip.h"

//private func

//public func

//getters & setters

void SpaceShip::setSpeed(float speed)
{
	this->speed = speed;
}

float SpaceShip::getSpeed()
{
	return this->speed;
}

void SpaceShip::setHealth(int health)
{
	this->health = health;
}

int SpaceShip::getHealth()
{
	return this->health;
}

//constr & destr

SpaceShip::SpaceShip(const int windowWidth, const int windowHeight) //ww
{
	this->speed = 0;
	this->health = 100;

	this->body.setPosition(static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2));
}


SpaceShip::~SpaceShip()
{
	
}
