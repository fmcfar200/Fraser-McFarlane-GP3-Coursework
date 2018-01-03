/*
==========================================================================
Sound.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "Sound.h"
using namespace std;

Sound::Sound()
{
	OALData = NULL;           //data for the buffer
	OALFrequency = 0;     //frequency
	OALBitRate = 0;		  // Bit Rate
	OALLength = 0;		  // Length
	OALBuffer = 0;         // Buffer

}

Sound::~Sound()
{
	cleanUp();
}

void Sound::loadWAVFile(LPCSTR filename)
{
	// Check for EAX 2.0 support
	OALbEAX = alIsExtensionPresent("EAX2.0");
	
	alGetError(); // clear error code

	//load the wave file
	alutLoadWAVFile((ALbyte *)filename, &OALFormat, (void **)&OALData, 
	(ALsizei *)&OALBufferLen, &OALFrequency, &alLoop);

	//create a source
	alGenSources(1, &OALSource);

	//create  buffer
	alGenBuffers(1, &OALBuffer);

	//put the data into our sampleset buffer
	alBufferData(OALBuffer, OALFormat, OALData, OALBufferLen, OALFrequency);

	//assign the buffer to this source
	alSourcei(OALSource, AL_BUFFER, OALBuffer);

	//release the data
	alutUnloadWAV(OALFormat, OALData, OALBufferLen, OALFrequency);
}

void Sound::LoadWAVInfo(ifstream &filename, string &name, 	unsigned int &size)
{
	char chunk[4];
	filename.read((char *)&chunk, 4);
	filename.read((char *)&size, 4);

	name = string(chunk, 4);
}

void Sound::playAudio(ALboolean sndLoop)
{
	alSourcei(OALSource, sndLoop, AL_TRUE);

	//play
	alSourcePlay(OALSource);

}

void Sound::stopAudio()
{
	//to stop
	alSourceStop(OALSource);
}

void Sound::cleanUp()
{
	int state;
	alGetSourcei(OALSource, AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
	{
		stopAudio();
	}

	alDeleteSources(1, &OALSource);

	//delete our buffer
	alDeleteBuffers(1, &OALBuffer);

	//Disable context
	alcMakeContextCurrent(NULL);

	//release the data
	delete OALData;
}
