#ifndef _Player_H
#define _Player_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "Model.h"
#include "InputManager.h"

class Player : public Model
{
private:
	InputManager* m_InputMgr;
public:
	Player();
	void attachInputMgr(InputManager* inputMgr);
	virtual void update(float elapsedTime);

	~Player();
};
#endif