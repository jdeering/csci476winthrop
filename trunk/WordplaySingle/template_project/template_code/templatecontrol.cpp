#include "templatecontrol.h"

//////////////////////////////
//	click handlers			//
//////////////////////////////

void TemplateControl::masterClickHandler(int button, int state, int x, int y)
{

}

//////////////////////////////////////
//		framework integration		//
//////////////////////////////////////

/*********************************************
	Returns the value of <code>running</code>. This is used for the API callback function that
	determines whether to exit the game or not--<code>GameFramework::gameFunc</code>.

*********************************************/
bool TemplateControl::returnRunning()
{
	return running;
}

/*********************************************
	Starts the game running by creating the initial overlay using <code>GameFramework::CreateSprite</code> and
	setting <code>running</code> to true. To begin the game, it defines the click handler through <code>GameFramework::mouseFunc</code>
	and the game function through <code>GameFramework::gameFunc</code>. Finally, <code>GameFramework::gameLoop</code> is called and
	the game begins.
*********************************************/
void TemplateControl::start(){
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
void TemplateControl::exitGame()
{
	//send the score back to the framework
	GameFramework::score = score;

	//end game
	running = false;
}