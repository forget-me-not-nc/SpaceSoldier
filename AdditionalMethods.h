#pragma once

#include "Includes.h"

/////////////////
//check for Mouse pos accordint to navigation text
/////////////////
extern bool isMouseInTextRegion(Vector2i mousePos, Text& text);

/////////////////
//check for bullet and asteroid intersection
/////////////////
extern bool bulletAndAsteroidIntersect(const Sprite& asteroid, const CircleShape& bullet);

/////////////////
//check for ship and asteroid intersection
/////////////////
extern bool shipAndAsteroidIntersect(const Sprite& asteroid, const Sprite& spaceShip);

/////////////////
//convert string to bin before write to file
/////////////////
extern string stringToBin(string& line);

/////////////////
//convert from bin to string while read from file
/////////////////
extern string binToString(string& line);
