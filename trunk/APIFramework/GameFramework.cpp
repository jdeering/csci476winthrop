#include <iostream>
#include "GameFramework.h"

int const GameFramework::GFS_MAX = 500;
int const GameFramework::GFT_MAX = 50;
int const GameFramework::GFA_MAX = 50;

GameFramework& GameFramework::Instance()
{
	static GameFramework inst;
	return inst;
}
	
GameFramework::GameFramework()
{
	/* EMPTY THE BUFFER */
	_clrBuffer();

	/* COUNT OF GF OBJECTS THAT HAVE BEEN CREATED */
	gft_count = gft_total = 0;
	gfa_count = gfa_total = 0;
	gfs_count = gfs_total = 0;

	/* ITERATION VALUES FOR GF OBJECTS */
	gfti =   0;
	gfai = 100;
	gfsi = 200;
}

GameFramework::~GameFramework()
{
	/* EMPTY THE BUFFER */
	_clrBuffer();
}

void GameFramework::_clrBuffer()
{ memset(_msgBuffer, 0, GFW_BUFFER_SIZE); };

void GameFramework::kybdFunc(void (*f)(int, int, int, int))
{ cb_KH = f; };

void GameFramework::mouseFunc(void (*f)(int, int, int, int))
{ cb_MH = f; };

void GameFramework::gameFunc(bool (*f)())
{ cb_GL = f; };

void GameFramework::gameLoop()
{ while (cb_GL()); }

GFSprite& GameFramework::createSprite(std::string asset, int x, int y, int w, int h)
{
	/* IF THERE ARE SPACES IN THE ASSET NAME, EXIT AS GRACEFULLY AS POSSIBLE */
	if (asset.find(' ') == std::string::npos)
	{ std::cerr << "Malformed Asset Name: " << asset << std::endl; return (GFSprite&)GFSprite::nul; };

	/* CREATE THE MESSAGE BUFFER TO SEND THE DATA TO THE FRAMEWORK */
	sprintf(_msgBuffer, "301 %d %s %d %d %d %d", gfsi, asset.c_str(), x, y, w, h);

	/* SEND THE MESSAGE TO THE FRAMEWORK */
	std::cout << _msgBuffer << std::endl;
}

GFText& GameFramework::createTextFromAsset(std::string, int, int, int)
{

}

GFText& GameFramework::createTextFromString(std::string, int, int, int)
{

}

GFAudio& GameFramework::createAudio(std::string, int, int)
{

}
