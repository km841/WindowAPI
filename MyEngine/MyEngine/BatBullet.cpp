#include "pch.h"
#include "BatBullet.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"

BatBullet::BatBullet()
{
	mInfo.mAtt = 5.f;
	mInfo.mSpeed = 300.f;

	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	Texture* batBulletTex = LOAD_TEXTURE(L"BatBulletIdleAnim", L"Texture\\RangeBallBullet.bmp");

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
	MonsterBullet::Initialize();
}

void BatBullet::Update()
{
	MonsterBullet::Update();
}

void BatBullet::Render()
{
	MonsterBullet::Render();
}

void BatBullet::Dead()
{
	SetObjState(OBJECT_STATE::DEAD_ANIM);
	GetAnimator()->SelectAnimation(L"BatBulletHit", false);
}

void BatBullet::OnCollision(Collider* _other)
{
}

void BatBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::DUNGEON_OBJECT == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"BatBulletHit", false);

		auto& rels = GetRelations();
		for (auto& rel : rels)
		{
			if (RELATION_TYPE::COLLISION == rel.mRelType)	
				CollisionMgr::GetInstance().CollisionForceQuit(GetCollider(), rel.mOther->GetCollider());
		}

	}
}

void BatBullet::OnCollisionExit(Collider* _other)
{
}
