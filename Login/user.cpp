#include "user.h"

int createUser(string username, string password, string verpass)
// createUser
// Arguments:	username -	username for new user
//				password -	password for new user
//				verpass -	ensures password accuracy
// Attempts to create a new user with the username and password given.
// Checks to see if the password and verpass match and if a user with
// the given username already exists.
// Returns: An integer that represents the success of the user creation.
//			-1 = failed user creation (user with username already exists)
//			0 = failed user creation (mismatched password and verpass)
//			1 = successful user creation
{
	md5wrapper md5; // Used for password encryption/decryption

	if (password != verpass) //If password and verpass do not match
		return 0; //Return failed user creation (mismatched password and verpass)

	ifstream inp, loginFileIn;
	ofstream loginFileOut;

	inp.open("data\\users.dat", ios::in);
	inp.close();
	if(!inp.fail()) // If users data file exists
	{
		loginFileIn.open("data\\users.dat"); // File containing usernames and passwords
		string tempuser; // Used for iterating over usernames in file

		loginFileIn >> tempuser;
		while(!loginFileIn.eof())
		{
			if(tempuser == username) //If the username already exists
			{
				loginFileIn.close(); // Close user data file
				return -1; //Return failed user creation (user with username already exists)
			}
			loginFileIn >> tempuser >> tempuser; //Else, keep iterating over the file
		}
		loginFileIn.close(); // Close user data file after end of iteration
	}
	else inp.clear(ios::failbit); //Else, clear failure bit

	// Open the data file for appending
	loginFileOut.open("data\\users.dat", ios::out | ios::app);

	// User credentials written to file
	loginFileOut << username << "\t" << md5.getHashFromString(password + username) << endl;
	loginFileOut.close(); // Close user data file
	return 1; // Return successful user creation!
}

vector<string> showScores(string module)
// showScores
// Arguments:	module -	a string representing the name of the module from where
//							the scores are retrieved
//
// Pushes all users' scores from a given module to a string vector
//
// Returns: A string vector containing usernames in the format:
//			[username],[score],...,[username],[score]
{
	vector<string> scores; // Vector for storing usernames and scores
	CMarkup xmlscores; // Declares an XML object for reading in scores.xml

	ifstream inp;
	string scoreFileStream = "modules\\" + module + "\\users\\scores.xml";
	
	inp.open( scoreFileStream.c_str(), ios::in);
	inp.close();
	if(inp.fail()) // Tests to see if the module's scores.xml file exists
					// If it does not exist...
	{
		inp.clear(ios::failbit);
		return scores; // Return empty vector
	}
	else  // Else, if scores.xml does exist
	{
		xmlscores.Load( StringToWString(scoreFileStream) ); //Load the XML document into memory
		xmlscores.FindElem( MCD_T("SCORES") ); // Find the SCORES element in the document
		xmlscores.IntoElem(); // Go inside the SCORES tags
		while(xmlscores.FindElem()) // While there are still SCORES 
		{
			scores.push_back(WStringToString(xmlscores.GetData())); // Push score onto vector
			scores.push_back(WStringToString(xmlscores.GetAttrib(MCD_T ("name") ))); // Push user name onto vector
		}
	}

	return scores; // Return the vector of usernames and scores
}

wstring StringToWString(const string& s)
// StringToWString
// Arguments:	s - standard string
// Converts an std string to an std wstring
// Returns:		An std wstring
{
	wstring temp(s.length(),L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}

string WStringToString(const wstring& s)
// WStringToString
// Arguments:	s - standard wide string
// Converts an std wstring to an std string
// Returns:		An std string
{
	string temp(s.length(),' ');
	copy(s.begin(),s.end(),temp.begin());
	return temp;
}

string IntToString(int i)
// IntToString
// Arguments:	i - integer to be converted
// Converts an integer to an std string
// Returns:		A string converted from i
{
	string s;
	stringstream out;
	out << i;
	s = out.str();
	return s;
}

//*********************************
// USER CLASS METHODS
//*********************************

User::User(string usr, string pwd)
// User class constructor
// Arguments:	usr	-	username for user instance
//				pwd -	password for user instance
// Creates a user with the username and password in the arguments
// and attempts to log this user in.  If unsuccessful, the constructor
// throws an exception to be caught by the caller of the function.
// Values of the exception described in the login function.
// Returns: Nothing (constructor)
{
	username = usr;
	int success = login(pwd);
	cout << success << endl;
	if(!success)
		throw success;
}

// Sets the default value of the static variable isLoggedIn to false
// (no one is logged in at first)
bool User::isLoggedIn = false;

int User::login(string password)
// User::login
// Arguments:	password -	password used for the login process
// Attempts to login a user with its username and the password argument.
// Checks to see if a user is already logged in and if the correct password/username
// combination was used.
// Returns: An integer that represents the success of the login.
//			0 = failed login
//			1 = successful login
{
	md5wrapper md5; // Used for encrypting and decrypting passwords

	if(User::getIsLoggedIn()) return 0; // If a user is already logged in
										// Return failed login value

	ifstream loginFile;
	string tempuser, temppass; // Temporary strings used to iterate through user file
	loginFile.open("data\\users.dat"); // File containing usernames and passwords
	
	loginFile >> tempuser;
	while(!loginFile.eof())
	{
		if(tempuser == username) //If the username matches
		{
			loginFile >> temppass;
			if(temppass == md5.getHashFromString(password+username)) //Check the MD5 encrypted password
			{
				// Logs the user in if the passwords match
				// and sets the users isUserLoggedIn value to true
				// as well ast the static isLoggedIn variable to true
				loginFile.close();
				User::isLoggedIn = true;
				isUserLoggedIn = true;
				return 1; // Return login success!
			}
		}
		else // Continue iterating the file
		{
			loginFile >> temppass;
		}

		loginFile >> tempuser;
	}
	loginFile.close(); // Close user file
	return 0; // Return failed login value (no matching entries)
}

int User::setScore(string module, int score)
/** XML FILE PARSER **/
{
	ifstream userInp, scoreInp;
	string userFileStream = "modules\\" + module + "\\users\\" + username + ".xml";
	string scoreFileStream = "modules\\" + module + "\\users\\scores.xml";

	userInp.open(userFileStream.c_str(), ifstream::in);
	userInp.close();
	if(userInp.fail()) //if user's xml file does not exist
	{
		userInp.clear(ios::failbit);
		//write xml heading and structure for new user
		//with first, last, and average score = score
		//set number of times played to 1
		//write closure tags

		ofstream newxml;
		newxml.open(userFileStream.c_str());

		newxml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
		newxml << "<USER name = \"" << username << "\">" << endl;
		newxml << "\t<FIRSTSCORE>" << score << "</FIRSTSCORE>" << endl;
		newxml << "\t<LASTSCORE>" << score << "</LASTSCORE>" << endl;
		newxml << "\t<PLAYS>1</PLAYS>" << endl;
		newxml << "\t<AVERAGESCORE>" << score << "</AVERAGESCORE>" << endl;
		newxml << "\t<BESTSCORE>" << score << "</BESTSCORE>" << endl;
		newxml << "</USER>";

		newxml.close(); // close xml file

		scoreInp.open(scoreFileStream.c_str(), ifstream::in);
		scoreInp.close();
		if(scoreInp.fail()) // if module's xml file does not exist
		{
		// add xml heading and current users information
			
			scoreInp.clear(ios::failbit);


			newxml.open(scoreFileStream.c_str());
			newxml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
			newxml << "<SCORES>" << endl;
			newxml << "\t<USER name = \"" << username << "\">" << score << "<\USER>" << endl;
			newxml << "</SCORES>" << endl;
			newxml.close(); //close xml file
		}
		else // module's xml file already exists
		{
			CMarkup scorexml;
			wstring currscore, curruser;

			cout << "reallyhere" << endl;
			
			//load the module's xml file
			scorexml.Load( StringToWString(scoreFileStream) );
			scorexml.FindElem( MCD_T("SCORES") );
			scorexml.IntoElem();
			
			while(scorexml.FindElem()) //iterate through all scores
			{
				currscore = scorexml.GetData();
				if(atoi(WStringToString(currscore).c_str()) > score) //if current score is greater than user's score
						continue; // continue down the list
				else // user's score is greater than current score
				{
					// insert user's name and score above current record
					// and break from loop
					scorexml.InsertElem( MCD_T("USER"), StringToWString(IntToString(score)) );
					scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
					scorexml.SetData( StringToWString(IntToString(score)) );
					break;
				}
			}
			scorexml.Save(StringToWString(scoreFileStream));
		}
		return 0;
	}
	else
	{
		CMarkup userxml, scorexml;
		int plays;
		int average;
		wstring tempWstring, currscore;

	//load user's xml file
		userxml.Load(StringToWString(userFileStream));

	//find last score
		userxml.FindElem( MCD_T("USER") );
		userxml.IntoElem();
		userxml.FindElem( MCD_T("LASTSCORE") );

	//replace last score
		userxml.SetData( StringToWString(IntToString(score)) );

	//find and increment number of plays
		userxml.FindElem( MCD_T("PLAYS") );
		tempWstring = userxml.GetData();

		plays = (atoi(WStringToString(tempWstring).c_str()));
		plays++;
		userxml.SetData( StringToWString(IntToString(plays)) );

	//find and recalculate average
		userxml.FindElem( MCD_T("AVERAGESCORE") );
		tempWstring = userxml.GetData();
		string tempAvgstring(tempWstring.begin(), tempWstring.end());
		average = (atoi(tempAvgstring.c_str()) + score)/plays;
		userxml.SetData( StringToWString(IntToString(average)) );

		userxml.FindElem( MCD_T("BESTSCORE") );
		currscore = userxml.GetData();

		if(score > atoi(WStringToString(currscore).c_str()))
		{	
			userxml.SetData( StringToWString(IntToString(score)) );
		//open scores.xml file
			scorexml.Load( StringToWString(scoreFileStream));
		//find user
			scorexml.FindElem( MCD_T("SCORES") );
			scorexml.IntoElem();

		//find score
			while(scorexml.FindElem()) // iterate through all scores
			{
				currscore = scorexml.GetData();
				if(atoi(WStringToString(currscore).c_str()) > score)
						continue;
				else // if current score is less than user's score, insert
					// user's name and score, and break out of loop
				{
					scorexml.InsertElem( MCD_T("USER"), StringToWString(IntToString(score)) );
					scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
					scorexml.SetData( StringToWString(IntToString(score)) );
					break;
				}
			}
			scorexml.Save(StringToWString(scoreFileStream));
		}
		userxml.Save(StringToWString(userFileStream));
		return 1;
	}
}

string User::getUserName()
{
	return username;
}

bool User::getIsLoggedIn()
{
	return isLoggedIn;
}

bool User::getIsUserLoggedIn()
{
	return isUserLoggedIn;
}

int User::logout()
{
	if(isLoggedIn)
	{
		isLoggedIn = false;
		isUserLoggedIn = false;
		return 1;
	}
	else
		return 0; // logout failed
}

vector<string> User::getProgressReport(string module)
{
	/** XML FILE PARSER **/
	CMarkup userxml;
	vector<string> progressVec;
	wstring currWscore;
	string userFileStream = "modules\\" + module + "\\users\\" + username + ".xml";
	
	progressVec.push_back("User");
	progressVec.push_back(username);
	
	userxml.Load( StringToWString(userFileStream) );
	userxml.FindElem(MCD_T("USER"));
	userxml.IntoElem();

	userxml.FindElem(MCD_T("FIRSTSCORE"));
	progressVec.push_back("First Score");
	currWscore = userxml.GetData();
	progressVec.push_back(WStringToString(currWscore));

	userxml.FindElem(MCD_T("LASTSCORE"));
	progressVec.push_back("Last Score");
	currWscore = userxml.GetData();
	progressVec.push_back(WStringToString(currWscore));

	userxml.FindElem(MCD_T("PLAYS"));
	progressVec.push_back("Plays");
	currWscore = userxml.GetData();
	progressVec.push_back(WStringToString(currWscore));

	userxml.FindElem(MCD_T("AVERAGESCORE"));
	progressVec.push_back("Average Score");
	currWscore = userxml.GetData();
	progressVec.push_back(WStringToString(currWscore));

	userxml.FindElem(MCD_T("BESTSCORE"));
	progressVec.push_back("Best Score");
	currWscore = userxml.GetData();
	progressVec.push_back(WStringToString(currWscore));

	return progressVec;

}