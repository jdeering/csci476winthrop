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
	bool AddFile(std::string imageRef, std::string filePath, int w, int h, int frame_count, int col_count);
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