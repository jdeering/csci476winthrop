#ifndef _AUDIO_H
#define _AUDIO_H

#include "globals.h"

class Audio
{
private:
	bool loop, playing;
	SAMPLE *sample;
public:
	Audio();
	~Audio();
	Audio(SAMPLE* sam, bool loops);
	void LoadSample(char* file, bool loops);
	void Stop();
	int Play(int volume, int pan, int freq);
	void ResetVolume(int volume, int pan, int freq);
	void ResetLoopFlag(int volume, int pan, int freq, int set_loop);
};


#endif