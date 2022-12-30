#include "pch.h"
#include "IceBullet.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "CollisionMgr.h"

IceBullet::IceBullet()
	:mInitFlag(true)
{
	mInfo.mAtt = 5.f;
	mInfo.mSpeed = 300.f;

	GetCollider()->SetSize(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));

	Texture* iceBulletTex = ResourceMgr::GetInstance().Load<Texture>(L"IceBulletTex", L"Texture\\IceBullet.bmp");
	Texture* iceBulletHitTex = ResourceMgr::GetInstance().Load<Texture>(L"IceBulletHitTex", L"Texture\\IceBulletHit.bmp");

	GetAnimator()->RegisterAnimation(
		L"IceBulletAnim",
		iceBulletTex,
		Vec2(0.f, 0.f),
		Vec2(54.f, 54.f),
		Vec2(54.f, 0.f),
		0.05f,
		1
	);

	GetAnimator()->RegisterAnimation(
		L"IceBulletHitAnim",
		iceBulletHitTex,
		Vec2(0.f, 0.f),
		Vec2(75.f, 75.f),
		Vec2(75.f, 0.f),
		0.05f,
		3
	);
}

IceBullet::~IceBullet()
{
}

void IceBullet::Initialize()
{
	MonsterBullet::Initialize();
	GetAnimator()->RotSelectAnimation(L"IceBulletAnim", GetAngle(), true);
	GetAnimator()->GetCurAnimation()->SetEffectAnimation(false);
}

void IceBullet::Update()
{
	MonsterBullet::Update();
}

void IceBullet::Render()
{
	MonsterBullet::Render();
}

void IceBullet::Dead()
{
	SetObjState(OBJECT_STATE::DEAD_ANIM);
	GetAnimator()->SelectAnimation(L"IceBulletHitAnim", false);
}

void IceBullet::OnCollision(Collider* _other)
{
}

void IceBullet::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::WALL == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::DUNGEON_OBJECT == _other->GetOwner()->GetType() ||
		OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		// 애니메이션 변경후 애니메이션이 끝나면 소멸
		SetObjState(OBJECT_STATE::DEAD_ANIM);
		GetAnimator()->SelectAnimation(L"IceBulletHitAnim", false);
		

		auto& rels = GetRelations();
		for (auto& rel : rels)
		{
			if (RELATION_TYPE::COLLISION == rel.mRelType)
				CollisionMgr::GetInstance().CollisionForceQuit(GetCollider(), rel.mOther->GetCollider());
		}
	}
}

void IceBullet::OnCollisionExit(Collider* _other)
{
}
