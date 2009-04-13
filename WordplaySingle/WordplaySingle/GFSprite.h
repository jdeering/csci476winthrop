#pragma once
#include <string>
#include <iostream>

#include "GFObject.h"

class GFSprite : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFSprite();
		
		/* SCREEN POSITION */
		int _x, _y;
		
		/* NULL OBJECT */
		static const GFSprite null;

		/* BITMAP FUNCTIONS */
		void changeBitmap(std::string);

		/* SPRITE FUNCTIONS */
		void setVisible(bool);
		void setSpriteSize(int, int);
		void setSpritePosition(int, int);
		void moveTo(int, int, int);

		/* ANIMATION FUNCTIONS */
		void setSpriteFrame(int);
		void setAnimation(bool);
		void setSpriteFrameDelay(int);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFSprite&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFSprite(int, int, int);
};
