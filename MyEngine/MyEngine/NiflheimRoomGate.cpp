#include "pch.h"
#include "NiflheimRoomGate.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"


NiflheimRoomGate::NiflheimRoomGate()
{
	mToolID = TOOL_ID::BTN_NIFLHEIM_DOOR;
	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"NiflheimDoorTex", L"Texture\\NiflheimDoorAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"NiflheimDoorAnim",
		tex,
		Vec2(0, 0),
		Vec2(171, 195),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->SelectAnimation(L"NiflheimDoorAnim", false);
}

NiflheimRoomGate::~NiflheimRoomGate()
{
}

void NiflheimRoomGate::Initialize()
{
	BossRoomGate::Initialize();
}

void NiflheimRoomGate::Update()
{
	BossRoomGate::Update();
}

void NiflheimRoomGate::Render()
{
	BossRoomGate::Render();
}

void NiflheimRoomGate::Destroy()
{
	BossRoomGate::Destroy();
}

void NiflheimRoomGate::OnCollision(Collider* _other)
{
	BossRoomGate::OnCollision(_other);
}

void NiflheimRoomGate::OnCollisionEnter(Collider* _other)
{
}

void NiflheimRoomGate::OnCollisionExit(Collider* _other)
{
	BossRoomGate::OnCollisionExit(_other);
}