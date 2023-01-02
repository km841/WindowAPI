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
	Texture* tex = LOAD_TEXTURE(L"NiflheimDoorTex", L"Texture\\DungeonObject\\NiflheimDoorAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"NiflheimDoorOpenAnim",
		tex,
		Vec2(0, 0),
		Vec2(171, 195),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"NiflheimDoorCloseAnim",
		tex,
		Vec2(0, 195),
		Vec2(171, 195),
		Vec2(171, 0),
		0.1f,
		10
	);

	GetAnimator()->SelectAnimation(L"NiflheimDoorOpenAnim", false);
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
	
	if (mState != mPrevState)
	{
		switch (mState)
		{
		case DOOR_STATE::OPEN:
			GetAnimator()->SelectAnimation(L"NiflheimDoorOpenAnim", false);
			break;

		case DOOR_STATE::CLOSE:
			GetAnimator()->SelectAnimation(L"NiflheimDoorCloseAnim", false);
			break;
		}
	}

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