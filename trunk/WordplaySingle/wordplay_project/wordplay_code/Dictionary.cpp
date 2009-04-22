/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Dictionary.cpp
For use with the Wordplay game module
Implementation of Dictionary.h; all the function documentation and includes are found there.
Cppdocs comments are also found in this file.

*/
#include "Dictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

// constructs dictionary by loading in words from a file
/*********************************************
	Default constructor. Loads in words from dictionary.txt (in same folder as executable) and puts them into the <code>words</code> vector.
	In order for the search algorithm to work correctly, dictionary.txt must be an already ordered list of words.
*********************************************/
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

/*********************************************
	Searches the dictionary <code>words</code> vector for the incoming word using the STL <code>binary_search</code> algorithm.

	@param s the word that we're looking for in the dictionary
	@return true if the word is in the dictionary, false if it is not in the dictionary
*********************************************/

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
