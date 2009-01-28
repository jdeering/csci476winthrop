#include <vector>
#include <string>

class Dictionary
{
	public:
		Dictionary(std::string);
		int isWord(std::string);
		
	private:
		std::vector <std::string> words;
};
