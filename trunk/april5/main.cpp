#include <iostream>
#include "user.h"
#include <time.h>
#include <stdlib.h>
#include <direct.h>

using namespace std;

int main()
{
// Example setScore code
	User usera("Andrew");
	usera.setScore("thisgame", 5100);
// SetScore parameters:
	// module = "thisgame"
	// score = 5100
	// These directories MUST be already exist, or the files
	// will not be created.
	return 0;
}