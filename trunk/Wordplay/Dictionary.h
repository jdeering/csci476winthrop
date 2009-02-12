#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include <string>

class Dictionary
{
	public:
		Dictionary(std::string);
		bool search(std::string);
		
	private:
		std::vector <std::string> words;
};
#endif