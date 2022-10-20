#include "yaPlayer.h"

namespace ya
{

	Player::Player()
		: mSpeed(1.0f)
	{
		SetPos(Vector2{ 100.f, 100.f });
		SetScale(Vector2{ 100.f, 100.f });
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		Vector2 pos = GetPos();
		if (GetAsyncKeyState('W') & 0x8000)
		{
			pos.y -= 0.01;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			pos.y += 0.01;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			pos.x -= 0.01;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			pos.x += 0.01;
		}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Rectangle(hdc
			, pos.x
			, pos.y
			, pos.x + scale.x
			, pos.y + scale.y);

	}

}