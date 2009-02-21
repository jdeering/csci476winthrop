#include <iostream>

#include "GameFramework.h"

void mouseCB(int, int, int, int);

int main()
{
	/* NEW INSTANCE OF THE GAME FRAMEWORK */
	GameFramework gf = GameFramework::Instance();

	/* VALID SPRITE */
	GFSprite s1 = gf.createSprite("helloworld", 1, 2, 3, 4);

	/* PRINT REFERENCE NUMBER FOR SPRITE */
	std::cout << s1 << std::endl;

	/* REMOVE THE SPRITE */
	gf.removeSprite(s1);

	/* INVALID SPRITE */
	GFSprite s2 = gf.createSprite("hell world", 0, 6, 6, 6);

	/* CHECK TO SEE IF THE VALUE RETURNED FROM s2 IS NULL */
	if (s2 == GFSprite::null) std::cout << "s2 is nul" << std::endl;

	/* TEXT OBJECT (ASSET) */
	GFText t1 = gf.createTextFromAsset("goodbyeearth", 10, 0, 0);

	/* CHECK TO SEE IF THE VALUE RETURNED FROM t1 IS NULL */
	if (t1 == GFText::null) std::cout << "t1 is nul" << std::endl;

	/* TEXT OBJECT (STRING) */
	GFText t2 = gf.createTextFromString("Call me Ishmael.", 12, 100, 100);

	/* MAKE SOME NOISE */
	GFAudio a1 = gf.createAudio("rickroll.wav");
	
	/* MOUSE CALLBACK HANDLER */
	gf.mouseFunc(mouseCB);
}

void mouseCB(int btn, int state, int x, int y)
{
	std::cout << "Mouse button " << btn << " is now " << state << " @ " << x << ", " << y << std::endl;
}
