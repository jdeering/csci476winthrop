#include "engine.h"

Framework* Framework::inst = NULL;

Framework* Framework::Instance()
{
	if(!Framework::inst)
	{
		Framework::inst = new Framework;
	}
	return Framework::inst;
}

Framework::Framework()
{
	buffer = create_bitmap(800, 600);
	active = true;
}

Framework::~Framework()
{
	destroy_bitmap(buffer);
	active = false;
}


void Framework::LoadImages(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	imgXML.Load(file);
	LoadImages();
}

void Framework::LoadAudio(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	audXML.Load(file);
	LoadAudio();
}

void Framework::LoadText(std::string file_name)
{
	std::wstring file(file_name.begin(), file_name.end());
	txtXML.Load(file);
	LoadText();
}

void Framework::LoadImages()
{
	BITMAP *temp = NULL;
	imgXML.FindElem();

	while(imgXML.FindChildElem(TEXT("image")))
	{
		imgXML.IntoElem();
		// Get attributes
		std::wstring atFile = imgXML.GetAttrib(TEXT("file"));
		std::wstring atRef = imgXML.GetAttrib(TEXT("ref"));
		std::wstring atNumFrames = imgXML.GetAttrib(TEXT("numFrames"));
		std::wstring atNumFrameCol = imgXML.GetAttrib(TEXT("numFrameCol"));
		std::wstring atWidth = imgXML.GetAttrib(TEXT("frameWidth"));
		std::wstring atHeight = imgXML.GetAttrib(TEXT("frameHeight"));
		// Set variables for attributes
		std::string file(atFile.begin(), atFile.end());
		std::string ref(atRef.begin(), atRef.end());
		std::string numFrames(atNumFrames.begin(), atNumFrames.end());
		std::string numFrameCol(atNumFrameCol.begin(), atNumFrameCol.end());
		std::string width(atWidth.begin(), atWidth.end());
		std::string height(atHeight.begin(), atHeight.end());
		imgXML.OutOfElem();
		
		// Add file to sprite handler
		sprites.AddFile(ref, file, atoi(numFrames.c_str()), atoi(numFrameCol.c_str()), atoi(width.c_str()), atoi(height.c_str()));
	}
	destroy_bitmap(temp);
}

void Framework::LoadAudio(){}
void Framework::LoadText(){}

void Framework::UpdateSprites()
{
	clear_to_color(buffer, makecol(255, 255, 255));
	sprites.DrawSprites(buffer);
}

void Framework::MessageLoop()
{
	if(key[KEY_ESC])
		active = false;
	UpdateSprites();
	sprites.MoveSprite(100, 401, 301, 10);
}

void Framework::MainLoop()
{
	MessageLoop();
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}
