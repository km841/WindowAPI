#include "pch.h"
#include "BelialCoreBullet.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "CollisionMgr.h"
#include "Sound.h"


BelialCoreBullet::BelialCoreBullet()
{
	SetBulletWayType(BULLET_WAY_TYPE::LINEAR);

	mInfo.mMinAtt = 5.f;
	mInfo.mMaxAtt = 7.f;
	mInfo.mSpeed = 400.f;

	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));

	Texture* tex = LOAD_TEXTURE(L"BelialCoreBulletTex", L"Texture\\BelialBulletAnim.bmp");

	GetAnimator()->RegisterAnimation(
		L"BelialCoreBulletAnim",
		tex,
		Vec2(0, 0),
		Vec2(39, 39),
		Vec2(39, 0),
		0.05f,
		2
	);

	GetAnimator()->RegisterAnimation(
		L"BelialCoreBulletHitAnim",
		tex,
		Vec2(0, 39),
		Vec2(96, 96),
		Vec2(96, 0),
		0.02f,
		5);

	GetAnimator()->SelectAnimation(L"BelialCoreBulletAnim", true);
}

BelialCoreBullet::~BelialCoreBullet()
{
}

void BelialCoreBullet::Initialize()
{
	MonsterBullet::Initialize();
}

void BelialCoreBullet::Update()
{
	MonsterBullet::Update();
}

void BelialCoreBullet::Render()
{
	MonsterBullet::Render();
}

void BelialCoreBullet::Dead()
{
	SetObjState(OBJECT_STATE::DEAD_ANIM);
	GetAnimator()->SelectAnimation(L"BelialCoreBulletHitAnim", false);
}

void BelialCoreBullet::OnCollision(Collider* _other)
{
}

void BelialCoreBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::DUNGEON_OBJECT == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"BelialCoreBulletHitAnim", false);

		auto& rels = GetRelations();
		for (auto& rel : rels)
		{
			if (RELATION_TYPE::COLLISION == rel.mRelType)
				CollisionMgr::GetInstance().CollisionForceQuit(GetCollider(), rel.mOther->GetCollider());
		}

		if (nullptr != GetHitSound())
		{
			GetHitSound()->Play(false);
		}
	}
}

void BelialCoreBullet::OnCollisionExit(Collider* _other)
{
}
