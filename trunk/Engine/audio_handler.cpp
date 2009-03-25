#include "audio_handler.h"

AudioHandler::AudioHandler()
{
	muted = false;
	readText = true;
	volume = (MAX_VOLUME - MIN_VOLUME) / 2;
}

AudioHandler::~AudioHandler()
{
	for(std::map<std::string, Audio>::iterator i = samples.begin(); i != samples.end(); ++i)
	{
		i->second.~Audio();
	}
	samples.clear();
}

bool AudioHandler::AddSample(std::string refName, SAMPLE *sample, bool loop)
{
	if(numSamples < MAXFILES)
	{
		Audio temp(sample, loop);
		samples[refName] = temp;
		numSamples++;
	}
	else
	{
		allegro_message("Sample \"%d\" could not be added.", refName);
		return false;
	}
}

bool AudioHandler::RemoveSample(std::string refName)
{
	std::map<std::string, Audio>::iterator loc = samples.find(refName);
	if(numSamples > 0 && loc != samples.end())
	{
		samples.erase(loc);
		numSamples--;
		return true;
	}
	else
	{
		allegro_message("Sample \"%d\" not found or could not be removed.", refName);
		return false;
	}
}

bool AudioHandler::PlaySample(std::string refName, int volume)
{
	if(samples[refName].Play(volume, PAN, FREQ) < 0)
	{
		allegro_message("Sample \"%d\" could not be played.\n(May be out of voice channels)", refName);
		return false;
	}
	else
		return true;
}

void AudioHandler::StopSample(std::string refName)
{
	samples[refName].Stop();
}

void AudioHandler::SetVolume(int vol)
{
	volume = vol * MAX_VOLUME / 100;
}

void AudioHandler::SetReadText(bool read)
{
	readText = read;
}

void AudioHandler::Mute()
{
	muted = true;
	ResetVolume(0);
}

void AudioHandler::Unmute()
{
	muted = false;
	ResetVolume(volume);
}

void AudioHandler::ResetLoopFlag(std::string refName, int loop)
{
	samples[refName].ResetLoopFlag(volume, PAN, FREQ, loop);
}

void AudioHandler::ResetVolume(int volume_)
{
	for(std::map<std::string, Audio>::iterator i = samples.begin(); i != samples.end(); ++i)
	{
		i->second.ResetVolume(volume_, PAN, FREQ);
	}
	if(volume_) // Only resets volume if not muting
		volume = volume_;
}