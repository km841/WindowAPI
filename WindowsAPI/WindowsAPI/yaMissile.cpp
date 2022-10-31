#include "yaMissile.h"
#include "yaTime.h"

namespace ya
{



	Missile::Missile()
	{
		SetPos({ 100.f, 100.f });
		SetScale({ 50.f, 50.f });
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		Vector2 pos = GetPos();

		pos.y -= 600.0f * Time::DeltaTime();
		SetPos(pos);
	}

	void Missile::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Ellipse(hdc
			, pos.x
			, pos.y
			, pos.x + scale.x
			, pos.y + scale.y);
	}

}