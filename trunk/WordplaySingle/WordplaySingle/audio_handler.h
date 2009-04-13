/*
Jason Deering

audio_handler.h

This class is for use in the Framework.

Requires including the STL map as a container.

The AudioHandler class is responsible for the playing of all audio, except text-to-speech.


DATA ITEMS
	std::map<std::string, Audio> samples - container for all active instances of the Audio class
	int volume - the current volume at which to play audio samples
	bool muted - whether or not sound is currently muted
	int numSamples - number of audio samples in the container

FUNCTIONS
	void SetVolume(int volume) - sets the volume to the parameter's value
	Mute() - mutes all sounds
	Unmute() - unmutes sounds
	bool AddSample(std::string refName, SAMPLE* sample, bool loop) - adds the audio sample to the container
				with the specified loop value; returns true for success, false for failure.
	bool RemoveSample(std::string refName) - removes the audio sample from the container
				returns true for success, false for failure.
	bool PlaySample(std::string refName, int volume) - plays the sample in the container at key refName at the specified volume
	void StopSample(std::string refName) - stops the playing of the sample at key refName
	void ResetLoopFlag(std::string refName, int loop) - sets the loop value for the sample at key refName
	void ResetVolume(int volume) - resets the volume to the parameter's value for all samples that are currently playing

*/

#ifndef _AUDIO_HANDLER_H
#define _AUDIO_HANDLER_H

#include "globals.h"
#include "audio.h"


class AudioHandler
{
private:
	std::map<std::string, Audio> samples;
	int volume;
	bool muted;
	int numSamples;
public:
	AudioHandler();
	~AudioHandler();
	void SetVolume(int volume);
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