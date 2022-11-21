#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "CameraMgr.h"

UINT Collider::gID = 0;

Collider::Collider()
	:mID(gID++)
{
	//SetSize(Vec2(30.f, 30.f));
}

Collider::~Collider()
{
}

void Collider::Update()
{
	GameObject* owner = GetOwner();
	Vec2 ownerPos = owner->GetPos();
	Vec2 pos = ownerPos + GetOffset();
	
	SetPos(pos);
}

void Collider::Render()
{
	// Owner�� Ÿ���� ���� �׸��� ������ �����Ѵ�

	Vec2 size = GetSize();
	Vec2 pos = GetPos();

	// Convert Render Pos
	pos = RENDER_POS(pos);
	HPEN pen = 0;

	OBJECT_TYPE objectType = GetOwner()->GetType();

	if (mColCnt > 0)
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	else
	{
		

		switch (objectType)
		{
		case OBJECT_TYPE::WALL:
			pen = CreatePen(PS_SOLID, 2, RGB(128, 128, 255));
			break;

		case OBJECT_TYPE::FOOTHOLD:
			pen = CreatePen(PS_SOLID, 2, RGB(128, 0, 64));
			break;

		default:
			pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			break;
		}

		
	}

	HPEN oldPen = (HPEN)SelectObject(BACK_BUF_DC, pen);

	Brush brush(BACK_BUF_DC, BRUSH_TYPE::HOLLOW);

	if (OBJECT_TYPE::WALL == objectType ||
		OBJECT_TYPE::FOOTHOLD == objectType)
	{
		Rectangle(BACK_BUF_DC
			, (int)pos.x
			, (int)pos.y
			, (int)(pos.x + size.x)
			, (int)(pos.y + size.y));
	}

	else
	{
		Rectangle(BACK_BUF_DC
			, (int)(pos.x - (size.x / 2))
			, (int)(pos.y - (size.y / 2))
			, (int)(pos.x + (size.x / 2))
			, (int)(pos.y + (size.y / 2)));
	}
	

	SelectObject(BACK_BUF_DC, oldPen);
	DeleteObject(pen);
}

void Collider::OnCollision(Collider* _other)
{
	mOwner->OnCollision(_other);
}

void Collider::OnCollisionEnter(Collider* _other)
{
	mOwner->OnCollisionEnter(_other);
	mColCnt++;
}

void Collider::OnCollisionExit(Collider* _other)
{
	mOwner->OnCollisionExit(_other);
	mColCnt--;
}
