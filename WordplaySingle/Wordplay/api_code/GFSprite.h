/**
 *		@file GFSprite.h
 *		@brief A Sprite Object to be used with the CSCI476 Game Framework
 */
 
#pragma once
#include <string>
#include <iostream>

#include "GFObject.h"

/**
 *		The class representing the Sprite object.
 */
class GFSprite : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFSprite();
		
		/* SCREEN POSITION */
		/** 	@brief Screen coordinates for the GFSprite
		 */
		int _x, _y;
		
		/* NULL OBJECT */
		static const GFSprite null;

		/* BITMAP FUNCTIONS */
		
		/** 	@brief Change the file displayed in the GFSprite
		 *		@param s 		new filename
		 */
		void changeBitmap(std::string s);

		/* SPRITE FUNCTIONS */
		
		/** 	@brief Change the visibility of the GFSprite
		 *		@param b 		new visibility (true = visible, false = invisible)
		 */
		void setVisible(bool b);
		
		/** 	@brief Change the size of the GFSprite
		 *		@param w 		new width
		 *		@param h 		new height
		 */
		void setSpriteSize(int w, int h);
		
		/** 	@brief Change the position of the GFSprite
		 *		@param x 		new x-position
		 *		@param y 		new y-position
		 */
		void setSpritePosition(int x, int y);
		
		/** 	@brief Begin movement of the sprite toward the specified location
		 *		@param x		target x-position
		 *		@param x		target y-position
		 *		@param x		speed (in ticks)
		 */
		void moveTo(int x, int y, int s);

		/* ANIMATION FUNCTIONS */
		
		/** 	@brief If the GFSprite is animated, show the specified frame
		 *		@param n 		new frame
		 */
		void setSpriteFrame(int n);
		
		/** 	@brief Play or stop the animation in the GFSprite
		 *		@param b 		animation (true = play, false = stop)
		 */
		void setAnimation(bool b);
		
		/** 	@brief Change the frame delay of the GFSprite animation
		 *		@param t 		delay (in ticks)
		 */
		void setSpriteFrameDelay(int t);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFSprite&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFSprite(int, int, int);
};
