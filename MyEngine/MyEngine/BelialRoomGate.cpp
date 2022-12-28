#include "pch.h"
#include "BelialRoomGate.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"


BelialRoomGate::BelialRoomGate()
{
	mToolID = TOOL_ID::BTN_BELIAL_DOOR;
	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"BelialDoorTex", L"Texture\\BelialDoorAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"BelialDoorAnim",
		tex,
		Vec2(0, 0),
		Vec2(171, 195),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->SelectAnimation(L"BelialDoorAnim", false);
}

BelialRoomGate::~BelialRoomGate()
{
}

void BelialRoomGate::Initialize()
{
	BossRoomGate::Initialize();
}

void BelialRoomGate::Update()
{
	BossRoomGate::Update();
}

void BelialRoomGate::Render()
{
	BossRoomGate::Render();
}

void BelialRoomGate::Destroy()
{
	BossRoomGate::Destroy();
}

void BelialRoomGate::OnCollision(Collider* _other)
{
	BossRoomGate::OnCollision(_other);
}

void BelialRoomGate::OnCollisionEnter(Collider* _other)
{
}

void BelialRoomGate::OnCollisionExit(Collider* _other)
{
	BossRoomGate::OnCollisionExit(_other);
}
