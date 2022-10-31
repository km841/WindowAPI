#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaApplication.h"
namespace ya
{
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale({100.f, 100.f})
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;
	}
	void Collider::Render(HDC hdc)
	{
		HPEN greenPen = Application::GetInstance().GetPen(ePenColor::Green);
		Pen pen(hdc, greenPen);
		
		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		Rectangle(hdc, mPos.x - mScale.x / 2.f, mPos.y- mScale.y / 2.f
			, mPos.x + mScale.x / 2, mPos.y + mScale.y / 2);
	}
}