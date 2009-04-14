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

	std::string s;
	inFile>>s;
	while (!inFile.eof()){
		words.push_back(s);
		inFile>>s;
	}
}

//returns whether the word is in the dictionary or not
bool Dictionary::search(std::string s)
{
	//convert to lowercase
	for (int i = 0; i < s.length(); i++){
		s[i] = char( char(s[i]) + 32);
	}

	// binary search through the vector to find out if there's a match using the STL algorithm for binary search
	return binary_search(words.begin(), words.end(), s);
}
