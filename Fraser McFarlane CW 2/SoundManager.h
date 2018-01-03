
#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

#include "Constants.h"

#include "Sound.h"


using namespace std;

class SoundManager
{
private:
	static SoundManager* pInstance;
	ALCcontext *OALContext;
	ALCdevice *OALDevice;

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
	bool mute = false;
};
#endif