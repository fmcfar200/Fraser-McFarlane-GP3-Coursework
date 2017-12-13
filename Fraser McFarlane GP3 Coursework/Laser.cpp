#include "Laser.h"

Laser::Laser() : Model()
{

}

void Laser::update(float elapsedTime)
{
	Model::m_mdlPosition += Model::m_mdlDirection * Model::m_mdlSpeed * elapsedTime;
	if (Model::m_mdlPosition.x > PLAYFIELDX ||
		Model::m_mdlPosition.x < -PLAYFIELDX ||
		Model::m_mdlPosition.z > PLAYFIELDZ ||
		Model::m_mdlPosition.z < -PLAYFIELDZ)
		Model::m_IsActive = false;

}

Laser::~Laser()
{

}
