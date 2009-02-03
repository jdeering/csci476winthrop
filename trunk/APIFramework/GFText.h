#include <string>

class GFText
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* NULL OBJECT */
		static const GFText null;

		/* PUBLIC DESTRUCTOR */
		~GFText();

		/* FRAMEWORK CALLS */
		void setTextPosition(int, int);
		void setVisible(bool);

		/* OVERLOADED OPERATORS */
		bool operator==(const GFText&);

		/* PRINT FUNCTION (FOR DEBUG) */
		friend std::ostream& operator<<(std::ostream&, GFText&);

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFText(int, int, int);

	private:
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		/* SCREEN POSITION */
		int _x, _y;
};

