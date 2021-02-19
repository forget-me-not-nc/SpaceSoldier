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

	//private func
	void initWindow();
	void handleEvents();

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

