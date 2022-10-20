#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2(int x, int y)
		: x(x)
		, y(y)
	{ }
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{ }

	Vector2(const Vector2& other) = default;
	//Vector2(Vector2&& other) = default;
	Vector2() = default;
	~Vector2() = default;
};
