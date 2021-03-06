#pragma once

#include "AdditionalMethods.h"

extern bool isMouseInTextRegion(Vector2i mousePos, Text& text)
{	
	return (mousePos.x >= text.getPosition().x &&
		mousePos.x <= (text.getPosition().x + text.getGlobalBounds().width) &&
		mousePos.y >= text.getPosition().y &&
		mousePos.y <= (text.getPosition().y + text.getGlobalBounds().height));	
}

extern bool bulletAndAsteroidIntersect(const Sprite& asteroid, const CircleShape& bullet)
{
	float dX = asteroid.getPosition().x - bullet.getPosition().x;
	float dY = asteroid.getPosition().y - bullet.getPosition().y;

	float spriteRadius = static_cast<float>((asteroid.getTexture()->getSize().x + asteroid.getTexture()->getSize().y) / 4);

	return sqrt(dX * dX + dY * dY) <= (spriteRadius + bullet.getRadius());
}

extern bool shipAndAsteroidIntersect(const Sprite& asteroid, const Sprite& spaceShip)
{
	float dX = asteroid.getPosition().x - spaceShip.getPosition().x;
	float dY = asteroid.getPosition().y - spaceShip.getPosition().y;

	float spriteRadius = static_cast<float>((asteroid.getTexture()->getSize().x + asteroid.getTexture()->getSize().y) / 4);
	float shipRadius = static_cast<float>((spaceShip.getTexture()->getSize().x + spaceShip.getTexture()->getSize().y) / 4);

	return sqrt(dX * dX + dY * dY) <= (spriteRadius + shipRadius);
}

string stringToBin(string& line)
{
	string result = "";

	for (string::iterator iter = line.begin(); iter != line.end();)
	{
		result += std::bitset<8>(*iter).to_string();

		++iter;
	}

	return result;
}

string binToString(string& line)
{
	string result = "";	
	string set = "";

	for (unsigned int i = 0; i < line.length();)
	{
		for (unsigned int j = i; j < i + 8; j++)
		{
			set += line[j];
		}

		i += 8;

		result += static_cast<char>(std::bitset<8>(set).to_ulong());

		set = "";
	}

	return result;
}
