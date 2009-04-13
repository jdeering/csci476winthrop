/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Dictionary.cpp
For use with the Wordplay game module
Implementation of Dictionary.h; all the function documentation and includes are found there

*/
#include "Dictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

// constructs dictionary based on filename passed in, or the default if no filename is passed into the constructor
Dictionary::Dictionary()
{
	//initialize word list
	ifstream inFile;
	inFile.open("dictionary.txt");

	std::cout << "Dictionary Loading..." << std::endl;
	std::string s;
	inFile>>s;
	while (!inFile.eof()){
		words.push_back(s);
		inFile>>s;
	}
	std::cout << "Dictionary Loaded." << std::endl;
	std::cout << "size: "<<words.size()<<std::endl;

}

//returns whether the word is in the dictionary or not
bool Dictionary::search(std::string s)
{
//cout<<words.size()<<endl;
return true;
/*	// binary search through the vector to find out if there's a match using the STL algorithm for binary search
	//return binary_search(words.begin(), words.back(), s);
	//return binary_search(words.begin(), words.end() - 1, s);

	//real binary search here
	return bSearch(s, 0, words.size());
	*/
}

bool Dictionary::bSearch(std::string s, int begin, int end)
{
	if (end == begin) return false;
	if (s == words.at((end - begin) / 2)) return true;
	else if (s < words.at((end - begin) / 2))
		bSearch(s, begin, (end - begin) / 2);
	else if (s > words.at((end - begin) / 2))
		bSearch(s, (end - begin) / 2, end);
}