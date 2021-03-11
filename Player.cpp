#include "Player.h"

//accessors
void Player::setName(String name)
{
	this->name = name;
}

void Player::setPoints(int points)
{
	this->points = points;
;}

String Player::getName()
{
	return this->name;
}

int Player::getPoints()
{
	return this->points;
}

//operators
bool operator==(const Player& p1, const Player& p2)
{
	return (p1.name.toAnsiString()._Equal(p2.name.toAnsiString()));
}

bool operator!=(const Player& p1, const Player& p2)
{
	return (!p1.name.toAnsiString()._Equal(p2.name.toAnsiString()));
}

Player& Player::operator=(const Player& player)
{
	this->name = player.name;
	this->points = player.points;

	return *this;
}

//constr & destr
Player::Player(string name, int points)
{
	this->name = name;
	this->points = points;
}

Player::Player(const Player& player)
{
	this->name = player.name;
	this->points = player.points;
}

Player::~Player()
{
}
