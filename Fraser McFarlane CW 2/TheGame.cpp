#include "TheGame.h"


LPCSTR sounds[3] = {"res/throw.wav", "res/hitenemy.wav", "res/thememusic.wav"};
LPCSTR fonts[1] = { "res/doctor_who.ttf" };

TheGame::TheGame()
{
	InitObjects();
	SetTransforms();

}


TheGame::~TheGame()
{
}

void TheGame::InitObjects()
{
	mInputMgr = InputManager::getInstance();
	theSoundManager = SoundManager::getInstance();
	theFontManager = FontManager::getInstance();

	display = new SDLDisplay(WIDTH, HEIGHT, "HEllo");
	
	robot = new ModelManager("res/R01.obj");
	bomb = new ModelManager("res/Bob.obj");
	enemy = new ModelManager("res/Alien.obj");
	ship = new ModelManager("res/Sample_Ship.obj");
	ground = new ModelManager("res/desert.obj");

	shader = new ShaderManager("res/lightShader");

	textureRobot = new TextureManager("res/R1.jpg");
	textureBomb = new TextureManager("res/RobotBad.jpg");
	textureAlien = new TextureManager("res/Alien.jpg");
	textureShip = new TextureManager("res/sh3.jpg");
	textureDesert = new TextureManager("res/sand.jpg");

	camera = new Camera(cameraTransform.GetPos(), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	theSoundManager->add("Throw", sounds[0]);
	theSoundManager->add("Hit", sounds[1]);
	theSoundManager->add("Music", sounds[2]);

	theFontManager->addFont("DrWho", fonts[0], 48);



}

void TheGame::SetTransforms()
{
	transformBomb.SetScale(glm::vec3(5, 5, 5));

	transformShip.SetScale(glm::vec3(80, 80, 80));
	transformShip.GetPos().y = 15.0f;

	transformGround.SetScale(glm::vec3(10, 2, 10));

}
void TheGame::RunGame()
{
	theSoundManager->getSnd("Music")->playAudio(AL_LOOPING);

	//while the display is not closed
	while (!display->IsClosed())
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		display->setMVP(WIDTH, HEIGHT);
		mInputMgr->UpdateInput(); //update manager
		UpdateAndRender();
		CheckCollisions();


		/*
		Test For Controller
		*/
		while (SDL_PollEvent(&evt) != 0)
		{
			if (evt.type == SDL_JOYAXISMOTION)
			{
				if (evt.jaxis.axis == 0)
				{
					std::cout << evt.jaxis.value << std::endl;
				}
			}
		}

		//perform transform to camera  from WASD
		if (mInputMgr->isKeyDown(SDL_SCANCODE_W))
		{
			cameraTransform.GetPos().z += 0.5f;
		}
		if (mInputMgr->isKeyDown(SDL_SCANCODE_S))
		{
			cameraTransform.GetPos().z -= 0.5f;
		}
		if (mInputMgr->isKeyDown(SDL_SCANCODE_A))
		{
			cameraTransform.GetPos().x += 0.5f;
		}
		if (mInputMgr->isKeyDown(SDL_SCANCODE_D))
		{
			cameraTransform.GetPos().x -= 0.5f;
		}
		//Rotate player with Q and E
		if (mInputMgr->isKeyDown(SDL_SCANCODE_Q))
		{
			transformRobot.GetRot().y += 0.1f;
		}
		if (mInputMgr->isKeyDown(SDL_SCANCODE_E))
		{
			transformRobot.GetRot().y -= 0.1f;
		}

		//Fire bomb
		if (mInputMgr->isKeyDown(SDL_SCANCODE_SPACE))
		{
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
		if (mInputMgr->isKeyDown(SDL_SCANCODE_TAB))
		{
			begin = true;
			waveNo = 1;
		
		}

		if (mInputMgr->isKeyDown(SDL_SCANCODE_C))
		{
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

		if (mInputMgr->isKeyDown(SDL_SCANCODE_M))
		{
			if (theSoundManager->mute == false)
			{
				theSoundManager->mute = true;
			}
			else
			{
				theSoundManager->mute = false;

			}
		}

		if (mInputMgr->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			SDL_Quit();
		}


		//display colour set to WHite
		display->ClearDisplayColour(0.0f, 0.0f, 0.5f, 1.0f);

	}
}

void TheGame::CheckCollisions()
{
	//COLLISION DETECTION
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

	for (vector<Enemy*>::iterator enemyIterator = thEnemies.begin(); enemyIterator != thEnemies.end(); ++enemyIterator)
	{
		if ((*enemyIterator)->SphereCollision(transformRobot.GetPos(), 2.5f))
		{
			(*enemyIterator)->isActive = false;
			theSoundManager->getSnd("Hit")->playAudio(AL_TRUE);
			health -= 35;
			cout << health << endl;
		}
		
	}
	
}

void TheGame::UpdateAndRender()
{
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
	shader->Update(transformRobot, currentCam);
	textureRobot->BindTexture(0);
	robot->DrawMesh();

	shader->BindShader();
	shader->Update(transformShip, currentCam);
	textureShip->BindTexture(0);
	ship->DrawMesh();

	shader->BindShader();
	shader->Update(transformGround, currentCam);
	textureDesert->BindTexture(0);
	ground->DrawMesh();

	if (begin)
	{
		if (waveStarted)
		{
			waveStarted = false;
			waveNo++;
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

	if (health <= 0)
	{
		cout << "GAME OVER" << endl;
		cout << "You survived until wave " << waveNo << flush << endl;
		display->~SDLDisplay();
	}


	glEnd();
	glPushMatrix();
	display->setOrthographicProj(WIDTH, HEIGHT);
	theFontManager->getFont("DrWho")->printText("Hello World", FTPoint(10.0f, 35.0f, 0.0f), colour3f(225.0f, 0.0f, 0.0f));
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);


	//Swap the buffer for a window
	display->SwapBuffers();

	//increase counter
	//counter += 0.01f;
}
