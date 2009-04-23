/**
 *		@file GFAudio.h
 *		@brief An Audio Object to be used with the CSCI476 Game Framework
 */
 
#pragma once
#include <string>

#include "GFObject.h"

/**
 *		The class representing the Audio object.
 */
class GFAudio : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFAudio();
		
		/* NULL OBJECT */
		static const GFAudio null;

		/* CONSTANTS FOR AUDIO PLAYBACK */
		// static const int STOP = 0;
		// static const int PLAY = 1;

		/* PLAYBACK FUNCTIONS */
		/** 	@brief Play this piece of audio
		 */
		void play();
		
		/** 	@brief Stop this piece of audio
		 */
		void stop();
		
		/** 	@brief Set the number of times for this piece of audio to loop.
		 *		@param c 		Loop Count
		 */
		void setLoopCount(int c);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream& o, GFAudio& a);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFAudio(int r);
};
