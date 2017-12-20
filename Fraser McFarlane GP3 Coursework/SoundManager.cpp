/*
==================================================================================
SoundManager.cpp
==================================================================================
*/

#include "SoundManager.h"

SoundManager* SoundManager::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
SoundManager::SoundManager()
{
	createContext();
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
SoundManager* SoundManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new SoundManager();
	}
	return SoundManager::pInstance;
}

void SoundManager::createContext()
{
	OALDevice = alcOpenDevice(NULL);
	if (OALDevice)
	{
		//Create a context
		OALContext = alcCreateContext(OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(OALContext);
	}
}

void SoundManager::add(LPCSTR sndName, LPCSTR fileName)
{
	if (!getSnd(sndName))
	{
		Sound * newSnd = new Sound();
		newSnd->loadWAVFile(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

Sound* SoundManager::getSnd(LPCSTR sndName)
{
	map<LPCSTR, Sound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}

void SoundManager::deleteSnd()
{
	for (map<LPCSTR, Sound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}


SoundManager::~SoundManager()
{
	OALContext = alcGetCurrentContext();

	//Get device for active context
	OALDevice = alcGetContextsDevice(OALContext);

	//Release context(s)
	alcDestroyContext(OALContext);

	//Close device
	alcCloseDevice(OALDevice);

}
