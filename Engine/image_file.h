#ifndef _IMAGE_FILE_H
#define _IMAGE_FILE_H

#include "allegro.h"
#include <string>

class ImageFile
{
private:
	std::string filePath;
	int frameWidth, frameHeight;
	int numFrames, numCols;
	BITMAP *img;
public:
	ImageFile();
	ImageFile(std::string filePath, int frame_count, int col_count, int w, int h);
	BITMAP* GetFrame(int frameNum, int width, int height);
	int GetNumFrames();
	int GetNumCols();
	int GetWidth(){ return frameWidth; }	
	int GetHeight(){ return frameHeight; }
};



#endif