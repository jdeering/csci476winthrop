/*
Lauren Cairco
26 February 2009
CSCI 476 Project

Dictionary.h
For use with the Wordplay game module
This class loads in a dictionary from a file and has a function that lets you search through it for words.
Needs STL vector and string to keep track of the words in the dictionary, and algorithm to use binary search.
Also needs fstream so that it can load in the dictionary from a file.

DATA ITEMS
vector <string> words
	list of all the words in the dictionary

FUNCTIONS
Dictionary(string)
	takes the given filepath in string as the source of the dictionary, and loads it all into the class
bool search(string)
	searches through the dictionary for the word passed in as the parameter
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

class Dictionary
{
	public:
		Dictionary();
		bool search(std::string);
		
	private:
		std::vector<std::string> words;
};
#endif