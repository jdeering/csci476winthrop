/*
Jason Deering

sprite_handler.h

This class is for use in the Framework.

It requires the C++ STL map class file reference and sprite containers.

The SpriteHandler class controls the display and changing of all sprites and bitmap image files.


DATA ITEMS
	std::map<std::string, Sprite> sprites - container for all active sprites 
	std::map<std::string, ImageFile*> files - container for all files that may be used by the framework a module
	
	int numSprites - the number of sprites currently in the sprite container
	int numFiles - the number of files currently in image file container

FUNCTIONS
	bool RemoveSprite(std::string refName) - removes the sprite from the container at key refName. 
												Returns success or fail as a boolean.
	bool AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h) - adds a sprite to the container
			with the specified properties to the key refName. Returns success or fail as a boolean.
	bool AddSprite(std::string refName, std::string imageRef, int x, int y) - adds a sprite to the container
			with the specified properties to the key refName. Uses the width and height parameters of the image
			file specified by imageRef for use in the sprite. Returns success or fail as a boolean.
	DrawSprites(BITMAP* dest) - draws all active sprites to the dest parameter
	bool AddFile(std::string imageRef, std::string filePath, int w, int h, int frame_count, int col_count) -
					adds the image file referenced by the key imageRef to container with the specified properties
						returns success or fail as a boolean
	bool RemoveFile(std::string imageRef) - removes the image file referenced by the key imageRef in the container
												returns success or fail as a boolean

	MoveSprite(std::string refName, int new_x, int new_y, int speed) - calls the Sprite class's move function for
					the sprite at key refName using the remaining parameters
	SetSpriteSize(std::string refName, int w, int h) - calls the Sprite class's set size function for
					the sprite at key refName using the remaining parameters
	SetSpriteLocation(std::string refName, int x, int y) - calls the Sprite class's set location function for
					the sprite at key refName using the remaining parameters
	SetVisible(std::string refName, int visible) - calls the Sprite class's set visible function for
					the sprite at key refName using the remaining parameter
	SetFrameDelay(std::string refName, int delay) - calls the Sprite class's frame delay function for
					the sprite at key refName using the remaining parameter
	SetAnimation(std::string refName, int animate) - calls the Sprite class's set animate function for
					the sprite at key refName using the remaining parameter
	SetFrame(std::string refName, int frame) - calls the Sprite class's set frame function for
					the sprite at key refName using the remaining parameter
	ChangeBitmap(std::string refName, std::string fileRef) - calls the Sprite class's change bitmap function for
					the sprite at key refName using the remaining parameter

	CheckClicks(BoundingBox &pointer) - checks collision detection of the mouse pointer on a sprite on clicks
										 returns a std::string reference to the sprite

*/

#ifndef _SPRITE_HANDLER_H
#define _SPRITE_HANDLER_H

#include "sprite.h"
#include "image_file.h"
#include "globals.h"


#define MAX_SPRITES 500

class SpriteHandler
{
private:
	// Sprite Container
	std::map<std::string, Sprite> sprites;
	// Bitmap Files
	std::map<std::string, ImageFile*> files;
	
	int numSprites, numFiles;
public:
	SpriteHandler();
	~SpriteHandler();

	// Sprite updater
	bool RemoveSprite(std::string refName);
	bool AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h);
	bool AddSprite(std::string refName, std::string imageRef, int x, int y);
	void DrawSprites(BITMAP*);
	bool AddFile(std::string imageRef, std::string filePath, int frame_count, int col_count, int w, int h);
	bool RemoveFile(std::string imageRef);

	// Sprite moving/animating
	void MoveSprite(std::string refName, int new_x, int new_y, int speed){ sprites[refName].MoveTo(new_x, new_y, speed); }
	void SetSpriteSize(std::string refName, int w, int h);
	void SetSpriteLocation(std::string refName, int x, int y);
	void SetVisible(std::string refName, int visible);
	void SetFrameDelay(std::string refName, int delay);
	void SetAnimation(std::string refName, int animate);
	void SetFrame(std::string refName, int frame);
	void ChangeBitmap(std::string refName, std::string fileRef);

	// Check Mouse Clicks on Sprites
	std::string CheckClicks(BoundingBox &pointer);
};


#endif