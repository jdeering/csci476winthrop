#include <string>
#include "../APIFramework/GameFramework.h";

class Tile
{
	public:
		Tile();
		char getLetter();
		void toggleImage();
		void showTile(int, int);
		bool isSelected();
		void highlightValid();
		void highlightInvalid();
		void unhighlight();

	private:
		char letter;
		bool selected;

		GFSprite * relatedSprite;

		char generateLetter();
};
