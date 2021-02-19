#include "SpaceShip.h"

//getters & setters

void SpaceShip::setSpeed(float speed)
{
	this->speed = speed;
}

void SpaceShip::setHealth(int health)
{
	this->health = health;
}

void SpaceShip::setRotationDegree(float rotationDegree)
{
	this->rotationDegree = rotationDegree;
}

float SpaceShip::getRotationDegree()
{
	return this->rotationDegree;
}

float SpaceShip::getSpeed()
{
	return this->speed;
}

int SpaceShip::getHealth()
{
	return this->health;
}

VertexArray SpaceShip::getBody()
{
	return this->body;
}

//public func

void SpaceShip::transformShip(Vector2f offset, float degree)
{
	this->shipTransform.translate(offset);
	this->shipTransform.rotate(degree);

	this->rotationDegree = degree;
	
	this->body[0].position = this->shipTransform.transformPoint(this->body[0].position);
	this->body[1].position = this->shipTransform.transformPoint(this->body[1].position);
	this->body[2].position = this->shipTransform.transformPoint(this->body[2].position);
}


void SpaceShip::calculateRotationDegree(Vector2f mousePos)
{
	Vector2f bodyOrigin;


}

//constr & destr

SpaceShip::SpaceShip(const int windowWidth, const int windowHeight)
{
	this->speed = 0;
	this->rotationDegree = 0;
	this->shipTransform.rotate(this->rotationDegree);
	this->shipTransform.translate(Vector2f(this->speed, this->speed));

	this->body = VertexArray(sf::Triangles, 3);

	this->body[0].position = Vector2f(static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2 - 20));
	this->body[1].position = Vector2f(static_cast<float>(windowWidth / 2 - 10), static_cast<float>(windowHeight / 2 + 20));
	this->body[2].position = Vector2f(static_cast<float>(windowWidth / 2 + 10), static_cast<float>(windowHeight / 2 + 20));

	this->body[0].color = sf::Color::White;
	this->body[1].color = sf::Color::Red;
	this->body[2].color = sf::Color::Red;

	this->health = 100;
}

SpaceShip::~SpaceShip()
{

}
