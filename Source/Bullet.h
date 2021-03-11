#pragma once

#include "Includes.h"

struct Bullet
{
public:

	//public variables
	CircleShape bullet;
	Vector2f speed;
	float angle;
	int damage;
	bool isDestoyed;

	//constr & destr
	Bullet(Vector2f startPos, float rotation);
	~Bullet();
};
