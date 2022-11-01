#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2() = default;

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{ }

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{ }

	Vec2(const Vec2& _other)
		: x(_other.x)
		, y(_other.y)
	{ }

	Vec2& operator= (const Vec2& _other)
	{
		x = _other.x;
		y = _other.y;
		return *this;
	}

	Vec2 operator+ (const Vec2 & _other)
	{
		Vec2 ret = {x, y};
		ret.x += _other.x;
		ret.y += _other.y;

		return ret;
	}

	Vec2& operator+= (const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}

	Vec2 operator- (const Vec2& _other)
	{
		Vec2 ret = { x, y };
		ret.x -= _other.x;
		ret.y -= _other.y;

		return ret;
	}

	Vec2 operator* (const Vec2& _other)
	{
		Vec2 ret = { x, y };
		ret.x *= _other.x;
		ret.y *= _other.y;

		return ret;
	}

	Vec2 operator* (float _f)
	{
		Vec2 ret = { x, y };
		ret.x *= _f;
		ret.y *= _f;

		return ret;
	}

	Vec2 operator/ (const Vec2& _other)
	{
		Vec2 ret = { x, y };
		assert(_other.x != 0 || _other.y != 0);

		ret.x /= _other.x;
		ret.y /= _other.y;

		return ret;
	}

	void Norm()
	{
		float length = sqrt( (x * x) + (y * y) );
		x /= length;
		y /= length;
	}
};