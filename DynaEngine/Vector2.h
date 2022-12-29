#pragma once
#include <math.h>

class Vector2
{
public:
	float x, y;

	Vector2() :x(0), y(0)
	{
	}
	Vector2(float x, float y) :x(x), y(y)
	{
	}
	Vector2(float i) :x(i), y(i)
	{
	}
	Vector2(const Vector2& vector) :x(vector.x), y(vector.y)
	{
	}

	float sqrMagnitude()
	{
		return x * x + y * y;
	}

	float magnitude()
	{
		return sqrt(x * x + y * y);
	}

	static Vector2 lerp(const Vector2& start, const Vector2& end, float delta)
	{
		Vector2 v;
		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;

		return v;
	}

	~Vector2()
	{
	}
};

