#include "user.h"
#include <iostream>

using namespace std;

int main()
{
	char choice, subchoice;
	string usr, pwd, verpwd;
	int failnum;
	choice = 'z';
	subchoice = 'z';

	while(choice != 'X' && choice != 'x' && subchoice != 'X' && subchoice != 'x')
	{
		subchoice = 'z';

		cout << "**************************************" << endl;
		cout << "* OPG Login Program  (Test)   ********" << endl;
		cout << "**************************************" << endl;
		cout << "**************************************" << endl << endl;
		cout << "L\tLogin" << endl;
		cout << "C\tCreate User" << endl;
		cout << "X\tExit" << endl << endl;

		cout << "What would you like to do? ";
		cin >> choice;

		switch(choice)
		{
		case 'l':
		case 'L':
			cout << "---Login---" << endl << endl;
			cout << "Username: ";
			cin >> usr;
			cout << "Password: ";
			cin >> pwd;

			try{
				User usera(usr, pwd);
				
				while(subchoice != 'x' && subchoice != 'X' && subchoice != 'l' && subchoice != 'L')
				{
					cout << "**************************************" << endl;
					cout << "* OPG Login Program  (Test)   ********" << endl;
					cout << "**************************************" << endl;
					cout << "**************************************" << endl << endl;
					cout << "User: " << usera.getUserName() << " logged in!"<< endl;
					cout << "**************************************" << endl << endl;
					cout << "L\tLogout" << endl;
					cout << "X\tExit" << endl << endl;
					
					cout << "What would you like to do? ";
					cin >> subchoice;
					
					switch(subchoice)
					{
					case 'l':
					case 'L':
						usera.logout();
						cout << "Logged out successfully!" << endl << endl;
						break;
					case 'x':
					case 'X':
						cout << "Bye!" << endl;
						break;
					default:
						cout << "Invalid choice!  Try again." << endl << endl;
					}
				}
			}
			catch(int ExLoginSuccess)
			{
				cout << "Username or password do not match!  Try again. (Login code: " << ExLoginSuccess << ")" << endl;
			}
			break;
		case 'c':
		case 'C':
			cout << "---Create User---" << endl << endl;
			cout << "Username: ";
			cin >> usr;
			cout << "Password: ";
			cin >> pwd;
			cout << "Verify Password: ";
			cin >> verpwd;

			failnum = createUser(usr,pwd,verpwd);

			if(failnum == 1)
				cout << "User \"" << usr << "\" created successfully!" << endl << endl;
			else if(failnum == 0)
				cout << "Passwords do not match, try again!" << endl << endl;
			else
				cout << "User already exists!  Try another username." << endl << endl;
			break;
		case 'x':
		case 'X':
			cout << "Bye!" << endl;
			break;
		default:
			cout << "Invalid choice!  Try again." << endl << endl;
		}

		
	}

	return 0;
}