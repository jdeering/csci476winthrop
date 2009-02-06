#include <vector>
#include <string>

#include <fstream>
#include <algorithm>

#include "Dictionary.h"

// constructs dictionary based on filename passed in, or the default if no filename is passed into the constructor
Dictionary::Dictionary(std::string filename = "dictionary.dat")
{
	std::ifstream inFile(filename.c_str());
	
	std::string tmp;
	inFile >> tmp;
	
	// load the file into the vector
	while (!inFile.eof())
	{
		words.push_back(tmp);
		inFile >> tmp;
	}
}


bool Dictionary::search(std::string s)
{
	// binary search through the vector to find out if there's a match using the STL algorithm for binary search
	return binary_search(words.begin(), words.end(), s);
}
