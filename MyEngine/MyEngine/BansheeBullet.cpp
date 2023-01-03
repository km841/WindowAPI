#include "pch.h"
#include "BansheeBullet.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CollisionMgr.h"

BansheeBullet::BansheeBullet()
{
	mInfo.mMinAtt = 5.f;
	mInfo.mMaxAtt = 7.f;
	mInfo.mSpeed = 300.f;

	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	Texture* bansheeBulletTex = LOAD_TEXTURE(L"BansheeBullet", L"Texture\\BansheeBulletAnim.bmp");

	GetAnimator()->RegisterAnimation(
		L"BansheeBullet",
		bansheeBulletTex,
		Vec2(0.f, 0.f),
		Vec2(39.f, 48.f),
		Vec2(39.f, 0.f),
		0.05f,
		4
	);

	GetAnimator()->RegisterAnimation(
		L"BansheeBulletHit",
		bansheeBulletTex,
		Vec2(0.f, 48.f),
		Vec2(60.f, 81.f),
		Vec2(60.f, 0.f),
		0.05f,
		6
	);

	GetAnimator()->SelectAnimation(L"BansheeBullet", true);
}

BansheeBullet::~BansheeBullet()
{
}

void BansheeBullet::Initialize()
{
	MonsterBullet::Initialize();
}

void BansheeBullet::Update()
{
	MonsterBullet::Update();
}

void BansheeBullet::Render()
{
	MonsterBullet::Render();
}

void BansheeBullet::Dead()
{
	SetObjState(OBJECT_STATE::DEAD_ANIM);
	GetAnimator()->SelectAnimation(L"BansheeBulletHit", false);
}

void BansheeBullet::OnCollision(Collider* _other)
{
}

void BansheeBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"BansheeBulletHit", false);

		auto& rels = GetRelations();
		for (auto& rel : rels)
		{
			if (RELATION_TYPE::COLLISION == rel.mRelType)
				CollisionMgr::GetInstance().CollisionForceQuit(GetCollider(), rel.mOther->GetCollider());
		}

	}
}

void BansheeBullet::OnCollisionExit(Collider* _other)
{
}
