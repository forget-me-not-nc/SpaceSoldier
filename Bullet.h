#pragma once

#include "Includes.h"

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