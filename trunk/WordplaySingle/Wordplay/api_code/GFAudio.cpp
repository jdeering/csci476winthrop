#include <iostream>
#include "GameFramework.h"

/* NULL OBJECT */
GFAudio const GFAudio::null(-1);

/* CONSTRUCTOR */
GFAudio::GFAudio(int r) : GFObject(r) { };

/* DESTRUCTOR */
GFAudio::~GFAudio() { };

void GFAudio::play()
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d", AUDIO_PLAY, _ref); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->PlayFile(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFAudio::stop()
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d", AUDIO_STOP, _ref); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->StopFile(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

void GFAudio::setLoopCount(int loops)
{ 
	sprintf(GameFramework::_msgBuffer, "%d %d %d", AUDIO_SET_LOOP_COUNT, _ref, loops); 
	//GameFramework::sendMessage();
	GameFramework::ENGINE->ResetLoop(GameFramework::_msgBuffer);
	_clrBuffer(GameFramework::_msgBuffer);
};

/* PRINT FUNCTION */
std::ostream& operator<<(std::ostream &s, GFAudio &a)
{ return s << "AUDIO @ " << &a << ": " << a._ref; };
