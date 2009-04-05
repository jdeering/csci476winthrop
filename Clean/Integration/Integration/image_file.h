/*
Jason Deering

image_file.h

This class is for use in the Framework.

It requires Allegro header files included for the BITMAP struct.

The ImageFile class controls the information for each bitmap file that may be displayed
by the Framework and is used to provide sprites with their current frame to draw.

DATA ITEMS
	std::string filePath - the path to the associated bitmap file
	int frameWidth - width of one frame of animation in the file
	int frameHeight - height of one frame of animation in the file
	int numFrames - number of frames of animation provided in the bitmap file
	int numCols - max number of columns of frames in the bitmap file
	BITMAP *img - pointer to the BITMAP struct loaded from the associated bitmap file

FUNCTIONS
	BITMAP* GetFrame(int frameNum, int width, int height) - returns a BITMAP pointer that contains
			the specified frame of animation at a stretched or condensed size of width and height specified
	int GetNumFrames() - returns the number of frames for animation
	int GetNumCols() - returns the number of columns of frames
	int GetWidth() - returns the width of a frame of animation
	int GetHeight() - returns the height of a frame of animation
	bool isValid() - returns true if the BITMAP pointer is valid and able to be referenced

*/

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
	~ImageFile();
	ImageFile(std::string filePath, int frame_count, int col_count, int w, int h);
	BITMAP* GetFrame(int frameNum, int width, int height);
	int GetNumFrames();
	int GetNumCols();
	int GetWidth();
	int GetHeight();
	bool isValid();
};



#endif