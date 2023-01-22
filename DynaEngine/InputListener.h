#pragma once
#include "Vector2.h"

class InputListener
{
public:
	InputListener()
	{
	}
	~InputListener()
	{
	}

	virtual void onKeyDown(int key) = 0;
	virtual void whileKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;
	
	virtual void onMouseMove(const Vector2& mouse_pos) = 0;
	
	virtual void onLeftMouseDown(const Vector2& mouse_pos) = 0;
	virtual void whileLeftMouseDown(const Vector2& mouse_pos) = 0;
	virtual void onLeftMouseUp(const Vector2& mouse_pos) = 0;
	virtual void onRightMouseDown(const Vector2& mouse_pos) = 0;
	virtual void whileRightMouseDown(const Vector2& mouse_pos) = 0;
	virtual void onRightMouseUp(const Vector2& mouse_pos) = 0;
};