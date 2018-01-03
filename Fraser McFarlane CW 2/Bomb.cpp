#include "Bomb.h"


Bomb::Bomb(Transform playerTrans)
{
	//sets scale and position on instantiation
	bombTrans.SetScale(vec3(5, 5, 5));
	//bombTrans.SetPos(playerTrans.GetPos());
	bombTrans.SetPos(vec3(playerTrans.GetPos().x, playerTrans.GetPos().y + 6.0f, playerTrans.GetPos().z + 4.0f));

}

void Bomb::update()
{
	bombTrans.GetPos().z += 0.5f; //moves down the z axis 
}
Bomb::~Bomb()
{
}
