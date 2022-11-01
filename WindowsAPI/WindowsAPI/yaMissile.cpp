#include "yaMissile.h"
#include "yaTime.h"
#include "yaCollider.h"

namespace ya
{



	Missile::Missile()
	{
		SetPos({ 100.f, 100.f });
		SetScale({ 50.f, 50.f });

		AddComponent(new Collider());
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		
		Vector2 pos = GetPos();

		pos.y -= 600.0f * Time::DeltaTime();
		SetPos(pos);

		GameObject::Tick();
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

		GameObject::Render(hdc);
	}

}