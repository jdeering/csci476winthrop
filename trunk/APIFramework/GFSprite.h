#include <string>

class GFSprite
{
	/* FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* NULL OBJECT */
		static const GFSprite nul;

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
		bool operator==(const GFSprite &s){ return _ref == s._ref; };

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFSprite(int, int, int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		/* SCREEN POSITION */
		int _x, _y;
};
