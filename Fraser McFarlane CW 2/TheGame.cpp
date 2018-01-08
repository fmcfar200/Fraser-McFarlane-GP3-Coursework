#include "TheGame.h"


LPCSTR sounds[3] = {"res/throw.wav", "res/hitenemy.wav", "res/thememusic.wav"};
LPCSTR fonts[1] = { "res/doctor_who.ttf" };


TheGame::TheGame()
{
	//object and transforms are initalised
	InitObjects();
	SetTransforms();

}


TheGame::~TheGame()
{
}

void TheGame::InitObjects()
{
	//instamces recieved
	theInputManager = InputManager::getInstance();
	theSoundManager = SoundManager::getInstance();
	theFontManager = FontManager::getInstance();

	display = new SDLDisplay(WIDTH, HEIGHT, "HEllo");	//display is constructed

	//models are created
	robot = new ModelManager("res/R01.obj");
	bomb = new ModelManager("res/Bob.obj");
	enemy = new ModelManager("res/Alien.obj");
	ship = new ModelManager("res/Sample_Ship.obj");
	ground = new ModelManager("res/desert.obj");

	//shders are created
	shader = new ShaderManager("res/phongShader");
	shader2 = new ShaderManager("res/basicShader");

	//textures are created
	textureRobot = new TextureManager("res/R1.jpg");
	textureBomb = new TextureManager("res/RobotBad.jpg");
	textureAlien = new TextureManager("res/Alien.jpg");
	textureShip = new TextureManager("res/sh3.jpg");
	textureDesert = new TextureManager("res/sand.jpg");

	//camera initialsed
	camera = new Camera(cameraTransform.GetPos(), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	
	//sounds added
	theSoundManager->add("Throw", sounds[0]);
	theSoundManager->add("Hit", sounds[1]);
	theSoundManager->add("Music", sounds[2]);

	//font added (BROKEN)
	theFontManager->addFont("DrWho", fonts[0], 48);



}

void TheGame::SetTransforms()
{
	//transforms are set for scaling and positioning
	transformBomb.SetScale(glm::vec3(5, 5, 5));

	transformShip.SetScale(glm::vec3(80, 80, 80));
	transformShip.GetPos().y = 15.0f;

	transformGround.SetScale(glm::vec3(10, 2, 10));

}
void TheGame::RunGame()
{
	theSoundManager->getSnd("Music")->playAudio(AL_LOOPING);	//music is played

	
	glPopMatrix();
	//while the display is not closed
	while (!display->IsClosed())
	{
		
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//Broken font code
		glPushMatrix();
		display->setOrthographicProj(WIDTH, HEIGHT);
		//LPCSTR temphealth = health.c_str();
		theFontManager->getFont("DrWho")->printText("Health: ", FTPoint(10.0f, 35.0f, 0.0f), colour3f(225.0f, 0.0f, 0.0f));
		glPopMatrix();

		display->setMVP(WIDTH, HEIGHT);
		UpdateAndRender();	//update and render
		theInputManager->CheckEvents(transformRobot, currentCam);	//check for input events
		CheckCollisions();
		theInputManager->UpdateInput(); //update manager

		

		/*
		controller code 
		*/
		if (theInputManager->leftMove)
		{
			cameraTransform.GetPos().x += 0.5f;

		}
		else if (theInputManager->rightmove)
		{
			cameraTransform.GetPos().x -= 0.5f;

		}
		else if (theInputManager->upmove)
		{
			cameraTransform.GetPos().z -= 0.5f;

		}
		else if (theInputManager->downmove)
		{
			cameraTransform.GetPos().z += 0.5f;

		}
		
		//perform transform to camera  from WASD
		if (theInputManager->isKeyDown(SDL_SCANCODE_W))
		{
			cameraTransform.GetPos().z += 0.5f;
		}
		if (theInputManager->isKeyDown(SDL_SCANCODE_S))
		{
			cameraTransform.GetPos().z -= 0.5f;
		}
		if (theInputManager->isKeyDown(SDL_SCANCODE_A))
		{
			cameraTransform.GetPos().x += 0.5f;
		}
		if (theInputManager->isKeyDown(SDL_SCANCODE_D))
		{
			cameraTransform.GetPos().x -= 0.5f;
		}
		//Rotate player with Q and E
		if (theInputManager->isKeyDown(SDL_SCANCODE_Q))
		{
			transformRobot.GetRot().y += 0.1f;
		}
		if (theInputManager->isKeyDown(SDL_SCANCODE_E))
		{
			transformRobot.GetRot().y -= 0.1f;
		}

		//Fire bomb
		if (theInputManager->isKeyDown(SDL_SCANCODE_SPACE) || theInputManager->fire)
		{
			theInputManager->fire = false;

			if (!bombFired)
			{
				theBombs.push_back(new Bomb(transformRobot));
				int numBombs = theBombs.size() - 1;
				theBombs[numBombs]->isActive = true;
				theSoundManager->getSnd("Throw")->playAudio(AL_TRUE);

				bombFired = true;
				timer = fireDelay;

			}
		}
		else if (timer > 0)
		{
			timer -= 0.1f;
		}
		else
		{
			bombFired = false;
		}

		//Init enemies 
		if (theInputManager->isKeyDown(SDL_SCANCODE_TAB) || theInputManager->start)
		{
			if (begin == false)
			{
				begin = true;
				//waveNo++;
			}
		}

		//camera switch
		if (theInputManager->isKeyDown(SDL_SCANCODE_C) || theInputManager->camswitch)
		{
			theInputManager->camswitch = false;
			Transform tempTrans = cameraTransform.GetPos();
			if (!camSwitch)
			{
				if (thirdP)
				{

					thirdP = false;

				}
				else
				{
					thirdP = true;

				}
				camSwitch = true;
				camTimer = fireDelay;
			}
		}
		else if (camTimer > 0)
		{
			camTimer -= 0.1f;

		}
		else
		{
			camSwitch = false;
		}

		//mute toggle
		if (theInputManager->isKeyDown(SDL_SCANCODE_M) || theInputManager->mute)
		{
			theInputManager->mute = false;
			if (theSoundManager->mute == false)
			{
				theSoundManager->mute = true;
			}
			else
			{
				theSoundManager->mute = false;

			}
		}

		//quit
		if (theInputManager->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			SDL_Quit();
		}
		

		//display colour set to WHite
		display->ClearDisplayColour(0.0f, 0.0f, 0.5f, 1.0f);

		cout << "Health: " << health <<"	" << "Wave: " << waveNo << endl;


	}

}

void TheGame::CheckCollisions()
{
	//COLLISION DETECTION

	//hit between bomb and enemy
	for (vector<Bomb*>::iterator bombIterartor = theBombs.begin(); bombIterartor != theBombs.end(); ++bombIterartor)
	{
		(*bombIterartor)->update();
		for (vector<Enemy*>::iterator enemyIterator = thEnemies.begin(); enemyIterator != thEnemies.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereCollision((*bombIterartor)->bombTrans.GetPos(), 2.5f))
			{
				(*enemyIterator)->isActive = false;
				(*bombIterartor)->isActive = false;
				theSoundManager->getSnd("Hit")->playAudio(AL_TRUE);
			}
		}
	}

	//hit between enemy and player
	for (vector<Enemy*>::iterator enemyIterator = thEnemies.begin(); enemyIterator != thEnemies.end(); ++enemyIterator)
	{
		if ((*enemyIterator)->SphereCollision(transformRobot.GetPos(), 2.5f))
		{
			(*enemyIterator)->isActive = false;
			theSoundManager->getSnd("Hit")->playAudio(AL_TRUE);
			health -= 35;
			system("CLS");

		}
		
	}
	
}

void TheGame::UpdateAndRender()
{
	
	//camera reinitialised
	Camera camera(cameraTransform.GetPos(), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Camera camera2(camera2Transform.GetPos(), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Camera currentCam;

	if (thirdP)
	{
		currentCam = camera;
	}
	else
	{
		currentCam = camera2;
		//currentCam.Rotation();
	}

	//Set transform of first object
	transformRobot.SetScale(glm::vec3(1, 1, 1));
	transformRobot.GetPos().x = cameraTransform.GetPos().x;
	transformRobot.GetPos().z = cameraTransform.GetPos().z;


	transformRobot.GetPos().z += 20.0f;
	transformRobot.GetPos().x += 10.0f;
	transformRobot.GetPos().y = 10.0f;


	camera2Transform.SetPos(glm::vec3(transformRobot.GetPos().x,
		transformRobot.GetPos().y + 6.0f, transformRobot.GetPos().z + 2.0f));


	//bind and update shader, bind texture and draw the mesh
	shader->BindShader();
	shader->Update(transformRobot, currentCam, phongLight);
	textureRobot->BindTexture(0);
	robot->DrawMesh();


	shader->BindShader();
	shader->Update(transformShip, currentCam,phongLight);
	textureShip->BindTexture(0);
	ship->DrawMesh();

	shader2->BindShader();
	shader2->Update(transformGround, currentCam);
	textureDesert->BindTexture(0);
	ground->DrawMesh();

	//wave code
	if (begin)
	{
		//if started
		if (waveStarted)
		{
			system("CLS");
			waveStarted = false;
			waveNo++;
			//spawn enemies
			for (int i = 0; i < spawnCount; i++)
			{
				thEnemies.push_back(new Enemy(vec3((rand() % 250) - 100 , 0, rand()% 100 + 250)));
				thEnemies[i]->speed += (float)(rand() % 5 + 2) / 10;
				thEnemies[i]->isActive = true;
				enemiesAlive++;
				offset += 50;
			}
		
		}
		else
		{
			//reset 
			if (enemiesAlive <= 0)
			{
				thEnemies.clear();
				offset = 0;
				spawnCount += rand() % 3 + 1;
				if (spawnCount >= 25)
				{
					spawnCount = 25;
				}
				waveStarted = true;
			}
		}

		
	}

	//Iterate enemies and draw if they are active
	for (vector<Enemy*>::iterator enemyIter = thEnemies.begin(); enemyIter != thEnemies.end(); enemyIter++)
	{
		if ((*enemyIter)->isActive)
		{
			(*enemyIter)->update();
			shader->BindShader();
			shader->Update((*enemyIter)->enemyTrans, currentCam);
			textureAlien->BindTexture(0);
			enemy->DrawMesh();
		}
	}

	//iterate through bombs and draw if active 
	for (vector<Bomb*>::iterator bombiter = theBombs.begin(); bombiter != theBombs.end(); bombiter++)
	{
		if ((*bombiter)->isActive)
		{
			(*bombiter)->update();
			shader->BindShader();
			shader->Update((*bombiter)->bombTrans, currentCam);
			textureBomb->BindTexture(0);
			bomb->DrawMesh();
		}
	}

	

	//erase bombs from vector if they are set to false
	vector<Bomb*>::iterator bombIter = theBombs.begin();
	while (bombIter != theBombs.end())
	{
		if ((*bombIter)->isActive == false)
		{
			bombIter = theBombs.erase(bombIter);
		}
		else
		{
			bombIter++;
		}
	}

	//erase enemies if they are false
	vector<Enemy*>::iterator enemyIterartor = thEnemies.begin();
	while (enemyIterartor != thEnemies.end())
	{
		if ((*enemyIterartor)->enemyTrans.GetPos().z <= -500)
		{
			health -= 20;
			system("CLS");

			(*enemyIterartor)->isActive = false;
		}

		if ((*enemyIterartor)->isActive == false)
		{
			enemiesAlive--;
			enemyIterartor = thEnemies.erase(enemyIterartor);
		}
		else
		{
			enemyIterartor++;
		}
	}

	//if game over then display stuff in console
	if (health <= 0)
	{

		cout << "GAME OVER" << endl;
		cout << "You survived until wave " << waveNo << flush << endl;
		system("CLS");
		display->~SDLDisplay();
	}


	glEnd();
	


	//Swap the buffer for a window
	display->SwapBuffers();

}
