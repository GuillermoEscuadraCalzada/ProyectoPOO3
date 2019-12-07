#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>
struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) :x(_x), y(_y) {};
	Vector2& operator +=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	};
	Vector2& operator -=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	};
};


inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}
inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

#endif // !VECTOR2_H
