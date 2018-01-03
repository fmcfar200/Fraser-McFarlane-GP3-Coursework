#include "Enemy.h"


Enemy::Enemy(vec3 position)
{
	enemyTrans.SetPos(position);
	enemyTrans.SetScale(vec3(2, 2, 2));
	enemyTrans.GetRot().y += 3.2;
}


Enemy::~Enemy()
{
}

void Enemy::update()
{
	enemyTrans.GetPos().z -= speed;
}

bool Enemy::SphereCollision(vec3 mdlPos, float mdlRadius)
{
	const float distanceSq = CalcLengthSQRD(enemyTrans.GetPos() - mdlPos);
	const float sumRadius = (17.5f + mdlRadius);

	if (distanceSq < sumRadius * sumRadius)
	{
		return true;
	}
	return false;
}

float Enemy::CalcLengthSQRD(vec3(mdlLength))
{
	return (mdlLength.x*mdlLength.x) + (mdlLength.y*mdlLength.y) + (mdlLength.z*mdlLength.z);
}

