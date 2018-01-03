#pragma once
#include "transform.h"
#include "TextureManager.h"
#include "ModelManager.h"

class Bomb
{
public:
	Bomb(Transform playerTrans); //constructor

	void update();	//update per frame
	~Bomb();	//destructor

	bool isActive = false;	//active boolean for rendering and updating
	Transform bombTrans;	//transform
};

