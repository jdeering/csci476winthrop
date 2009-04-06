#include "image_file.h"


/******************************************************
	Default Constructor
******************************************************/
ImageFile::ImageFile()
{
	img = NULL;
}

/******************************************************
	Constructor to set the class data to the specified values.
	
	@param file The file path for the bitmap file associated with the object.
	@param frame_count The number of frames of animation in the file.
	@param col_count The number of columns of frames in the file.
	@param w The width of a single animation frame.
	@param h The height of a single animation frame. 
******************************************************/
ImageFile::ImageFile(std::string file, int frame_count, int col_count, int w, int h)
{	
	img = NULL;
	filePath = file;
	frameWidth = w;
	frameHeight = h;
	numFrames = frame_count;
	numCols = col_count;
	img = load_bitmap(filePath.c_str(), NULL);
	if(!img)
	{
		allegro_message("Could not find image file reference \"%s\"", file.c_str());
	}
}

/******************************************************
	Default Destructor. 
	Ensures that the associated BITMAP* memory is released.
******************************************************/
ImageFile::~ImageFile()
{
	if(img)
		destroy_bitmap(img);
}

/******************************************************
	Returns a BITMAP* for the specified frame from the associated bitmap file.
	
	@param frameNum The index for the frame to be copied.
	@param width The desired width of the returned BITMAP. 
	@param height The desired height of the returned BITMAP. 
	@return A BITMAP* that is the desired from of size width x height.
******************************************************/
BITMAP* ImageFile::GetFrame(int frameNum, int width, int height)
{
	if(img == NULL) 
	{
		return img;	
	}
	BITMAP *retImg;
	retImg = create_bitmap(frameWidth, frameHeight);
	int s_x, s_y;
	s_x = (frameNum % numCols) * frameWidth;
	s_y = (frameNum / numCols) * frameHeight;	
	stretch_blit(img, retImg, s_x, s_y, frameWidth, frameHeight, 0, 0, width, height);
	return retImg;
}

/******************************************************
	Gets the number of frames for the associated file.
	
	@return The number of frames in the associated bitmap file.
******************************************************/
int ImageFile::GetNumFrames()
{ 
	return numFrames; 
}

/******************************************************
	Gets the number of columns of animation frames for the associated file.
	
	@return The number of columns of animation frames in the associated bitmap file.
******************************************************/
int ImageFile::GetNumCols()
{ 
	return numCols; 
}

/******************************************************
	Gets the width of one frame of animation in the associated file.
	
	@return The width of one frame of animation in the associated file.
******************************************************/
int ImageFile::GetWidth()
{ 
	return frameWidth; 
}

/******************************************************
	Gets the height of one frame of animation in the associated file.
	
	@return The height of one frame of animation in the associated file.
******************************************************/
int ImageFile::GetHeight()
{ 
	return frameHeight; 
}

/******************************************************
	Gets whether or not the associated bitmap file has been loaded.
	
	@return <code>true</code> if the file has been loaded successfully, <code>false</code> otherwise.
******************************************************/
bool ImageFile::isValid()
{
	if(img == NULL) return false;
	return true;
}