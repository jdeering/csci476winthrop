#include "sprite_handler.h"

/******************************************************
	Default Constructor
******************************************************/
SpriteHandler::SpriteHandler()
{
	numSprites = 0;
	numFiles = 0;
}

/******************************************************
	Default Destructor
******************************************************/
SpriteHandler::~SpriteHandler()
{
	sprites.clear();
	for(std::map<std::string, ImageFile*>::iterator i = files.begin(); i != files.end(); ++i)
	{
		i->second->~ImageFile();
	}
	numFiles = 0;
	numSprites = 0;
}

/******************************************************
	Removes the sprite object from the container at the
	specified key value.

	@param refName The key value of the sprite to remove
	@return true if successful, false otherwise
******************************************************/
bool SpriteHandler::RemoveSprite(std::string refName)
{
	std::map<std::string, Sprite>::iterator loc = sprites.find(refName);
	if(numSprites > 0 && loc != sprites.end())
	{
		sprites[refName].SetAlive(false);
		sprites.erase(loc);
		numSprites--;
		return true;
	}
	return false;
}

/******************************************************
	Adds a sprite object to the container at the
	specified key value, or updates the sprite at the key
	value if it is already in use.

	@param refName The key value of the sprite to add or update
	@param imageRef The key value of the bitmap file to associate with the <code>Sprite</code>
	@param x The initial x-coordinate of the <code>Sprite</code>
	@param y The initial y-coordinate of the <code>Sprite</code>
	@param w The initial width in pixels of the <code>Sprite</code>
	@param h The initial height in pixels of the <code>Sprite</code>
	@return true if successful, false otherwise
******************************************************/
bool SpriteHandler::AddSprite(std::string refName, std::string imageRef, int x, int y, int w, int h)
{
	if(numSprites < MAXSPRITES)
	{
		if(files.count(imageRef) > 0)
		{
			Sprite temp(imageRef, x, y, w, h);
			temp.SetFrameCount(files[imageRef]->GetNumFrames());
			sprites[refName] = temp;
			numSprites++;
			return true;
		}
		else
		{
			allegro_message("Image file reference \"%s\" not found.", imageRef.c_str());
			return false;
		}
	}
	else
	{
		allegro_message("Sprite cannot be added.");
		return false;
	}
}

/******************************************************
	Adds a sprite object to the container at the
	specified key value, or updates the sprite at the key
	value if it is already in use. Uses the specified bitmap file's
	width and height as the sprite's width and height.

	@param refName The key value of the sprite to add or update
	@param imageRef The key value of the bitmap file to associate with the <code>Sprite</code>
	@param x The initial x-coordinate of the <code>Sprite</code>
	@param y The initial y-coordinate of the <code>Sprite</code>
	@return true if successful, false otherwise
******************************************************/
bool SpriteHandler::AddSprite(std::string refName, std::string imageRef, int x, int y)
{
	if(numSprites < MAXSPRITES)
	{
		if(files.count(imageRef) > 0)
		{
			Sprite temp(imageRef, x, y, files[imageRef]->GetWidth(), files[imageRef]->GetHeight());
			temp.SetFrameCount(files[imageRef]->GetNumFrames());
			sprites[refName] = temp;
			numSprites++;	
			return true;
		}
		else
		{
			allegro_message("Image file reference \"%s\" not found.", imageRef.c_str());
			return false;
		}
	}
	else
	{
		allegro_message("Sprite cannot be added.");
		return false;
	}
}

/******************************************************
	Draws the current frame of all active sprites to the specified
	BITMAP buffer. Removes all inactive sprites from the container
	after updating.

	@param buffer Pointer to the Allegro BITMAP struct that sprites should be drawn to
******************************************************/
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
			temp = files[refName]->GetFrame(frame, i->second.GetWidth(), i->second.GetHeight());	
			if(temp == NULL)
				allegro_message("Error generating Frame %d for sprite reference \"%s\".", frame, i->first);
			else
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

/******************************************************
	Adds a file object to the container at the
	specified key value, or updates the file at the key
	value if it is already in use.

	@param imageRef The key value of the file to add or update
	@param filePath The file path of the bitmap file to load
	@param frame_count The number of animation frames in the file
	@param col_count The number of columns of animation frames in the file
	@param w The initial width in pixels of a frame of animation
	@param h The initial height in pixels of a frame of animation
	@return true if successful, false otherwise
******************************************************/
bool SpriteHandler::AddFile(std::string imageRef, std::string filePath, int frame_count, int col_count, int w, int h)
{
	if(numFiles < MAXFILES)
	{
		ImageFile* temp = new ImageFile(filePath, frame_count, col_count, w, h);
		if(temp->isValid())
		{
			files.insert(pair<std::string, ImageFile*>(imageRef, temp));
			numFiles++;
			return true;
		}
		else
			allegro_message("The file referenced by %s could not be found at %s.", imageRef.c_str(), filePath.c_str());
	}
	return false;
} 

/******************************************************
	Removes the file object from the container at the
	specified key value.

	@param imageRef The key value of the file to remove
	@return <code>true</code> if successful, <code>false</code> otherwise
******************************************************/
bool SpriteHandler::RemoveFile(std::string imageRef)
{
	std::map<std::string, ImageFile*>::iterator loc = files.find(imageRef);
	if(numFiles > 0 && loc != files.end())
	{
		files.erase(loc);
		numFiles--;
		return true;
	}
	return false;
}

/******************************************************
	Checks whether or not any of the active sprites have been
	clicked or released on by the mouse pointer.

	@param pointer Reference to the <code>BoundingBox</code> of the mouse pointer
	@return The key value of the most recently added sprite (hopefully top sprite) being clicked or released on
******************************************************/
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

/******************************************************
	Resizes the <code>Sprite</code> at the specified key
	value.
	
	@param refName Key value of the <code>Sprite</code> to resize
	@param w The new width for the <code>Sprite</code>
	@param h The new height for the <code>Sprite</code>
******************************************************/
void SpriteHandler::SetSpriteSize(std::string refName, int w, int h)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetSize(w, h);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the new position for the <code>Sprite</code> 
	at the specified key value.
	
	@param refName Key value of the <code>Sprite</code> to relocate
	@param x The new x coordinate for the <code>Sprite</code>
	@param y The new y coordinate for the <code>Sprite</code>
******************************************************/
void SpriteHandler::SetSpriteLocation(std::string refName, int x, int y)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetPosition(x, y);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the visibility of the <code>Sprite</code> 
	at the specified key value.
	
	@param refName Key value of the <code>Sprite</code>
	@param visible The new visibility value for the <code>Sprite</code>
******************************************************/
void SpriteHandler::SetVisible(std::string refName, int visible)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetVisible(visible);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the frame delay of the <code>Sprite</code> 
	at the specified key value.
	
	@param refName Key value of the <code>Sprite</code>
	@param delay The new frame delay value for the <code>Sprite</code>
******************************************************/
void SpriteHandler::SetFrameDelay(std::string refName, int delay)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetFrameDelay(delay);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the frame delay of the <code>Sprite</code> 
	at the specified key value and starts animating
	the <code>Sprite</code>.
	
	@param refName Key value of the <code>Sprite</code>
	@param animate The new frame delay value for the <code>Sprite</code>.
					0 or less stops animation.
******************************************************/
void SpriteHandler::SetAnimation(std::string refName, int animate)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetAnimation(animate);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the current frame of animation for the <code>Sprite</code> 
	at the specified key value.
	
	@param refName Key value of the <code>Sprite</code>
	@param frame The frame of animation to display.
******************************************************/
void SpriteHandler::SetFrame(std::string refName, int frame)
{
	if(sprites.count(refName) > 0)
		sprites[refName].SetFrame(frame);
	else
		allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets the associated bitmap file for the <code>Sprite</code> 
	at the specified key value.
	
	@param refName Key value of the <code>Sprite</code>
	@param fileRef The <code>ImageFile</code> container key value for the bitmap.
******************************************************/
void SpriteHandler::ChangeBitmap(std::string refName, std::string fileRef)
{
	if(files.count(fileRef) > 0)
	{
		if(sprites.count(refName) > 0)
			sprites[refName].ChangeBitmap(fileRef);
		else
			allegro_message("Sprite \"%s\" does not exist.", refName.c_str());
	}
	else
	{
		allegro_message("Image file reference \"%s\" not found.", fileRef.c_str());
	}
}