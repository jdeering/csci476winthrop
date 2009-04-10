#ifndef _USER_H
#define _USER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include "md5wrapper.h"
#include "Markup.h"

using namespace std;

//String conversion methods for XML Parser
wstring StringToWString(const string& s);
string WStringToString(const wstring& s);
string IntToString(int i);


class User
{
	private:

		string username;

	public:

		 // constructor that creates a user class if login succeeds
		User(string);

		// Sets a users score from a module into an XML file
		int setScore(string module, int score);

};

#endif