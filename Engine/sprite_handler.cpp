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


bool SpriteHandler::RemoveSprite(std::string refName)
{
	std::map<std::string, Sprite>::iterator loc = sprites.find(refName);
	if(numSprites > 0 && loc != sprites.end())
	{
		sprites.erase(loc);
		numSprites--;
		return true;
	}
	return false;
}
bool SpriteHandler::AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h)
{
	if(numSprites < MAXSPRITES)
	{
		Sprite temp(imageRef, x, y, w, h);
		temp.SetFrameCount(files[imageRef].GetNumFrames());
		temp.SetColumnCount(files[imageRef].GetNumCols());
		sprites[refName] = temp;
		numSprites++;	
		return true;
	}
	else
	{
		allegro_message("Sprite cannot be added.");
		return false;
	}
}

bool SpriteHandler::AddSprite(std::string refName, std::string imageRef, int x, int y)
{
	if(numSprites < MAXSPRITES)
	{
		Sprite temp(imageRef, x, y, files[imageRef].GetWidth(), files[imageRef].GetHeight());
		temp.SetFrameCount(files[imageRef].GetNumFrames());
		temp.SetColumnCount(files[imageRef].GetNumCols());
		sprites[refName] = temp;
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
	BITMAP *temp = NULL;
	for(std::map<std::string, Sprite>::iterator i = sprites.begin(); i != sprites.end(); ++i)
	{
		if(i->second.isAlive())
		{
			i->second.Update();
			refName = i->second.GetSheetRef();
			frame = i->second.GetFrameNum();
			temp = files[refName].GetFrame(frame, i->second.GetWidth(), i->second.GetHeight());
			i->second.Draw(temp, buffer);
		}
		else
		{
			sprites.erase(i);
		}
	}
	if(temp)
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

std::string SpriteHandler::CheckClicks(BoundingBox &pointer)
{
	std::string sprite_name = "";
	for(std::map<std::string, Sprite>::reverse_iterator i = sprites.rbegin(); i != sprites.rend(); ++i)
	{
		if(i->second.isColliding(pointer))
		{
			sprite_name = i->first;
			break;
		}
	}
	return sprite_name;
}

void SpriteHandler::SetSpriteSize(std::string refName, int w, int h)
{
	sprites[refName].SetSize(w, h);
}

void SpriteHandler::SetSpriteLocation(std::string refName, int x, int y)
{
	sprites[refName].SetPosition(x, y);
}

void SpriteHandler::SetVisible(std::string refName, int visible)
{
	sprites[refName].SetVisible(visible);
}

void SpriteHandler::SetFrameDelay(std::string refName, int delay)
{
	sprites[refName].SetFrameDelay(delay);
}

void SpriteHandler::SetAnimation(std::string refName, int animate)
{
	sprites[refName].SetAnimation(animate);
}

void SpriteHandler::SetFrame(std::string refName, int frame)
{
	sprites[refName].SetFrame(frame);
}
