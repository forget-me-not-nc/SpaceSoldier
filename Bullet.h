#pragma once

#include "SFML/Graphics.hpp"

using sf::PrimitiveType;
using sf::CircleShape;
using sf::Vector2f;

struct Bullet
{
public:
	CircleShape bullet;
	Vector2f speed;
	float angle;
	int damage;
	bool isDestoyed;

	Bullet(Vector2f startPos, float rotation);
	~Bullet();
};