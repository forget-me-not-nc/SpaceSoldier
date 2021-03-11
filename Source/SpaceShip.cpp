#include "SpaceShip.h"

/////////////////
//getters & setters
/////////////////

void SpaceShip::setSpeed(Vector2f speed)
{
	this->speed = speed;
}

Vector2f SpaceShip::getSpeed()
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

/////////////////
//constr & destr
/////////////////

SpaceShip::SpaceShip(const int windowWidth, const int windowHeight) 
{
	this->speed = Vector2f(5.f, 5.f);
	this->health = 200;

	this->body.setPosition(static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2));
}


SpaceShip::~SpaceShip()
{
	
}
