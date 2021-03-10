#pragma once

#include "Includes.h"

class Player
{
private:
	string name;
	int points;

public:
	Player() = default;
	Player(string name, int points);
	~Player();
};

