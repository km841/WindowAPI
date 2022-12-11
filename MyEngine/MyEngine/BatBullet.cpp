#include "pch.h"
#include "BatBullet.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"

BatBullet::BatBullet()
{

	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	Texture* batBulletTex = ResourceMgr::GetInstance().Load<Texture>(L"BatBulletIdleAnim", L"Texture\\RangeBallBullet.bmp");

	GetAnimator()->RegisterAnimation(
		L"BatBullet",
		batBulletTex,
		Vec2(0.f, 0.f),
		Vec2(42.f, 42.f),
		Vec2(42.f, 0.f),
		0.05f,
		5
	);

	GetAnimator()->RegisterAnimation(
		L"BatBulletHit",
		batBulletTex,
		Vec2(0.f, 42.f),
		Vec2(96.f, 96.f),
		Vec2(96.f, 0.f),
		0.05f,
		7
	);

	GetAnimator()->SelectAnimation(L"BatBullet", true);

}

BatBullet::~BatBullet()
{
}

void BatBullet::Initialize()
{
}

void BatBullet::Update()
{
	GameObject::Update();
	if (BULLET_STATE::DEAD_ANIM == GetBulletState())
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			SetBulletState(BULLET_STATE::DEAD);
		}
	}

	else
	{

		// 화면 밖으로 날아가면 false
		if (CameraMgr::GetInstance().OutOfScreen(GetPos()))
		{
			SetBulletState(BULLET_STATE::DEAD);
		}
	}
}

void BatBullet::Render()
{
	GameObject::Render();
}

void BatBullet::OnCollision(Collider* _other)
{
}

void BatBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetBulletState(BULLET_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"BatBulletHit", false);
	}
}

void BatBullet::OnCollisionExit(Collider* _other)
{
}
