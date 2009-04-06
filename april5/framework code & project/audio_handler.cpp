#include "audio_handler.h"

/******************************************************
	Default Constructor
******************************************************/
AudioHandler::AudioHandler()
{
	muted = false;
	volume = (MAX_VOLUME - MIN_VOLUME) / 2;
}

/******************************************************
	Default Destructor
******************************************************/
AudioHandler::~AudioHandler()
{
	for(std::map<std::string, Audio>::iterator i = samples.begin(); i != samples.end(); ++i)
	{
		i->second.~Audio();
	}
	samples.clear();
}

/******************************************************
	Adds an audio sample to the container at the
	specified key, or updates the audio sample at the
	key.

	@param refName The key name for the sample to add.
	@param sample The Allegro SAMPLE* associated with the key.
	@param loop <code>true</code> if the sample loops when played, <code>false</code> if it doesn't.
	@return <code>true</code> if the sample is successfully added, <code>false</code> otherwise.
******************************************************/
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

/******************************************************
	Removes the audio sample from the container at the
	specified key.

	@param refName The key name for the sample to remove.
	@return <code>true</code> if the sample is successfully removed, <code>false</code> otherwise.
******************************************************/
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

/******************************************************
	Plays the audio sample at the specified key.

	@param refName The key name for the sample to play.
	@param volume_ The volume to play the sample at.
	@return <code>true</code> if the sample is successfully started, <code>false</code> otherwise.
******************************************************/
bool AudioHandler::PlaySample(std::string refName, int volume_)
{
	if(muted)
		volume_ = 0;
	if(samples[refName].Play(volume_) < 0)
	{
		allegro_message("Sample \"%d\" could not be played.\n(May be out of voice channels)", refName);
		return false;
	}
	else
		return true;
}

/******************************************************
	Stops the audio sample at the specified key.

	@param refName The key name for the sample to stop playing.
******************************************************/
void AudioHandler::StopSample(std::string refName)
{
	samples[refName].Stop();
}

/******************************************************
	Sets the volume at which to play all samples.

	@param vol The volume at which to play audio samples (0 to 100);
******************************************************/
void AudioHandler::SetVolume(int vol)
{
	volume = vol * MAX_VOLUME / 100;
	ResetVolume(volume);
}

/******************************************************
	Mutes all playing samples and subsequently played samples.
******************************************************/
void AudioHandler::Mute()
{
	muted = true;
	ResetVolume(0);
}

/******************************************************
	Unmutes all playing samples and subsequently played samples.
******************************************************/
void AudioHandler::Unmute()
{
	muted = false;
	ResetVolume(volume);
}

/******************************************************
	Resets the loop flag for the audio sample at the
	specified key.

	@param refName The key value for the audio sample.
	@param loop The new value for the loop flag. Zero for no looping, non-zero for looping.
******************************************************/
void AudioHandler::ResetLoopFlag(std::string refName, int loop)
{
	samples[refName].ResetLoopFlag(volume, loop);
}

/******************************************************
	Resets the volume for all currently playing samples.

	@param volume_ The volume at which to set the samples (0 to 255).
******************************************************/
void AudioHandler::ResetVolume(int volume_)
{
	for(std::map<std::string, Audio>::iterator i = samples.begin(); i != samples.end(); ++i)
	{
		i->second.ResetVolume(volume_);
	}
	if(volume_) // Only resets volume if not muting
		volume = volume_;
}