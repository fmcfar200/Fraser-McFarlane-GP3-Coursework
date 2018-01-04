
#include "Constants.h"

#ifndef _SOUND_H
#define _SOUND_H


class Sound
{
private:

	char*        OALData;           //data for the buffer
	ALenum       OALFormat;         //buffer format
	ALsizei      OALFrequency;     //frequency
	long         OALBufferLen;      //bit depth
	int			 OALChannels;		  // Channels
	int			 OALSize;			  // Size
	int			 OALBitRate;		  // Bit Rate
	float        OALLength;		  // Length
	ALboolean    OALLoop;           //loop
	unsigned int OALSource;         //source
	ALuint       OALBuffer;         // Buffer
	ALboolean    OALbEAX;			  // for EAX 2.0 support
	ALboolean    alLoop;			  //loop

	struct FMTCHUNK {
		short format;
		short channels;
		unsigned long srate;
		unsigned long bps;
		short balign;
		short samp;
	};

	void LoadWAVInfo(ifstream &filename, string &name, unsigned int &size); //loads wav file data

public:
	Sound(); //constructor
	~Sound(); //destructor

	void loadWAVFile(LPCSTR filename);	//loads wav file from filname
	void playAudio( ALboolean sndLoop);	//plays audio file
	void stopAudio();	//stops audop
	void cleanUp();	//deletes sources and contexts
	bool isPlaying();
};
#endif