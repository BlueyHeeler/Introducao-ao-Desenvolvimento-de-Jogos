#ifndef VEC2_H
#define VEC2_H
class Vec2
{
public:
	Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
	Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
	float x, y;
};
#endif
