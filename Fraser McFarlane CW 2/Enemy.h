#pragma once
#include "transform.h"
#include "Constants.h"

class Enemy
{
public:
	Enemy(vec3 position); // constructor takes in position
	~Enemy(); //destructor
	void update(); //update function


	Transform enemyTrans;	//public transform
	bool isActive = false;

	bool SphereCollision(vec3 mdlPos, float mdlRadius); // collision method 
	float CalcLengthSQRD(vec3(mdlLength)); // calculates the length squared

	float speed = 0.15f;
};

