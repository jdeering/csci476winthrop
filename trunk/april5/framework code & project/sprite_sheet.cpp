#include "sprite_sheet.h"

SpriteSheet::SpriteSheet()
{
	sheet = NULL;
}


BITMAP* SpriteSheet::GetFrame(int frame)
{
	if(sheet == NULL) return sheet;
	BITMAP *retImg;
	int s_x, s_y;
	s_x = (frame % frameCols) * frameWidth;
	s_y = (frame / frameCols) * frameHeight;	
	blit(sheet, retImg, s_x, s_y, 0, 0,	frameWidth, frameHeight);
	return retImg;
}