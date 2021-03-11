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
	string currentDirectory; //for proper resources loading

	RenderWindow* renderWindow;
	VideoMode videoMode;

	SpaceShip spaceShip;
	Player player;

	Event event;

	Texture spriteTexture;
	Texture backgroundTexture;

	Sprite background;
	
	RectangleShape hpBarRect;
	RectangleShape inputRect;

	Font textFont;

	String nickname;

	//navigation
	Text returnToMainMenuText;
	Text startGameText;
	Text exitGameText;
	Text gameOverText;
	Text creatingPlayerText;
	Text playersName;
	Text leaderboard;
	Text hintText;

	int rotation;
	int totalPoints;

	bool ratingIsLoaded;
	bool ratingIsUpdated;

	//bullets vector
	vector<Bullet> bullets;

	//vector for rating
	vector<Player> rating;

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

	void initTexts();
	void changeHint();

	void loadRating();
	void updateRating();
	void showRating();

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
	GameStates gameState;

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
