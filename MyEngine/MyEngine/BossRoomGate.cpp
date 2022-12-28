#include "pch.h"
#include "BossRoomGate.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "Animation.h"

BossRoomGate::BossRoomGate()
{
	SetType(OBJECT_TYPE::DUNGEON_DOOR);
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30, 30));
	GetCollider()->SetOffset(Vec2(0, -15));

	mKeyTex = ResourceMgr::GetInstance().Load<Texture>(L"F_KEY", L"Texture\\F.bmp");
}

BossRoomGate::~BossRoomGate()
{
}

void BossRoomGate::Initialize()
{
	GameObject::Initialize();
}

void BossRoomGate::Update()
{
	GameObject::Update();

	Animation* anim = GetAnimator()->GetCurAnimation();
	if (nullptr != anim)
	{
		int frame = anim->GetCurFrame();

		if (9 == frame)
		{
			anim->SetFrameFix(true);
		}
	}
}

void BossRoomGate::Render()
{
	GameObject::Render();

	if (nullptr != mKeyTex &&
		true == mCollision)
	{
		Vec2 fKeyPos = GetPos();
		fKeyPos.y -= 110.f;

		fKeyPos = RENDER_POS(fKeyPos);
		Vec2 textureSize = mKeyTex->GetSize();

		TransparentBlt(
			BACK_BUF_DC,
			(int)(fKeyPos.x - ((textureSize.x * TIMES) / 2.f)),
			(int)(fKeyPos.y - ((textureSize.y * TIMES) / 2.f)),
			(int)(textureSize.x * TIMES),
			(int)(textureSize.y * TIMES),
			mKeyTex->GetDC(),
			0, 0,
			(int)textureSize.x,
			(int)textureSize.y,
			RGB(255, 0, 255)
		);
	}


}

void BossRoomGate::Destroy()
{
	GameObject::Destroy();
}

void BossRoomGate::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = true;
	}
	
}

void BossRoomGate::OnCollisionEnter(Collider* _other)
{
}

void BossRoomGate::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = false;
	}
}
