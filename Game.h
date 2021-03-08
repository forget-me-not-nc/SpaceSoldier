#pragma once

#define _USE_MATH_DEFINES

#include <vector>

#include "SpaceShip.h"
#include "Asteroid.h"
#include "Bullet.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using sf::RenderWindow;
using sf::Window;
using sf::Event;
using sf::VideoMode;
using sf::Mouse;
using sf::Texture;
using sf::RectangleShape;
using sf::Font;
using sf::Text;

using std::cout;
using std::endl;

class Game
{
private:

	//private variables
	SpaceShip spaceShip;
	VideoMode videoMode;
	Event event;
	Texture spriteTexture;
	RenderWindow* renderWindow;
	Texture backgroundTexture;
	Sprite background;
	RectangleShape hpBarRect;
	Font textFont;

	int rotation;
	int totalPoints;
	bool isWin;

	//bullets vector
	vector<Bullet> bullets;

	//Asteroids vector
	vector<Asteroid> asteroids;

	//destroyed asteroids vector
	vector<Asteroid> destroyedAsteroids;

	//asteroid textures vector
	vector<Texture> asteroidTextures;

	//explosin textures
	vector<Texture> explosions;

	//private func
	void initWindow();
	void handleEvents();
	void validateSpeed();
	void validatePosition();

	void moveBullets();
	void drawBullets();
	void deleteBullets();

	void addAsteroids();
	void moveAsteroids();
	void drawAsteroids();
	void drawDestroyedAsteroids();
	void deleteAsteroids();

	void collisionCheck();
	bool bulletAndAsteroidIntersect(const Sprite &asteroid, const CircleShape &bullet);
	bool shipAndAsteroidIntersect(const Sprite &asteroid);

	void loadTextures();

	void updateHpBar();
	void updatePoints();

	void gameOver();

public:
	
	//public variables
	bool isPaused;
	bool isOver;

	//accessorss

	//public func
	void update();
	void render();
	bool isRunning();

	//constr & destr
	Game();
	~Game();
};
