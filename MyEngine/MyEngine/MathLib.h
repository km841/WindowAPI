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

	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

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

	bool operator!=(const Vec2& _other)
	{
		return (x != _other.x) && (y != _other.y);
	}

	bool operator!=(const Vec2& _other) const
	{
		return (x != _other.x) && (y != _other.y);
	}

	Vec2 operator-()
	{
		return Vec2(-x, -y);
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

	Vec2 operator+ (float _f)
	{
		Vec2 ret = { x, y };
		ret.x += _f;
		ret.y += _f;

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

	Vec2 operator- (const Vec2& _other) const
	{
		Vec2 ret = { x, y };
		ret.x -= _other.x;
		ret.y -= _other.y;

		return ret;
	}

	Vec2& operator-= (const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
		return *this;
	}

	Vec2& operator-= (float _f)
	{
		x -= _f;
		y -= _f;
		return *this;
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

struct Math
{
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

	static float Lerp(float _f1, float _f2, float _t) {
		return (1 - _t) * _f1 + _t * _f2;
	}

	static Vec2 Lerp(Vec2 _v1, Vec2 _v2, float _t) {
		Vec2 temp = {};
		temp.x = Lerp(_v1.x, _v2.x, _t);
		temp.y = Lerp(_v1.y, _v2.y, _t);
		return temp;
	}

	static Vec2 ZeroVector()
	{
		return Vec2(0.f, 0.f);
	}

	static float LineToDotDistance(Vec2 _v1_start, Vec2 _v1_end, Vec2 _v)
	{
		// 직선의 방정식 구하기
		// 기울기
		float slope = (_v1_end.y - _v1_start.y) / (_v1_end.x - _v1_start.x);
		
		// y절편
		float r = _v1_start.y - (slope * _v1_start.x);
		
		return abs(slope * _v.x - _v.y + r) / sqrt(slope * slope + 1);
	}

};