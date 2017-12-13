#include "Enemy.h"

Enemy::Enemy() : Model()
{
	
}

void Enemy::randomise()
{
	if (rand() % 2 == 0)
	{
		Model::m_mdlPosition.x = -PLAYFIELDX;
	}
	else
	{
		Model::m_mdlPosition.x = PLAYFIELDX;
	}
	Model::m_mdlPosition.y = 0.0f;
	Model::m_mdlPosition.z = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	Model::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;
	Model::m_mdlDirection.x = -(float)glm::sin(Model::m_mdlRotation);
	Model::m_mdlDirection.z = (float)glm::cos(Model::m_mdlRotation);
	Model::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;
	Model::m_IsActive = true;
}

void Enemy::update(float elapsedTime)
{
	Model::m_mdlPosition += Model::m_mdlDirection * Model::m_mdlSpeed * elapsedTime;
	if (Model::m_mdlPosition.x > PLAYFIELDX)
		Model::m_mdlPosition.x -= 2 * PLAYFIELDX;
	if (Model::m_mdlPosition.x < -PLAYFIELDX)
		Model::m_mdlPosition.x += 2 * PLAYFIELDX;
	if (Model::m_mdlPosition.z > PLAYFIELDZ)
		Model::m_mdlPosition.z -= 2 * PLAYFIELDZ;
	if (Model::m_mdlPosition.z < -PLAYFIELDZ)
		Model::m_mdlPosition.z += 2 * PLAYFIELDZ;
}

Enemy::~Enemy()
{

}

