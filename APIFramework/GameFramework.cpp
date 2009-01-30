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
	//std::cerr << "ctor for obj @ " << this << std::endl;
}

GameFramework::~GameFramework()
{
	//std::cerr << "dtor for obj @ " << this << std::endl;
}

void GameFramework::kybdFunc(void (*f)(int, int, int, int))
{ cb_KH = f; };

void GameFramework::mouseFunc(void (*f)(int, int, int, int))
{ cb_MH = f; };

void GameFramework::gameFunc(void (*f)())
{ cb_GL = f; };
