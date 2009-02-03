#include <string>
#include <iostream>

class GFSprite
{
	/* FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* NULL OBJECT */
		static const GFSprite null;

		/* PUBLIC DESTRUCTOR */
		~GFSprite();

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

		/* OVERLOADED OPERATORS */
		bool operator==(const GFSprite &s);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFSprite&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFSprite(int, int, int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		/* SCREEN POSITION */
		int _x, _y;
};
