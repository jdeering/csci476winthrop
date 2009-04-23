/**
 *		@file GFText.h
 *		@brief A Text Object to be used with the CSCI476 Game Framework
 */
 
#pragma once
#include <string>

#include "GFObject.h"

/**
 *		The class representing the Text object.
 */
class GFText : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFText();
		
		/* SCREEN POSITION */
		
		/** 	@brief Screen coordinates for the GFText
		 */
		int _x, _y;
		
		/* NULL OBJECT */
		static const GFText null;

		/* FRAMEWORK CALLS */
		
		/** 	@brief Change the position of the GFText
		 *		@param x 		new x-position
		 *		@param y 		new y-position
		 */
		void setTextPosition(int x, int y);
		
		/** 	@brief Change the visibility of the GFText
		 *		@param b 		visibility (true = visible, false = invisible)
		 */
		void setVisible(bool b);
		
		/** 	@brief Change the text contents of the GFText
		 *		@param s 		new contents
		 */
		void setContent(std::string s);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFText&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFText(int, int, int);
};
