#ifndef _USER_H
#define _USER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "md5wrapper.h"
#include "Markup.h"

using namespace std;

// Creates a user with the given username, password, and password verification
int createUser(string username, string password, string verpass);

// Returns a vector of all the scores for a given module
vector<string> showScores(string module);

//String conversion methods for XML Parser
wstring StringToWString(const string& s);
string WStringToString(const wstring& s);
string IntToString(int i);


class User
{
	private:
		static bool isLoggedIn; // true if a user is logged in

		string username;
		bool isUserLoggedIn; // true if THIS user is logged in
		int score;

	public:

		 // constructor that creates a user class if login succeeds
		User(string, string);

		 // Logs a user in with password
		int login(string password);

		// Sets a users score from a module into an XML file
		int setScore(string module, int score);

		// Retrieves a user's name from private variable username
		string getUserName();

		// Retrieves a user's private isUserLoggedIn variable
		bool getIsUserLoggedIn();

		// Logs the current user out
		int logout();

		// Returns a vector of a user's first, last, best and average score
		vector<string> getProgressReport(string module);

		// Retrieves the getIsLoggedIn variable to see if any user is logged in
		static bool getIsLoggedIn();
};

#endif