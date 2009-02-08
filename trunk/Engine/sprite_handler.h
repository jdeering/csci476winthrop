#ifndef _SPRITE_HANDLER_H
#define _SPRITE_HANDLER_H

#include "sprite.h"
#include "image_file.h"
#include <list>
#include <map>

#define MAXSPRITES 500
#define MAXFILES 100

class SpriteHandler
{
private:
	// Sprite Container
	std::map<int, Sprite> sprites;
	// Bitmap Files
	std::map<std::string, ImageFile> files;
	
	int numSprites, numFiles;
public:
	SpriteHandler();
	~SpriteHandler();

	// Sprite updater
	bool RemoveSprite(int refNum);
	bool AddSprite(int refNum, std::string imageRef, int x, int y, int w, int h);
	void DrawSprites(BITMAP*);
	bool AddFile(std::string imageRef, std::string filePath, int w, int h, int frame_count, int col_count);
	bool RemoveFile(std::string imageRef);

	// Sprite moving/animating
	void MoveSprite(int refNum, int new_x, int new_y, int speed){ sprites[refNum].MoveTo(new_x, new_y, speed); }

	// Sprite searching
	std::list<Sprite>::iterator Find(int refNum); // algorithm find (returns iterator)
};


#endif