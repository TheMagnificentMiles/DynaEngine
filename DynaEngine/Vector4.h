#pragma once
#include <math.h>

class Vector4
{
public:
	float x, y, z, w;

	Vector4() :x(0), y(0), z(0), w(0)
	{
	}
	Vector4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w)
	{
	}
	Vector4(float i) :x(i), y(i), z(i), w(i)
	{
	}
	Vector4(const Vector4& vector) :x(vector.x), y(vector.y), z(vector.z), w(vector.w)
	{
	}

	void cross(Vector4& v1, Vector4& v2, Vector4& v3)
	{
		this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
		this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	static Vector4 lerp(const Vector4& start, const Vector4& end, float delta)
	{
		Vector4 v;
		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;
		v.w = start.w * (1.0f - delta) + end.w * delta;


		return v;
	}

	~Vector4()
	{
	}
};

