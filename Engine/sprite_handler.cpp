#include "sprite_handler.h"

SpriteHandler::SpriteHandler()
{
	numSprites = 0;
	numFiles = 0;
}

SpriteHandler::~SpriteHandler()
{
	sprites.clear();
	for(std::map<std::string, ImageFile>::iterator i = files.begin(); i != files.end(); ++i)
	{
		i->second.~ImageFile();
	}
	numFiles = 0;
	numSprites = 0;
}


bool SpriteHandler::RemoveSprite(int refNum)
{
	std::map<int, Sprite>::iterator loc = sprites.find(refNum);
	if(numSprites > 0 && loc != sprites.end())
	{
		sprites.erase(loc);
		numSprites--;
		return true;
	}
	return false;
}
bool SpriteHandler::AddSprite(int refNum, std::string imageRef, int x, int y, int w, int h)
{
	if(numSprites < MAXSPRITES)
	{
		Sprite temp(imageRef, x, y, w, h);
		temp.SetFrameCount(files[imageRef].GetNumFrames());
		temp.SetColumnCount(files[imageRef].GetNumCols());
		sprites[refNum] = temp;
		numSprites++;	
		return true;
	}
	else
	{
		allegro_message("Sprite cannot be added.");
		return false;
	}
}

void SpriteHandler::DrawSprites(BITMAP *buffer)
{
	std::string refName = "";
	int frame = 0;
	BITMAP *temp;
	for(std::map<int, Sprite>::iterator i = sprites.begin(); i != sprites.end(); ++i)
	{
		i->second.Update();
		refName = i->second.GetSheetRef();
		frame = i->second.GetFrameNum();
		temp = files[refName].GetFrame(frame, i->second.GetWidth(), i->second.GetHeight());
		i->second.Draw(temp, buffer);
	}
	destroy_bitmap(temp);
}

bool SpriteHandler::AddFile(std::string imageRef, std::string filePath, int w, int h, int frame_count, int col_count)
{
	if(numFiles < MAXFILES)
	{
		ImageFile temp(filePath, w, h, frame_count, col_count);
		files.insert(std::pair<std::string, ImageFile>(imageRef, temp));
		numFiles++;
		return true;
	}
	return false;
} 


bool SpriteHandler::RemoveFile(std::string imageRef)
{
	std::map<std::string, ImageFile>::iterator loc = files.find(imageRef);
	if(numFiles > 0 && loc != files.end())
	{
		files.erase(loc);
		numSprites--;
		return true;
	}
	return false;
}