#include "image_file.h"


ImageFile::ImageFile()
{
	img = NULL;
}

ImageFile::ImageFile(std::string file, int frame_count, int col_count, int w, int h)
{	
	filePath = file;
	frameWidth = w;
	frameHeight = h;
	numFrames = frame_count;
	numCols = col_count;
	img = load_bitmap(filePath.c_str(), NULL);
	if(!img)
	{
		char* msg = "Could not find file ";
		strcat(msg, filePath.c_str());
		allegro_message(msg);
	}
}

BITMAP* ImageFile::GetFrame(int frameNum, int width, int height)
{
	if(img == NULL) return img;
	BITMAP *retImg;
	retImg = create_bitmap(frameWidth, frameHeight);
	int s_x, s_y;
	s_x = (frameNum % numCols) * frameWidth;
	s_y = (frameNum / numCols) * frameHeight;	
	stretch_blit(img, retImg, s_x, s_y, frameWidth, frameHeight, 0, 0, width, height);
	return retImg;
}

int ImageFile::GetNumFrames()
{ 
	return numFrames; 
}

int ImageFile::GetNumCols()
{ 
	return numCols; 
}