#pragma once

#include <iostream>

#include "SpaceShip.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using sf::RenderWindow;
using sf::Event;
using sf::VideoMode;

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

	//private func
	void initWindow();
	void handleEvents();

public:
	
	//public variables
	
	//public func
	void update();
	void render();
	bool isRunning();

	//constr & destr
	Game();
	~Game();
};

