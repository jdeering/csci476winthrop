#include <string>

class Tile
{
	public:
		char getLetter();
		void toggleImage();

	private:
		char letter;
		std::string imagepath;
		bool selected;
};
