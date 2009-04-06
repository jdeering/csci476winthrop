#include "audio.h"

/******************************************************
	Default Constructor
******************************************************/
Audio::Audio()
{
	playing = false;
	loop = false;
	sample = NULL;
}

/******************************************************
	Default Destructor
******************************************************/
Audio::~Audio()
{
	playing = false;
	loop = false;
	destroy_sample(sample);
}

/******************************************************
	Constructor

	@param sam Allegro audio SAMPLE associated with the object.
	@param loops Sets the loop flag
******************************************************/
Audio::Audio(SAMPLE* sam, bool loops)
{
	sample = sam;
	loop = loops;
	Stop();
}

/******************************************************
	Loads the sample at the specified file location.

	@param file Path to the audio file to load.
	@param loops Sets the loop flag
******************************************************/
void Audio::LoadSample(char *file, bool loops)
{
	sample = load_sample(file);
	loop = loops;
}

/******************************************************
	Stops the sample if it is currently playing.
******************************************************/
void Audio::Stop()
{
	stop_sample(sample);
	playing = false;
}

/******************************************************
	Plays the sample at the specified volume.

	@param volume The volume at which to play the sample (0 to 255).
	@return The voice the sample is being played on.
******************************************************/
int Audio::Play(int volume)
{
	if(loop)
	{
		if(!playing)
		{			
			playing = true;
			return play_sample(sample, volume, PAN, FREQ, loop);
		}
		return 0;
	}
	else
		return play_sample(sample, volume, PAN, FREQ, loop);

}

/******************************************************
	Resets the playing sample at the specified volume.

	@param volume The volume to change the sample to (0 to 255).
******************************************************/
void Audio::ResetVolume(int volume)
{
	adjust_sample(sample, volume, PAN, FREQ, loop);
}

/******************************************************
	Resets the loop flag and volume of a playing sample.

	@param volume The volume to change the sample to (0 to 255).
	@param set_loop Zero to not loop, non-zero to loop.
******************************************************/
void Audio::ResetLoopFlag(int volume, int set_loop)
{	
	if(set_loop != 0)
		loop = true;
	else
		loop = false;
	adjust_sample(sample, volume, PAN, FREQ, loop);
}