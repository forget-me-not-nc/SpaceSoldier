#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

using sf::Sprite;
using sf::Texture;
using sf::Vector2f;

using std::string;
using std::vector;

struct Asteroid
{
public:
	Sprite meteorite;
	Vector2f speed;
	int damage = 0;

	Asteroid(sf::RenderWindow* window);
	~Asteroid();
};