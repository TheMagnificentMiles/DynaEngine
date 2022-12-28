#pragma once

class Vector3
{
public:
	float x, y, z;

	Vector3():x(0),y(0),z(0)
	{
	}
	Vector3(float x, float y, float z):x(x),y(y),z(z)
	{
	}
	Vector3(const Vector3& vector) :x(vector.x), y(vector.y), z(vector.z)
	{
	}

	static Vector3 lerp(const Vector3& start, const Vector3& end, float delta) 
	{
		Vector3 v;
		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;


		return v;
	}

	~Vector3() 
	{
	}
};

