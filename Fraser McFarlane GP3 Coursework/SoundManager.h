/*
==========================================================================
SoundManager.h
==========================================================================
*/

#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "Sound.h"


using namespace std;

class SoundManager
{
private:
	static SoundManager* pInstance;
	ALCcontext *m_OALContext;
	ALCdevice *m_OALDevice;

protected:
	SoundManager();
	~SoundManager();
	map <LPCSTR, Sound*> gameSnds;
	void createContext();

public:
	void add(LPCSTR sndName, LPCSTR fileName);
	Sound* getSnd(LPCSTR sndName);
	void deleteSnd();
	static SoundManager* getInstance();
};
#endif