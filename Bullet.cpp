#include "Bullet.h"

/////////////////
//Constr & Destr
/////////////////

Bullet::Bullet(Vector2f startPos, float rotation)
{
	this->bullet = CircleShape(4.f);

	this->bullet.setPosition(startPos);
	this->bullet.setFillColor(sf::Color::Red);
	this->bullet.setOrigin(this->bullet.getRadius(), this->bullet.getRadius());

	this->speed = Vector2f(10.f, 10.f);
	this->damage = rand() % 30 + 30;
	this->angle = rotation;
	this->isDestoyed = false;
}

Bullet::~Bullet()
{

}