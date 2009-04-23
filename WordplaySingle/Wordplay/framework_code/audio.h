/*
Jason Deering

audio.h

This class is for use in the Framework.

It requires Allegro header files included for the SAMPLE struct.

The Audio class implements the playing and stopping of an Allegro SAMPLE.


DATA ITEMS
	bool loop - whether or not the SAMPLE should loop after it is done playing
	bool playing - whether or not the current Audio object is playing
	SAMPLE *sample - a pointer to the SAMPLE struct for the audio file associated with the current instance

FUNCTIONS
	void LoadSample(char* file, bool loops) - loads the specified file as a SAMPLE and sets the loop flag to the 
												value of the respective parameter
	void Stop() - stops playing of the current file, if it is playing
	int Play(int volume, int pan, int freq) - plays the associated file at the specified volume, pan and frequency
	void ResetVolume(int volume, int pan, int freq) - resets the volume of currently playing audio
	void ResetLoopFlag(int volume, int pan, int freq, int set_loop) - resets loop flag of currently playing audio

*/

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
	int Play(int volume);
	void ResetVolume(int volume);
	void ResetLoopFlag(int volume, int set_loop);
};


#endif