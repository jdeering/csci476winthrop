#include "wordplaycontrol.h"

//////////////////////////////
//	click handlers			//
//////////////////////////////

/*********************************************
	All game clicks are passed to this function. No matter which button is clicked, if it is a mousedown (parameter <code>state</state> is 1),
	this function passes it to the correct click handler.

	@param button integer that represents which button is being clicked
	@param state integer that represents which state the mouse is in (up, down)
	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
*********************************************/
void WordplayControl::masterClickHandler(int button, int state, int x, int y)
{
	//1 is clicked, not worrying about which button for the purposes of this game
	if (state == 1){

		//dependent on status, choose the correct click handler
		if (currentState == CHOOSE_LEVEL)
		{
			introClickHandler(x,y);
		}
		else if (currentState == INSTRUCTIONS_1)
		{
			instructionsClickHandler(x, y, 1);
		}
		else if (currentState == INSTRUCTIONS_2)
		{
			instructionsClickHandler (x, y, 2);
		}
		else if (currentState == IN_GAME)
		{
			inGameClickHandler(x,y);
		}
		else if (currentState == DIALOGUE_EXIT)
		{
			dialogueClickHandler(x, y, exitGame, endDialogue);
		}
		else if (currentState == DIALOGUE_RESET)
		{
			dialogueClickHandler(x,y, reset, endDialogue);
		}
	}
}

/*********************************************
	If a click happens while the user is in the introduction screen where they select a level, it is passed to
	this function. If the click falls on any of the buttons for level selection, the background is created (using <code>GFSprite::createSprite</code>),
	the <code>Dictionary</code> is constructed, the <code>Board</code> is generated, and <code>showInstructions</code> is called.

	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
*********************************************/
void WordplayControl::introClickHandler(int x, int y)
{
	//this will hold the game level the user selects
	int gameLevel = -1;

	//if it's in the right y-value for a level button
	if(y > 400 && y < 575)
	{
		//decide which level it is, and select that level
		if(x > 20 && x < 145)
		{
			gameLevel = 1;
		}
		else if (x > 165 && x < 290)
		{
			gameLevel = 2;
		}
		else if (x > 310 && x < 435)
		{
			gameLevel = 3;
		}

		else if (x > 455 && x < 580)
		{
			gameLevel = 4;
		}

		//as long as they clicked on a level button
		if (gameLevel != -1){
	
			//create background
			background = &GameFramework::createSprite("background", 0, 0, 600, 600);
			background->setVisible(false);

			//show loading screen
			GameFramework::removeSprite(*overlay);
			overlay = &GameFramework::createSprite("loading", 0,0,600,600);
			overlay->setVisible(true);

			//make the dictionary
			userDictionary = new Dictionary();
			
			//create gameboard
			gameBoard = new Board(gameLevel, userDictionary);
				
			//show instructions
			showInstructions(gameLevel, 1);		//that 1 tells us to show the first page of the instructions
		}
	}
}

/*********************************************
	All clicks that happen when in the instructions screen are handled with this click handler. The parameter for
	<code>instructionsPage</code> is passed in depending on which instruction screen we're in, which is held in the
	<code>currentState</code> variable. If in the first page, there is only one button to click: a Next button, that will
	display the second instruction page using <code>showInstructions</code>. If in the second page, there is a 
	Previous button, that uses <code>showInstructions</code> to show the first page of instructions, and a Start Game
	button that begins the game by calling <code>beginGame</code>.

	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
	@param instructionsPage current page of instructions, as shown through <code>currentState</code> variable
*********************************************/
void WordplayControl::instructionsClickHandler(int x, int y, int instructionsPage){
	//if we're on the second instructions page, there's a begin game and previous page button
	if (instructionsPage == 2){	
		//if it's the begin game button	
		if(x > 335 && x < 550 && y > 505 && y < 550)
		{
			beginGame();
		}

		//if it's the previous button
		else if(x > 40 && x < 170 && y > 505 && y < 550)
		{
			showInstructions(gameBoard->returnLevel(), 1);
		}
	}

	//if we're on the first instructions page, there's a next button
	else{
		//if it's the 'next' button
		if (x > 420 && x < 545 && y > 505 && y < 550)
		{
			showInstructions(gameBoard->returnLevel(), 2);
		}
	}
}

/*********************************************
	All click events that happen in game are passed to this handler. If the click occurs on the gameboard, it is passed
	to <code>gameboardClickHandler</code>. Otherwise, there are three buttons to be clicked. If the user clicks
	the Submit button, <code>submitWord</code> is called. If Reset or End are clicked, then <code>dialogueBox</code>
	is called with "reset" or "end" as the parameter, respectively.

	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
*********************************************/
void WordplayControl::inGameClickHandler(int x, int y)
{
	//if it's anywhere in the board, let it be handled there
	if(x >= 25 && x <= 475 && y > 25 && y <=475)
	{
		gameboardClickHandler(x,y);
	}

	//if it's the submit word button
	else if(x > 475 && x < 575 && y > 525 && y < 575)
	{
		//let the board class handle it through this function
		submitWord();
	}
	
	//if it's the reset board button
	else if(x > 510 && x < 590 && y > 130 && y < 160)
	{
		dialogueBox("reset");
	}

	//if it's the end game button
	else if (x > 510 && x < 590 && y > 180 && y < 210)
	{
		dialogueBox("end");
	}
}

/*********************************************
	All click events that happen in the gameboard are passed to this handler. It in turn passes it to the <code>clickHandler</code>
	function for the <code>Board</code> associated with the game. Then, the text sprite, <code>currentWord</code>,
	modifies the current word text using <code>GFText::setContent</code>.

	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
*********************************************/
void WordplayControl::gameboardClickHandler(int x, int y){
	//handle inside of the gameboard
	gameBoard->clickHandler(x,y);

	//update the word if necessary
	currentWord->setContent(gameBoard->returnWord());
}

/*********************************************
	All click events that happen in either the reset or the end dialogue boxes are passed here. The other two 
	parameters are what should happen when the Yes and No buttons are clicked.

	@param x x coordinate of mouse event
	@param y y coordinate of mouse event
	@param (*yesFunction)() function that should happen if the user clicks yes
	@param (*noFunction) () functation that should happen if the user clicks no
*********************************************/
void WordplayControl::dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)())
{
	//if the user clicks yes
	if (x > 50 && x < 200 && y > 400 && y < 450 )
	{
		//call the yes function
		yesFunction();
	}

	//if the user clicks no
	else if (x > 300 && x < 450 && y > 400 && y < 450)
	{
		//call the no function
		noFunction();
	}
}



/*********************************************
	Shows the appropriate instructions for the selected game level and page. Uses <code>GameFramework::removeSprite</code> to clear
	out the current overlay screen and <code>gameFramework::createSprite</code> to display the instructions page.

	@param gameLevel current gameplay level
	@param page desired instructions page to be displayed; valid values are 1 and 2
*********************************************/
void WordplayControl::showInstructions(int gameLevel, int page)
{
	std::string assetName;
	
	//these are used for the spoken instructions
	std::string numberPoints;
	std::string numberLetters;
	std::string validTiles;
	std::string replacePolicy;

	//construct the asset name based on the game level and the page number
	switch (gameLevel)
	{
		case 1:
			assetName = "easy_";
			numberPoints = "10";
			numberLetters = "2";
			validTiles = "Click on any letter next to the letter you last clicked to add that letter to the word.";
			replacePolicy ="the letters in that word disappear and are replaced by the letters above them, or by new letters if they are on the top row.";
			break;
		case 2:
			assetName = "medium_";
			numberPoints = "20";
			numberLetters = "3";
			validTiles = "Click on any letter next to the letter you last clicked to add that letter to the word.";
			replacePolicy ="the letters in that word disappear and are replaced by the letters above them, or by new letters if they are on the top row.";
			break;
		case 3:
			assetName = "hard_";
			numberPoints = "30";
			numberLetters = "3";
			validTiles = "Click any letter to the right, left, top, or bottom of the one you just clicked to add it to the word.";
			replacePolicy ="the letters in that word disappear and are replaced by the letters above them, or by new letters if they are on the top row.";
			break;
		case 4:
			assetName = "challenge_";
			numberPoints = "40";
			numberLetters = "3";
			validTiles = "Click any letter to the right, left, top, or bottom of the one you just clicked to add it to the word.";
			replacePolicy ="the letters in that word disappear and are replaced by new letters.";
			break;
	}

	switch (page){
		case 1:
			assetName += "1";
			break;
		case 2:
			assetName += "2";
			break;
	}

	//and display it
	GameFramework::removeSprite(*overlay);
	overlay = &GameFramework::createSprite(assetName, 0, 0, 600, 600);
	overlay->setVisible(true);

	//set the game state to be in the instructions state
	//read the instructions out loud
	std::string instructions1 = 
		"The goal of this game is to spell words by clicking on a sequence of letters on the gameboard. \
		Letters change colors when they are clicked. An unselected letter has a light blue background, \
		a selected letter has a darker blue background, and a selected letter that is part of a valid word \
		is white on a green background." + validTiles;

	std::string instructions2 = 
		"Click on a selected letter to remove it from your word. If there are any other letters after that one\
		they will be removed too. When you are finished making your word, click the Submit Word button.\
		It will only work if your word is " + numberLetters + " long and is in the dictionary.\
		When you submit a word, " + replacePolicy + " For each letter in your word, you will earn " + numberPoints + " points!";

	switch (page)
	{
		case 1:
			currentState = INSTRUCTIONS_1;
			GameFramework::readText(instructions1);
			break;
		case 2:
			currentState = INSTRUCTIONS_2;
			GameFramework::readText(instructions2);
			break;
	}
}


/*********************************************
	This function begins gameplay. It removes the existing overlays using <code>GameFramework::removeSprite</code>,
	displays the gameboard using the board's <code>displayBoard</code> function, and sets up the text objects for
	score and current word using <code>GameFramework::createTextFromString, GameFramework::setTextSize, GameFramework::setTextColor,
	and GameFramework::setVisible</cost>. It also sets <code>currentState</code> to in-game status.

*********************************************/
void WordplayControl::beginGame()
{
	//kill overlay
	GameFramework::removeSprite(*overlay);

	//display the background
	background->setVisible(true);

	//display the gameboard
	gameBoard->displayBoard();

	//display the user score and current word text fields
	GFText & cw = GameFramework::createTextFromString("",40,535);
	GameFramework::setTextSize(cw, 30);
	GameFramework::setTextColor(cw, 0, 0, 0);
	cw.setVisible(true);

	currentWord = &cw;

	GFText & cs = GameFramework::createTextFromString("0", 490, 315);
	GameFramework::setTextSize(cs, 20);
	GameFramework::setTextColor(cs, 0, 0, 0);

	currentScore = &cs;

	//set the state of the game
	currentState = IN_GAME;
}



//////////////////////////////
// gameplay functions		//
//////////////////////////////

/*********************************************
	Displays either the "reset" or "end" dialogue box based on the string passed in as a parameter.
	Dialogue screen is displayed using <code>GameFramework::createSprite</code>, and <code>currentState</code>
	is changed to <code>DIALOGUE_RESET</code> or <code>DIALOGUE_EXIT</code>, depending on the dialogue box.

	@param name name of the dialogue box to be displayed: should be either "reset" or "end".
*********************************************/
void WordplayControl::dialogueBox(string name)
{
	string assetName;
	//construct asset name based on the parameter passed in, and set the game state
	if (name == "reset")
	{
		assetName = "reset";	
		GameFramework::readText("Are you sure you want to reset the gameboard?");
		currentState = DIALOGUE_RESET;
	}
	else if (name == "end")
	{
		assetName = "end";
		GameFramework::readText("Are you sure you want to end this game?");
		currentState = DIALOGUE_EXIT;
	}
	else{
		//we have a problem, return
		return;
	}

	//display the dialogue screen
	overlay = &GameFramework::createSprite(assetName, 0,0,600,600);
}

/*********************************************
	Uses <code>GameFramework::removeSprite</code> to delete the current dialogue box to display the gameplay area.
	Also resets <code>currentState</code> to <code>IN_Game</code>.
*********************************************/
void WordplayControl::endDialogue()
{
	GameFramework::removeSprite(*overlay);
		
	//reset the game state back to gameplay
	currentState = IN_GAME;
}

/*********************************************
	Gets the score for the currently selected word by calling <code>submitWord</code> for the current gameboard.
	The score is then added to the current <code>score</code> variable, and <code>updateTextAssets</code> is called
	so that the current word and score text items are updated.
*********************************************/
void WordplayControl::submitWord()
{
	//submit and score the word
	int wordScore;
	wordScore = gameBoard->submitWord();

	//add to the current score
	score = score + wordScore;
	
	//convert score to string
	string strScore;
	stringstream out;
	out<<score;
	strScore = out.str();

	//read current score
	GameFramework::readText("Your score is now " + strScore + ".");

	updateTextAssets();
}

/*********************************************
	Uses <code>GameFramework::removeSprite</code> to delete the current dialogue box to display the gameplay area.
	Calls <code>reset</code> for the current gameboard, subtracts 50 from <code>score</code> and calls <code>updateTextAssets</code>
	so that the current word and score are updated. Also resets <code>currentState</code> to <code>IN_GAME</code>.
*********************************************/
void WordplayControl::reset()
{
	GameFramework::removeSprite(*overlay);

	gameBoard->reset();
	score = score - 50;
	updateTextAssets();

	//convert score to string
	string strScore;
	stringstream out;
	out<<score;
	strScore = out.str();

	//read user the text
	GameFramework::readText("Your gameboard was reset, costing you 50 points.");
	GameFramework::readText("Your score is now " + strScore + ".");

	currentState = IN_GAME;
}

/*********************************************
	Converts <code>score</code> to a string and updates <code>currentScore</code> using <code>GFText::setContent</code>.
	Also updates the content of <code>currentWord</code> by calling <code>returnWord</code> for the gameboard and using 
	<code>GFText::setContent</code>.
*********************************************/
void WordplayControl::updateTextAssets()
{
	//convert score to string
	string strScore;
	stringstream out;
	out<<score;
	strScore = out.str();

	//update the score and current word
	currentScore->setContent(strScore);
	currentWord->setContent(gameBoard->returnWord());
}

//////////////////////////////////////
//		framework integration		//
//////////////////////////////////////

/*********************************************
	Returns the value of <code>running</code>. This is used for the API callback function that
	determines whether to exit the game or not--<code>GameFramework::gameFunc</code>.

*********************************************/
bool WordplayControl::returnRunning()
{
	return running;
}

/*********************************************
	Starts the game running by creating the initial overlay using <code>GameFramework::CreateSprite</code> and
	setting <code>running</code> to true. To begin the game, it defines the click handler through <code>GameFramework::mouseFunc</code>
	and the game function through <code>GameFramework::gameFunc</code>. Finally, <code>GameFramework::gameLoop</code> is called and
	the game begins.
*********************************************/
void WordplayControl::start(){
	currentState = CHOOSE_LEVEL;

	//display the beginning screen
	overlay = &GameFramework::createSprite("intro",0,0,600,600);

	srand(time(0));
	running = true;

	//set the correct click handler
	GameFramework::mouseFunc(masterClickHandler);
	
	//begin the game loop
	GameFramework::gameFunc(returnRunning);
	
	GameFramework::gameLoop();
}

/*********************************************
	Sends scores back to the API and sets <code>running</code> to false so that the game exits.
*********************************************/
void WordplayControl::exitGame()
{
	//send the score back to the framework
	/////api

	//end game
	running = false;
}