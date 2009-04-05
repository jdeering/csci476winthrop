#include "input.h"

/******************************************************
	Default Constructor
******************************************************/
Mouse::Mouse()
{
	x = mouse_x;
	y = mouse_y;
	pointer.SetSize(2,2);
	pointer.SetPosition(x-1, y-1);
	leftPressed = false;
	rightPressed = false;
}

/******************************************************
	Updates the x,y position of the mouse pointer from Allegro.
	
	@param x_ Pass-by-reference value in which to return the new x coordinate.
	@param y_ Pass-by-reference value in which to return the new y coordinate.
******************************************************/
void Mouse::Update(int &x_, int &y_)
{
	x = mouse_x;
	y = mouse_y;
	pointer.SetPosition(x-1, y-1);
	x_ = x - XOFFSET;
	y_ = y;
}

/******************************************************
	Controls the passing of state changes for the mouse buttons.
	
	@param button The button the state change is being reported for.
	@param state The new state of the button. 1 for clicked, 0 for not clicked.
	@param x_ The x coordinate of the mouse pointer.
	@param y_ The y coordinate of the mouse pointer. 
	@return <code>true</code> if a state has changed, <code>false</code> otherwise.
******************************************************/
bool Mouse::StateChange(int &button, int &state, int &x_, int &y_)
{
	button = 0;
	state = 0;
	bool change = false;
	Update(x_, y_);
	int lb = (mouse_b & 1);
	int rb = (mouse_b & 2);

	if(leftPressed)
	{
		if(!lb)
		{
			change = true;
			button = 1;
			state = 0;
			leftPressed ^= true;
		}
	}
	else
	{
		if(lb)
		{
			change = true;
			button = 1;
			state = 1;
			leftPressed ^= true;
		}
	}

	if(rightPressed)
	{
		if(!rb)
		{
			change = true;
			button = 2;
			state = 0;
			rightPressed ^= true;
		}
	}
	else
	{
		if(rb)
		{
			change = true;
			button = 2;
			state = 1;
			rightPressed ^= true;
		}
	}

	return change;
}

/******************************************************
	Checks to see if the specified <code>BoundingBox</code> has been clicked
	by the left mouse button.
	 
	@return <code>true</code> if a the left button is clicked on the <code>BoundingBox</code>, <code>false</code> otherwise.
******************************************************/
bool Mouse::LeftClick(BoundingBox &box)
{
	int button, state, x, y;
	Update(x, y);
	
	if(pointer.isColliding(box))
	{
		if(StateChange(button, state, x, y))
		{
			if(button == 1 && state == 1)
				return true;
		}
	}
	return false;
}

/******************************************************
	Checks to see if the specified <code>BoundingBox</code> has been released over
	by the left mouse button.
	 
	@return <code>true</code> if a the left button is released on the <code>BoundingBox</code>, <code>false</code> otherwise.
******************************************************/
bool Mouse::LeftRelease(BoundingBox &box)
{
	int button, state, x, y;
	Update(x, y);
	
	if(pointer.isColliding(box))
	{
		if(StateChange(button, state, x, y))
		{
			if(button == 1 && state == 0)
				return true;
		}
	}
	return false;
}

/******************************************************
	Checks to see if the specified <code>BoundingBox</code> has been clicked
	by the right mouse button.
	 
	@return <code>true</code> if a the right button is clicked on the <code>BoundingBox</code>, <code>false</code> otherwise.
******************************************************/
bool Mouse::RightClick(BoundingBox &box)
{
	int button, state, x, y;
	Update(x, y);
	
	if(pointer.isColliding(box))
	{
		if(StateChange(button, state, x, y))
		{
			if(button == 2 && state == 1)
				return true;
		}
	}
	return false;
}

/******************************************************
	Checks to see if the specified <code>BoundingBox</code> has been released over
	by the right mouse button.
	 
	@return <code>true</code> if a the right button is released on the <code>BoundingBox</code>, <code>false</code> otherwise.
******************************************************/
bool Mouse::RightRelease(BoundingBox &box)
{
	int button, state, x, y;
	Update(x, y);
	
	if(pointer.isColliding(box))
	{
		if(StateChange(button, state, x, y))
		{
			if(button == 2 && state == 01)
				return true;
		}
	}
	return false;
}


/******************************************************
	Gets the <code>BoundingBox</code> for the mouse pointer.
	 
	@return The <code>BoundingBox</code> for the mouse pointer.
******************************************************/
BoundingBox Mouse::GetPointer()
{
	return pointer;
}

/******************************************************
	Default Constructor
******************************************************/
Keyboard::Keyboard()
{
	for(int i = 0; i < KEY_MAX; i++)
		pressed[i] = false;
}

/******************************************************
	Controls the passing of state changes for the keyboard keys.
	
	@param key_ The keyboard key the state change is being reported for.
	@param state_ The new state of the button. 1 for pressed, 0 for not pressed.
	@return <code>true</code> if a key's state has changed, <code>false</code> otherwise.
******************************************************/
bool Keyboard::StateChange(int &key_, int &state_)
{
	bool change = false;
	key_ = 0;
	state_ = 0;
	for(int i = 0; i < KEY_MAX && !change; i++)
	{
		if(pressed[i])
		{
			if(!key[i])
			{
				change = true;
				key_ = i;
				state_ = 0;
			}
		}
		else
		{
			if(key[i])
			{
				change = true;
				key_ = i;
				state_ = 1;
			}
		}
	}
	pressed[key_] ^= change;
	return change;
}