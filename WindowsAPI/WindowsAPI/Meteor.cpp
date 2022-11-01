#include "Meteor.h"
#include "yaTime.h"
namespace ya
{


	Meteor::Meteor()
		:mSpeed(100.0f)
	{
		SetScale({ 25, 25 });
	}

	Meteor::~Meteor()
	{

	}

	void Meteor::Tick()
	{
		Vector2 pos = GetPos();
		pos.y += mSpeed * Time::DeltaTime();
		SetPos(pos);
	}

	void Meteor::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));

		Pen pen(hdc, hPen);
		Brush brush(hdc, hBrush);

		Ellipse(hdc
			, pos.x
			, pos.y
			, pos.x + scale.x
			, pos.y + scale.y);
	}

}