#pragma once


#include "Constants.h"
#include "SDLDisplay.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "transform.h"
#include "camera.h"
#include "inputManager.h"
#include "Bomb.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "Light.h"
#include "Player.h"


class TheGame
{
public:
	TheGame();
	~TheGame();
	void RunGame();	//running the game code


private:

	void InitObjects();	//initialise game objects
	void SetTransforms();	//set transforms
	void UpdateAndRender();	//updating and rendering
	void CheckCollisions();	//collision checks
	
	//manager instances 
	InputManager* theInputManager;
	SoundManager* theSoundManager;
	FontManager* theFontManager;

	SDLDisplay* display;	//display

	//game vector arrays
	vector<Bomb*> theBombs;
	vector<Enemy*> thEnemies;

	//models
	ModelManager* robot;
	ModelManager* bomb;
	ModelManager* enemy;
	ModelManager* ship;
	ModelManager* ground;

	//shaders
	ShaderManager* shader;
	ShaderManager* shader2;

	//textures
	TextureManager* textureRobot;
	TextureManager* textureBomb;
	TextureManager* textureAlien;
	TextureManager* textureShip;
	TextureManager* textureDesert;

	//camera trans
	Transform cameraTransform = glm::vec3(-50, 20, -400);
	Transform camera2Transform = glm::vec3(0, 20, 0);

	//object trans
	Transform transformBomb = glm::vec3(0, 20, 5);
	Transform transformRobot = glm::vec3(-50, 0, -400);
	Transform transoformAlien = glm::vec3(0, 0, 20);
	Transform transformShip = glm::vec3(0, 0, -450);
	Transform transformGround = glm::vec3(0, -20, 0);

	//cameras
	Camera* camera;
	Camera* camera2;
	Camera* currentCam;

	//lights
	Light phongLight;


	//offset spawning
	int offset = 0;
	int xpos = 0;

	//bool for toggles
	bool bombFired = false;
	bool camSwitch = false;
	bool thirdP = true;

	//wave variables
	bool begin = false;
	int waveNo = 0;
	int enemiesAlive;
	int spawnCount = 5;
	bool waveStarted = true;

	//timers and delays
	float timer = 0;
	float fireDelay = 1.0f;
	float camTimer = 0;

	//health for player
	int health = 100;



};

