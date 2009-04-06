#include "sprite.h"

/******************************************************
	Default Constructor
******************************************************/
Sprite::Sprite()
{
	box.SetPosition(0, 0);
	box.SetSize(0, 0);
	numFrames = 1;
	currFrame = 0;
	visible = true;
	moving = false;
	animating = false;
	alive = true;
	rest = 0;
}

/******************************************************
	Constructor

	@param spriteName The name of the sprite.
	@param x The initial x coordinate of the sprite
	@param y The initial y coordinate of the sprite
	@param w The initial width of the sprite in pixels
	@param h The initial height of the sprite in pixels
******************************************************/
Sprite::Sprite(std::string imageRef, int x = 0, int y = 0, int w = 0, int h = 0)
{
	fileRefName = imageRef;
	numFrames = 1;
	currFrame = 0;
	box.SetPosition(x, y);
	box.SetSize(w, h);
	visible = true;
	moving = false;
	animating = false;
	alive = true;
	rest = 0;
}

/******************************************************
	Deconstructor
******************************************************/
Sprite::~Sprite()
{
}

/******************************************************
	Toggles animation of the sprite
	and sets the frame rate

	@param delay The number of ticks to wait before moving to
				  the next frame. Higher numbers yield slower
				  animations. 0 or less will turn animation off.
******************************************************/
void Sprite::SetAnimation(int delay = 0)
{
	if(delay > 0)
	{
		frameDelay = delay;
		animating = true;
	}
}

/******************************************************
	Sets the rate at which to animate the sprite

	@param delay The number of ticks to wait before moving to
				  the next frame. Higher numbers yield slower
				  animations. 0 will turn animation off.
******************************************************/
void Sprite::SetFrameDelay(int delay)
{
	frameDelay = delay;
}

/******************************************************
	Toggles whether or not the sprite is alive.

	@param val <code>true</code> to have the sprite drawn,
				 <code>false</code> to have it not drawn
******************************************************/
void Sprite::SetAlive(bool val)
{
	alive = val;
}

/******************************************************
	@return <code>true</code> if the sprite is being animated,
	          <code>false</code> otherwise
******************************************************/
bool Sprite::isAnimating(){ return animating; }

/******************************************************
	@return <code>true</code> if the sprite is being drawn,
			  <code>false</code> otherwise
******************************************************/
bool Sprite::isAlive(){ return alive; }

/******************************************************
	Sets the current animation frame to draw.

	@param frame The index of the frame to draw
	@return <code>true</code> if the frame index is valid, 
			<code>false</code> otherwise.
******************************************************/
void Sprite::SetFrame(int frame)
{
	currFrame = frame;
}

/******************************************************
	Sets the position of the sprite on the screen.

	@param x The x coordinate of the position
	@param y The y coordinate of the position
******************************************************/
void Sprite::SetPosition(int x , int y)
{
	box.SetPosition(x, y);
}

/******************************************************
	Sets the width and height of the sprite.

	@param w The width of the sprite
	@param h The height of the sprite
******************************************************/
void Sprite::SetSize(int w, int h)
{
	box.SetSize(w, h);
}


/******************************************************
	Sets a sprite in motion until it reaches its destination.

	@param x The x coordinate being moved to
	@param y The y coordinate being moved to
	@param speed The number of pixels to move per tick (0 to stop movement)
******************************************************/
void Sprite::MoveTo(int x, int y, int s)
{
	new_x = x;
	new_y = y;
	speed = s;
	moving = true;
	if(speed < 0)
		speed = 0 - speed;
	if(speed == 0)
		moving = false;
}

/******************************************************
	Updates the sprite's location and animation.

	@param img The sprite image being drawn
	@param dest The screen bitmap on which to draw the sprite
******************************************************/
void Sprite::Update()
{
	if(alive)
	{
		NextFrame();
		MovePosition();
	}
}

/******************************************************
	Moves to the next frame of animation. If looping is
	enabled, the animation is restarted once the last frame
	has been rendered, otherwise animating is stopped.
******************************************************/
void Sprite::NextFrame()
{
	if(animating)
	{
		currFrame++;
		if(currFrame >= numFrames)
		{
			if(loops)
				currFrame = 0; // Start frames over
			else
			{
				currFrame--; // Reset to last valid frame
				animating = false;
			}
		}
	}
}

/******************************************************
	Draws the sprite in its current location.

	@param image The sprite image being drawn
	@param dest The screen bitmap on which to draw the sprite
******************************************************/
void Sprite::Draw(BITMAP *frame, BITMAP *buffer)
{
	if(visible)
	masked_blit(frame, buffer, 0, 0, box.GetPositionX(), box.GetPositionY(),
		box.GetWidth(), box.GetHeight());
}

/******************************************************
	Uses values specified in MoveTo() to change the position
	of the sprite.
******************************************************/
void Sprite::MovePosition()
{
	if(moving && rest == 0)
	{
		rest = speed;
		if(new_x > box.GetPositionX())
		{
			box.SetPosition(box.GetPositionX()+speed, box.GetPositionY());
			if(new_x <= box.GetPositionX()) box.SetPosition(new_x, box.GetPositionY()); // Prevents wobbling
		}
		if(new_x < box.GetPositionX())
		{
			box.SetPosition(box.GetPositionX()-speed, box.GetPositionY());
			if(new_x >= box.GetPositionX()) box.SetPosition(new_x, box.GetPositionY()); // Prevents wobbling
		}
		
		if(new_y > box.GetPositionY())
		{
			box.SetPosition(box.GetPositionX(), box.GetPositionY()+speed);
			if(new_y <= box.GetPositionY()) box.SetPosition(box.GetPositionX(), new_y); // Prevents wobbling
		}
		if(new_y < box.GetPositionY())
		{
			box.SetPosition(box.GetPositionX(), box.GetPositionY()-speed);
			if(new_y >= box.GetPositionY()) box.SetPosition(box.GetPositionX(), new_y); // Prevents wobbling
		}
		
		if(new_y == box.GetPositionY() && new_x == box.GetPositionX())
		{
			moving = false;
			speed = 0;
		}
	}
	if(moving && rest > 0)
	{
		rest--;
	}
}

int Sprite::GetFrameNum()
{
	return currFrame;
}

void Sprite::SetFrameCount(int fCount)
{
	numFrames = fCount;
}

int Sprite::GetWidth()
{
	return box.GetWidth();
}

int Sprite::GetHeight()
{
	return box.GetHeight();
}

void Sprite::SetVisible(bool in)
{
	visible = in;
}

bool Sprite::isVisible()
{
	return visible;
}


bool Sprite::isColliding(BoundingBox &other_box)
{
	return box.isColliding(other_box);
}

bool Sprite::isColliding(Sprite &other_sprite)
{
	return box.isColliding(other_sprite.box);
}


void Sprite::ChangeBitmap(std::string ref)
{
	fileRefName = ref;
}