
#include "user.h"

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

User::User(string usr)
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
}

// Sets the default value of the static variable isLoggedIn to false
// (no one is logged in at first)

int User::setScore(string module, int score)
/** XML FILE PARSER **/
{	
	char* tempPath = _getcwd( NULL, 0 );
	string str_tempPath(tempPath);
	cout << str_tempPath << endl;

// PATH NAMES
	string userFileStream = str_tempPath + "\\modules\\" + module + "\\users\\" + username + ".xml";
	string scoreFileStream = str_tempPath + "\\modules\\" + module + "\\users\\scores.xml";
	cout << userFileStream << endl;



	char dateChar [9];
    char timeChar [9];
	_strdate( dateChar);
	_strtime( timeChar);
	string dateStr(dateChar, 8);
	string timeStr(timeChar, 8);

	ifstream userInp, scoreInp;

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
		newxml << "<USER name=\"" << username << "\">" << endl;
		newxml << "\t<FIRSTSCORE>" << score << "</FIRSTSCORE>" << endl;
		newxml << "\t<LASTSCORE>" << score << "</LASTSCORE>" << endl;
		newxml << "\t<PLAYS>1</PLAYS>" << endl;
		newxml << "\t<TOTALSCORE>" << score << "</TOTALSCORE>" << endl;
		newxml << "\t<AVERAGESCORE>" << score << "</AVERAGESCORE>" << endl;
		newxml << "\t<BESTSCORE>" << score << "</BESTSCORE>" << endl;
		newxml << "<SCORE date=\"" << dateStr << "\" time=\"" << timeStr << "\">" << score << "</SCORE>" << endl;
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
			newxml << "<SCORES number=\"1\">" << endl;
			newxml << "<USER name=\"" << username << "\">" << score << "</USER>" << endl;
			newxml << "</SCORES>" << endl;
			newxml.close(); //close xml file
		}
		else // module's xml file already exists
		{
			CMarkup scorexml;
			wstring currscore, curruser;
			bool inserted = false;
			int count;
			int currCount = 1;
			
			//load the module's xml file
			scorexml.Load( StringToWString(scoreFileStream) );
			scorexml.FindElem( MCD_T("SCORES") );

			count = atoi(WStringToString(scorexml.GetAttrib(MCD_T("number"))).c_str());
			scorexml.SetAttrib( MCD_T("number"), StringToWString(IntToString(count + 1)) );
			cout << count << endl;
			scorexml.IntoElem();
			scorexml.FindElem(MCD_T("USER"));
			
			while(currCount <= count) //iterate through all scores
			{
				currscore = scorexml.GetData();

				if(atoi(WStringToString(currscore).c_str()) > score) //if current score is greater than user's score
				{
						cout << "moving down..." << endl << "Curr score = " << atoi(WStringToString(currscore).c_str()) <<
							"User score = " << score << endl;
						currCount++;
						scorexml.FindElem();
						continue; // continue down the list
				}
				else // user's score is greater than current score
				{
					// insert user's name and score above current record
					// and break from loop
					cout << "score inserted" << endl;
					scorexml.InsertElem( MCD_T("USER"), StringToWString(IntToString(score)) );
					scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				scorexml.AddElem( MCD_T("USER"), StringToWString(IntToString(score)) );
				scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
			}
			
			scorexml.Save(StringToWString(scoreFileStream));
		}
		return 0;
	}
	else //User's XML file does exist
	{
		CMarkup userxml, scorexml;
		int plays;
		int average;
		int totalscore;
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

	//find and add to total score
		userxml.FindElem( MCD_T("TOTALSCORE") );
		tempWstring = userxml.GetData();
		totalscore = (atoi(WStringToString(tempWstring).c_str()));
		totalscore+=score;
		userxml.SetData( StringToWString(IntToString(plays)) );


	//find and recalculate average
		userxml.FindElem( MCD_T("AVERAGESCORE") );
		tempWstring = userxml.GetData();
		string tempAvgstring(tempWstring.begin(), tempWstring.end());
		average = totalscore/plays;
		userxml.SetData( StringToWString(IntToString(average)) );

		userxml.FindElem( MCD_T("BESTSCORE") );
		currscore = userxml.GetData();

		if(score > atoi(WStringToString(currscore).c_str()))
		{	
			int count;
			int currCount = 1;
			userxml.SetData( StringToWString(IntToString(score)) );
		//open scores.xml file
			scorexml.Load( StringToWString(scoreFileStream));
		//find user
			scorexml.FindElem( MCD_T("SCORES") );

			count = atoi(WStringToString(scorexml.GetAttrib(MCD_T("number"))).c_str() );
			scorexml.SetAttrib( MCD_T("number"), StringToWString(IntToString(count + 1)) );

			scorexml.IntoElem();

		//find score
			while(currCount < count) // iterate through all scores
			{
				currscore = scorexml.GetData();
				if(atoi(WStringToString(currscore).c_str()) > score)
				{
						currCount++;
						scorexml.FindElem();
						continue;
				}
				else // if current score is less than user's score, insert
					// user's name and score, and break out of loop
				{
					scorexml.InsertElem( MCD_T("USER"), StringToWString(IntToString(score)) );
					scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
					break;
				}
			}
			if (currCount == count)
			{
				scorexml.AddElem( MCD_T("USER"), StringToWString(IntToString(score)) );
				scorexml.AddAttrib( MCD_T("name"), StringToWString(username) );
			}

			scorexml.Save(StringToWString(scoreFileStream));
		}
		userxml.FindElem(MCD_T("SCORE"));
		for(int i = 1; i < plays-1; i++)
		{
			userxml.FindElem();
		}
		userxml.AddElem(MCD_T("SCORE"), StringToWString(IntToString(score)));
		userxml.AddAttrib(MCD_T("date"), StringToWString(dateStr));
		userxml.AddAttrib(MCD_T("time"), StringToWString(timeStr));


		userxml.Save(StringToWString(userFileStream));
		return 1;
	}
}