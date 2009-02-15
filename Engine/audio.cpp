#include "audio.h"

Audio::Audio()
{
	playing = false;
	loop = false;
	sample = NULL;
}

Audio::~Audio()
{
	playing = false;
	loop = false;
	destroy_sample(sample);
}

Audio::Audio(SAMPLE* sam, bool loops)
{
	sample = sam;
	loop = loops;
	Stop();
}
void Audio::LoadSample(char *file, bool loops)
{
	sample = load_sample(file);
	loop = loops;
}

void Audio::Stop()
{
	stop_sample(sample);
	playing = false;
}

bool Audio::Play(int volume, int pan, int freq)
{
	if(loop)
	{
		if(!playing)
		{			
			playing = true;
			return play_sample(sample, volume, pan, freq, loop);
		}
	}
	else
		return play_sample(sample, volume, pan, freq, loop);

}


void Audio::ResetVolume(int volume, int pan, int freq)
{
	adjust_sample(sample, volume, pan, freq, loop);
}

void Audio::ResetLoopFlag(int volume, int pan, int freq, int set_loop)
{	
	if(set_loop != 0)
		loop = true;
	else
		loop = false;
	adjust_sample(sample, volume, pan, freq, loop);
}