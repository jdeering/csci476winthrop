#include <string>

class GFText
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* PUBLIC DESTRUCTOR */
		~GFText();

		/* FRAMEWORK CALLS */
		void setTextPosition(int, int);
		void setVisible(bool);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFText(int, int, int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		/* SCREEN POSITION */
		int _x, _y;
};

