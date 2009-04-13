#include "text_handler.h"

/******************************************************
	Default Constructor
******************************************************/
TextHandler::TextHandler()
{
	numObjects = 0;
	readEnabled = false;
}

/******************************************************
	Default Destructor
******************************************************/
TextHandler::~TextHandler()
{		
	text.clear();
	numObjects = 0;
}

/******************************************************
	Adds a text object at the specified key value or updates
	the object currently at that key value.

	@param refName The key value for the text object.
	@param textstd::string The std::string of the text object.
	@param x The x coordinate for the text object's position.
	@param y The y coordinate for the text object's position.
	@param visible <code>true</code> if the text object is to be displayed, <code>false</code> if it only exists to be read
	@return <code>true</code> if the text object is successfully added, <code>false</code> otherwise
******************************************************/
bool TextHandler::AddText(std::string refName, std::string textString, int x, int y, bool visible)
{
	Text temp;
	if(numObjects < MAXFILES)
	{
		temp.LoadText(textString, x, y, visible);
		text[refName] = temp;
		numObjects++;
		return true;
	}
	allegro_message("Text Object %s could not be added.", refName.c_str());
	return false;
}

/******************************************************
	Adds a text object at the specified key value or updates
	the object currently at that key value.

	@param refName The key value for the text object.
	@param instd::string The std::string of the text object.
	@param x The x coordinate for the text object's position.
	@param y The y coordinate for the text object's position.
	@param visible <code>true</code> if the text object is to be displayed, <code>false</code> if it only exists to be read
	@return <code>true</code> if the text object is successfully added, <code>false</code> otherwise
******************************************************/
bool TextHandler::AddText(std::string refName, const char* inString, int x, int y, bool visible)
{
	Text temp;
	std::string textString = inString;
	if(numObjects < MAXFILES)
	{
		temp.LoadText(textString, x, y, visible);
		text[refName] = temp;
		numObjects++;
		return true;
	}
	allegro_message("Text Object %s could not be added.", refName.c_str());
	return false;
}

/******************************************************
	Adds a text object at the specified key value or updates
	the object currently at that key value using the std::string
	specified at the given asset name in the text XML file.

	@param refName The key value for the text object.
	@param assetName The asset name at which to get the std::string for the text object.
	@param x The x coordinate for the text object's position.
	@param y The y coordinate for the text object's position.
	@param visible <code>true</code> if the text object is to be displayed, <code>false</code> if it only exists to be read
	@return <code>true</code> if the text object is successfully added, <code>false</code> otherwise
******************************************************/
bool TextHandler::AddTextByRef(std::string refName, std::string assetName, int x, int y, bool visible)
{
	if(numObjects < MAXFILES)
	{
		if(refName != assetName)
		{
			text[refName] = text[assetName];
			numObjects++;
			return true;
		}
		else
		{
			allegro_message("Text Object reference already exists.");
			return false;
		}
	}
	allegro_message("Text Object %s could not be added.", refName.c_str());
	return false;
}

/******************************************************
	Changes the associated std::string for the text object
	at the specified key value.

	@param refName The key value for the text object.
	@param textstd::string The new std::string for the text object.
	@return <code>true</code> if the text object is successfully updated, <code>false</code> otherwise
******************************************************/
bool TextHandler::ChangeText(std::string refName, std::string textString)
{
	if(text.count(refName) > 0)
	{
		text[refName].ChangeText(textString);
		return true;
	}
	else
	{
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
		return false;
	}
}

/******************************************************
	Removes the text object at the specified key value.

	@param refName The key value for the text object.
	@return <code>true</code> if the text object is successfully removed, <code>false</code> otherwise
******************************************************/
bool TextHandler::RemoveText(std::string refName)
{
	std::map<std::string, Text>::iterator loc = text.find(refName);
	if(numObjects > 0 && loc != text.end())
	{
		text.erase(loc);
		numObjects--;
		return true;
	}
	allegro_message("Text Object %s could not be removed.", refName.c_str());
	return false;
}

/******************************************************
	Displays and/or reads the text object at the specified key value onto
	the specified BITMAP.

	@param refName The key value for the text object.
	@param setVisible Zero if the std::string should only be read, non-zero to display and read.
	@param bmp The BITMAP on which to display the text.
	@return <code>true</code> if the text object is successfully displayed, <code>false</code> otherwise
******************************************************/
bool TextHandler::ShowText(std::string refName, int setVisible, BITMAP *bmp)
{
	if(text.count(refName) > 0)
	{
		if(setVisible)
			text[refName].ShowText(readEnabled, bmp);
		if(readEnabled)
			ReadText(refName);
		return true;
	}
	else
	{
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
		return false;
	}
}

/******************************************************
	Sets a new position for the text object at the specified key value.

	@param refName The key value for the text object.
	@param x The new x coordinate to display the text at.
	@param y The new y coordinate to display the text at.	
******************************************************/
void TextHandler::SetTextPosition(std::string refName, int x, int y)
{
	if(text.count(refName) > 0)
		text[refName].SetPosition(x, y);
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Sets a new position for the text object at the specified key value.

	@param refName The key value for the text object.
	@param x The new x coordinate to display the text at.
	@param y The new y coordinate to display the text at.	
******************************************************/
void TextHandler::SetTTS(bool TTS)
{
	readEnabled = TTS;
}

/******************************************************
	Reads the std::string of the text object at the specified
	key value.

	@param refName The key value for the text object.	
******************************************************/
void TextHandler::ReadText(std::string refName)
{
	if(text.count(refName) > 0)
		text[refName].ReadText();
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Displays and/or reads all the text objects that are visible.

	@param dest The Allegro BITMAP to display the text on.	
******************************************************/
void TextHandler::ShowAllVisible(BITMAP* dest)
{
	for(std::map<std::string, Text>::iterator i = text.begin(); i != text.end(); ++i)
	{
		i->second.ShowText(readEnabled, dest);
	}
}

/******************************************************
	Changes the pixel size of the text object for display.

	@param refName The key value for the text object.
	@param sz The pixel size for the text object.	
******************************************************/
void TextHandler::SetSize(std::string refName, int sz)
{
	if(text.count(refName) > 0)
		text[refName].SetSize(sz);
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Changes the foreground color of the text object for display.

	@param refName The key value for the text object.
	@param r The amount of red (0-255) in the RGB color.	
	@param g The amount of green (0-255) in the RGB color.
	@param b The amount of blue (0-255) in the RGB color.
******************************************************/
void TextHandler::SetColor(std::string refName, int r, int g, int b)
{
	if(text.count(refName) > 0)
		text[refName].SetColor(r, g, b);
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}

/******************************************************
	Changes the background color of the text object for display.

	@param refName The key value for the text object.
	@param r The amount of red (0-255) in the RGB color.	
	@param g The amount of green (0-255) in the RGB color.
	@param b The amount of blue (0-255) in the RGB color.
******************************************************/
void TextHandler::SetBackgroundColor(std::string refName, int r, int g, int b)
{
	if(text.count(refName) > 0)
		text[refName].SetBackgroundColor(r, g, b);
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}


/******************************************************
	Changes the visibility of the text object.

	@param refName The key for the text object.
	@param vis The new visibilty. 0 for invisible, non-zero for visible.	
******************************************************/
void TextHandler::SetVisible(std::string refName, int vis)
{
	if(text.count(refName) > 0)
		text[refName].SetVisible(vis);
	else
		allegro_message("The text object \"%s\" does not exist.", refName.c_str());
}