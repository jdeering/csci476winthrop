#include "wordplaycontrol.h"

//////////////////////////////
//	click handlers			//
//////////////////////////////

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
//			dialogueClickHandler(x, y, exitGame, endDialogue);
		}
		else if (currentState == DIALOGUE_RESET)
		{
//			dialogueClickHandler(x,y, resetBoard, endDialogue);
		}
	}
}

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
			//go ahead and show instructions for that level
			
			//create background
			background = &GameFramework::createSprite("background", 0, 0, 600, 600);
			background->setVisible(false);
			
			//make the dictionary
			userDictionary = new Dictionary();
			
			//create gameboard
			gameBoard = new Board(gameLevel, userDictionary);
				
			//show instructions
			showInstructions(gameLevel, 1);		//that 1 tells us to show the first page of the instructions
		}
	}
}

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

void WordplayControl::gameboardClickHandler(int x, int y){
	//handle inside of the gameboard
	gameBoard->clickHandler(x,y);

	//update the word if necessary
	currentWord->setContent(gameBoard->returnWord());
}

void WordplayControl::dialogueClickHandler(int x, int y, void (*yesFunction)(), void (*noFunction)())
{
	//if the user clicks yes
	if (x > 50 && x < 200 && y < 400 && y > 450 )
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




void WordplayControl::showInstructions(int gameLevel, int page)
{

	//clear out the screen
	//GameFramework::removeSprite(&overlay);

	std::string assetName;
	//construct the asset name based on the game level and the page number
	switch (gameLevel)
	{
		case 1:
			assetName = "easy_";
			break;
		case 2:
			assetName = "medium_";
			break;
		case 3:
			assetName = "hard_";
			break;
		case 4:
			assetName = "challenge_";
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

	//set the game state to be in the instructions state
	switch (page)
	{
		case 1:
			currentState = INSTRUCTIONS_1;
			break;
		case 2:
			currentState = INSTRUCTIONS_2;
			break;
	}
}



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

bool WordplayControl::returnRunning()
{
	return running;
}

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







void WordplayControl::dialogueBox(string name)
{
	string assetName;
	//construct asset name based on the parameter passed in, and set the game state
	if (name == "reset")
	{
		assetName = "reset";	
		currentState = DIALOGUE_RESET;
	}
	else if (name == "end")
	{
		assetName = "end";
		currentState = DIALOGUE_EXIT;
	}

	//display the dialogue screen
	overlay = &GameFramework::createSprite(assetName, 0,0,600,600);
}

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

	//update the score and current word
//	updateScore();
	currentScore->setContent(strScore);
	currentWord->setContent(gameBoard->returnWord());
}