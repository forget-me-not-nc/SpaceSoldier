#pragma once

#define _USE_MATH_DEFINES

#include "SpaceShip.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using sf::RenderWindow;
using sf::Window;
using sf::Event;
using sf::VideoMode;
using sf::Mouse;
using sf::Texture;

using std::cout;
using std::endl;

class Game
{
private:

	//private variables
	SpaceShip spaceShip;
	RenderWindow* renderWindow;
	VideoMode videoMode;
	Event event;
	Texture spriteTexture;

	int rotation = 0;
	const float maxSpeed = 8.f;
	const float acceleration = 0.5f;

	//private func
	void initWindow();
	void handleEvents();
	void validateSpeed();

public:
	
	//public variables
	
	//accessor

	//public func
	void update();
	void render();
	bool isRunning();

	//constr & destr
	Game();
	~Game();
};

