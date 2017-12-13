#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "Model.h"

class Enemy : public Model
{
public:
	Enemy();

	void randomise();
	virtual void update(float elapsedTime);

	~Enemy();

private:
	const float m_EnemyMinSpeed = 3.0f;
	const float m_EnemyMaxSpeed = 10.0f;
	const float m_EnemySpeedAdjustment = 2.5f;

};
#endif