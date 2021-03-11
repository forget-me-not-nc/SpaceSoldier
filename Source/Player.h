#pragma once

#include "Includes.h"

class Player
{
private:

	//private variables
	String name;
	int points = 0;

public:

	//accessors (getters & setters)
	void setName(String name);
	void setPoints(int points);

	String getName();
	int getPoints();

	//operators overloading
	friend bool operator==(const Player& p1, const Player& p2);
	friend bool operator!=(const Player& p1, const Player& p2);
	Player& operator=(const Player& player);

	//constr & destr
	Player() = default;
	Player(string name, int points);
	Player(const Player& player);
	~Player();
};

