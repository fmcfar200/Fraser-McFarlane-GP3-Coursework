#ifndef _Laser_H
#define _Laser_H

#include "GameConstants.h"
#include "Model.h"

class Laser : public Model
{
public:
	Laser();

	virtual void update(float elapsedTime);

	~Laser();

};
#endif