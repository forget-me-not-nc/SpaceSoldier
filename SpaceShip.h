#pragma once

#include "SFML/Graphics.hpp"

using sf::VertexArray;
using sf::Transform;
using sf::Vector2f;

class SpaceShip
{
private:

	//private variables
	float speed;
	float rotationDegree;
	int health;

	Transform shipTransform;
	VertexArray body;

	//private func

public:

	//public variables

	//getters & setters
	void setSpeed(float speed);
	void setHealth(int health);
	void setRotationDegree(float rotationDegree);

	float getRotationDegree();
	float getSpeed();
	int getHealth();

	VertexArray getBody();

	//public func
	void transformShip(Vector2f offset = Vector2f(0.f,0.f), float degree = 0);
	void calculateRotationDegree(Vector2f mousePos);

	//constr & destr
	SpaceShip() = default;
	SpaceShip(const int windowWidth, const int windowHeight);
	~SpaceShip();
};

