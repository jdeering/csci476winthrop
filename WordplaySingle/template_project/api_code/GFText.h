#pragma once
#include <string>

#include "GFObject.h"


class GFText : public GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFText();
		
		/* SCREEN POSITION */
		int _x, _y;
		
		/* NULL OBJECT */
		static const GFText null;

		/* FRAMEWORK CALLS */
		void setTextPosition(int, int);
		void setVisible(bool);
		void setContent(std::string);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFText&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFText(int, int, int);
};
