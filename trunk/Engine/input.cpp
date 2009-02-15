#include "input.h"

Mouse::Mouse()
{
	x = mouse_x;
	y = mouse_y;
	pointer.SetSize(2,2);
	pointer.SetPosition(x-1, y-1);
}

void Mouse::Update(int &x_, int &y_)
{
	x = mouse_x;
	y = mouse_y;
	pointer.SetPosition(x-1, y-1);
	x_ = x - 200;
	y_ = y;
}

bool Mouse::StateChange(int &button, int &state, int &x_, int &y_)
{
	button = 0;
	state = 0;
	bool change;
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

	if(x >= 200 && x <= 800 && y >= 0 && y <= 600)
		return change;
	return false; // Do not return state changes if outside of game area
}

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


BoundingBox Mouse::GetPointer()
{
	return pointer;
}


Keyboard::Keyboard()
{
	for(int i = 0; i < KEY_MAX; i++)
		pressed[i] = false;
}

bool Keyboard::StateChange(int &key_, int &state_)
{
	bool change;
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
	pressed[key_] ^= true;
	return change;
}