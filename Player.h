#pragma once

#include "Includes.h"

class Player
{
private:
	String name;
	int points = 0;

public:
	//accessors
	void setName(String Name);
	void setPoints(int points);

	String getName();
	int getPoints();

	//operators
	friend bool operator==(const Player& p1, const Player& p2);
	friend bool operator!=(const Player& p1, const Player& p2);
	Player operator=(const Player& player);

	//constr & destr
	Player() = default;
	Player(string name, int points);
	Player(const Player& player);
	~Player();
};

