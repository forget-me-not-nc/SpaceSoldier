#pragma once

#define _USE_MATH_DEFINES

#include "Includes.h"
#include "AdditionalMethods.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "GameStates.h"
#include "Player.h"

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

	//navigation
	Text returnToMainMenuText;
	Text startGameText;
	Text exitGameText;
	Text gameOverText;
	Text creatingPlayerText;

	int rotation;
	int totalPoints;

	Player player;

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

	void loadTextures();

	void updateHpBar();
	void updatePoints();

	void restartGame();

public:
	
	//public variables
	bool noRedraw;
	//game state
	GameStates gameState;

	//accessorss

	//public func
	void displayStartMenu(bool startGameHover, bool exitGameHover);
	void gameOver(bool gameOverHover, bool returnHover);
	void createPlayer();

	void update();
	void render();
	bool isRunning();

	//constr & destr
	Game();
	~Game();
};
