#include <string>

class GFSprite
{
	/* FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
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

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFSprite(int, std::string, int, int, int, int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		/* SCREEN POSITION */
		int _x, _y;
};

/* FOR DEVELOPER USE */
typedef GFSprite& GFSpriteRef;
