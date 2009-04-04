#ifndef _AUDIO_HANDLER_H
#define _AUDIO_HANDLER_H

#include "globals.h"
#include "audio.h"
#define PAN 128
#define FREQ 1000
#define MAX_VOLUME 255
#define MIN_VOLUME 0

class AudioHandler
{
private:
	std::map<std::string, Audio> samples;
	int volume;
	bool readText, muted;
	int numSamples;
public:
	AudioHandler();
	~AudioHandler();
	void SetVolume(int volume);
	void SetReadText(bool read);
	void Mute();
	void Unmute();
	bool AddSample(std::string refName, SAMPLE* sample, bool loop);
	bool RemoveSample(std::string refName);
	bool PlaySample(std::string refName, int volume);
	void StopSample(std::string refName);
	void ResetLoopFlag(std::string refName, int loop);
	void ResetVolume(int volume);
};



#endif