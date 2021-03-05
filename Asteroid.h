#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

using sf::Sprite;
using sf::Texture;
using sf::Vector2f;

using std::string;
using std::vector;

const vector<string> textures {
	"..\\Images\\Asteroid\\Asteroid1.png",
	"..\\Images\\Asteroid\\Asteroid2.png",
	"..\\Images\\Asteroid\\Asteroid3.png",
};

struct Asteroid
{
public:
	Sprite meteorite;
	Texture texture;
	Vector2f speed;
	int damage = 0;

	Asteroid(sf::RenderWindow* window);
	~Asteroid();
};