#pragma once
#define PI 3.1415926535f







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

	bool operator< (const Vec2& _other) const
	{
		if (x < _other.x &&
			y < _other.y)
			return true;

		return false;
	}

	bool operator>=(const Vec2& _other)
	{
		if (x >= _other.x &&
			y >= _other.y)
			return true;

		return false;
	}

	bool operator<=(const Vec2& _other)
	{
		if (x <= _other.x &&
			y <= _other.y)
			return true;

		return false;
	}

	bool operator==(const Vec2& _other) const
	{
		return (x == _other.x) && (y == _other.y);
	}

	bool operator==(const Vec2& _other)
	{
		return (x == _other.x) && (y == _other.y);
	}

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

	Vec2& operator+= (float _f)
	{
		x += _f;
		y += _f;
		return *this;
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

	Vec2& operator*= (float _f)
	{
		x *= _f;
		y *= _f;

		return *this;
	}

	Vec2 operator/ (const Vec2& _other)
	{
		Vec2 ret = { x, y };
		assert(_other.x != 0 || _other.y != 0);

		ret.x /= _other.x;
		ret.y /= _other.y;

		return ret;
	}

	Vec2 operator/ (float _f)
	{
		assert(_f != 0);
		Vec2 ret = { x, y };
		ret.x /= _f;
		ret.y /= _f;

		return ret;
	}

	Vec2 operator/ (float _f) const
	{
		assert(_f != 0);
		Vec2 ret = { x, y };
		ret.x /= _f;
		ret.y /= _f;

		return ret;
	}

	operator POINT()
	{
		return POINT{ static_cast<LONG>(x), static_cast<LONG>(y) };
	}

	operator POINT() const
	{
		return POINT{ static_cast<LONG>(x), static_cast<LONG>(y) };
	}

	void Norm()
	{
		float length = Len();
		x /= length;
		y /= length;
	}

	float Len()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dot(const Vec2& _other)
	{
		return (x * _other.x) + (y * _other.y);
	}


};

static float DegreeToRadian(float _degree)
{
	return (_degree * PI) / 180.f;
}

static float RadianToDegree(float _radian)
{
	return (_radian * 180.f) / PI;
}

static Vec2 RotateVector(Vec2 _v, float _radian)
{
	float x = _v.x * cos(_radian) - _v.y * sin(_radian);
	float y = _v.x * sin(_radian) + _v.y * cos(_radian);

	return Vec2(x, y);
}