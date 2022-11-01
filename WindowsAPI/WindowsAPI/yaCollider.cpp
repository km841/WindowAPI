#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaApplication.h"
namespace ya
{
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale({ 100.f, 100.f })
		, mCollisionCount(0)
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
		HPEN redPen = Application::GetInstance().GetPen(ePenColor::Red);
		Pen redpen(hdc, redPen);
		Pen greenpen(hdc, greenPen);

		if (mCollisionCount > 0)
			redpen.SetPen(redPen);
		else
			greenpen.SetPen(greenPen);
		
		
		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);



		Rectangle(hdc, mPos.x - mScale.x / 2.f, mPos.y- mScale.y / 2.f
			, mPos.x + mScale.x / 2, mPos.y + mScale.y / 2);
	}
	void Collider::OnCollisionEnter(Collider* _other)
	{
		mCollisionCount++;
		GetOwner()->OnCollisionEnter(_other);
	}
	void Collider::OnCollisionStay(Collider* _other)
	{
		GetOwner()->OnCollisionStay(_other);
	}
	void Collider::OnCollisionExit(Collider* _other)
	{
		mCollisionCount--;
		GetOwner()->OnCollisionExit(_other);
	}
}