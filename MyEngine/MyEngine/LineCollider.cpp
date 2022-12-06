#include "pch.h"
#include "LineCollider.h"
#include "GameObject.h"
#include "CameraMgr.h"

LineCollider::LineCollider()
	:mLineType(LINE_TYPE::FLAT)
{
	mColliderType = COLLISION_TYPE::LINE;
}

LineCollider::~LineCollider()
{
	
}

void LineCollider::Update()
{
	Collider::Update();
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	switch (mLineType)
	{
	case LINE_TYPE::FLAT:
		mLeftPos = Vec2(
			pos.x - size.x / 2.f,
			pos.y - size.y / 2.f);

		mRightPos = Vec2(
			pos.x + size.x / 2.f,
			pos.y - size.y / 2.f);

		break;

	case LINE_TYPE::DEGREE_45:
		mLeftPos = Vec2(
			pos.x - size.x / 2.f,
			pos.y + size.y / 2.f);

		mRightPos = Vec2(
			pos.x + size.x / 2.f,
			pos.y - size.y / 2.f);

		break;

	case LINE_TYPE::DEGREE_135:
		mLeftPos = Vec2(
			pos.x - size.x / 2.f,
			pos.y - size.y / 2.f);

		mRightPos = Vec2(
			pos.x + size.x / 2.f,
			pos.y + size.y / 2.f);

		break;
	}
}


void LineCollider::Render()
{
	Vec2 leftPos = RENDER_POS(mLeftPos);
	Vec2 rightPos = RENDER_POS(mRightPos);


	HPEN pen = 0;

	if (mColCnt > 0)
		pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	else
	{
		pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	}

	HPEN oldPen = (HPEN)SelectObject(BACK_BUF_DC, pen);

	MoveToEx(BACK_BUF_DC, (int)leftPos.x, (int)leftPos.y, NULL);
	LineTo(BACK_BUF_DC, (int)rightPos.x, (int)rightPos.y);

	SelectObject(BACK_BUF_DC, oldPen);
	DeleteObject(pen);
}

void LineCollider::OnCollision(Collider* _other)
{
	Collider::OnCollision(_other);
}

void LineCollider::OnCollisionEnter(Collider* _other)
{
	Collider::OnCollisionEnter(_other);
}

void LineCollider::OnCollisionExit(Collider* _other)
{
	Collider::OnCollisionExit(_other);
}
