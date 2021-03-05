#include "Bullet.h"

//Constr & Destr

Bullet::Bullet(Vector2f startPos, float rotation)
{
	this->bullet = CircleShape(3.f);
	this->bullet.setPosition(startPos);
	this->bullet.setFillColor(sf::Color::Red);
	this->bullet.setOrigin(this->bullet.getRadius(), this->bullet.getRadius());

	this->speed = Vector2f(5.f, 5.f);
	this->damage = 20;
	this->angle = rotation;
}

Bullet::~Bullet()
{

}