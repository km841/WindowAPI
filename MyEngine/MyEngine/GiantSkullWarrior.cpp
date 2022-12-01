#include "pch.h"
#include "GiantSkullWarrior.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "MonsterSwordEffect.h"
#include "CollisionMgr.h"

GiantSkullWarrior::GiantSkullWarrior()
{
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"GiantSkull_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"GiantSkull_Move";
	SetMoveAnimName(moveAnimName);
	
	std::wstring attAnimName = L"GiantSkull_Att";
	SetAttAnimName(attAnimName);
	
	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"GiantSkullAnimTex", L"Texture\\giant_skull_animation.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 90.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 180.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 270.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 360.f),
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimLeft->SetOffset(Vec2(-50, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 504.f),
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimRight->SetOffset(Vec2(50, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->SelectAnimation(L"GiantSkull_IdleLeft", true);

	MonsterSwordEffect* effect = new MonsterSwordEffect;
	effect->SetOwner(this);
	effect->GetCollider()->SetOwner(effect);
	effect->GetCollider()->SetSize(Vec2(120, 100));
	effect->GetCollider()->SetOffset_Y(-50);
	effect->GetCollider()->SetEnable(false);
	SetEffect(effect);
}

GiantSkullWarrior::~GiantSkullWarrior()
{
}

void GiantSkullWarrior::Initialize()
{
	Monster::Initialize();
}

void GiantSkullWarrior::Update()
{
	Monster::Update();
	
	//Vec2 pos = GetPos();

	//wchar_t buf[COMMENT_MAX_SIZE] = {};
	//swprintf_s(buf, L"x: %f, y:%f", pos.x, pos.y);

	//pos.y -= 100;
	//Vec2 renderPos = RENDER_POS(pos);
	//TextOut(BACK_BUF_DC, 100, 500, buf, wcslen(buf));

}

void GiantSkullWarrior::Render()
{
	Monster::Render();
}

void GiantSkullWarrior::OnCollision(Collider* _other)
{
}

void GiantSkullWarrior::OnCollisionEnter(Collider* _other)
{
	// 데미지를 입을 때 빨간색이 되고, 
	// 데미지를 입어서 HP가 0이 되면 Dead상태에서 죽는 애니메이션을 실행
	// 애니메이션이 끝난 후 DeleteObject..
	// if (isDead() && GetCurAnim()->isFinished())
	//   -> 소멸
	if (OBJECT_TYPE::PLAYER_EFFECT == _other->GetOwner()->GetType())
	{
		// 무기에서 이펙트에 공격력을 전달?
		EventRegisteror::GetInstance().DeleteObject(this);
	}

}

void GiantSkullWarrior::OnCollisionExit(Collider* _other)
{
}

void GiantSkullWarrior::AttackEnter()
{
	// Effect의 콜라이더
	switch (mDir)
	{
	case DIR::LEFT:
		GetEffect()->GetCollider()->SetOffset_X(-80);
		break;

	case DIR::RIGHT:
		GetEffect()->GetCollider()->SetOffset_X(80);
		break;
	}

	
	GetEffect()->GetCollider()->SetEnable(true);
	
}

bool GiantSkullWarrior::AttackExit()
{
	// 공격 이펙트가 끝났는지
	// 공격 이펙트가 끝나면 충돌을 끝내야 함
	// 콜리전매니저에 플레이어와 충돌이 있다면 삭제
	
	Animation* attAnim = GetAnimator()->GetCurAnimation();
	std::wstring attAnimName = GetAttAnimName();
	
	switch (mDir)
	{
	case DIR::LEFT:
		attAnimName += L"Left";
		break;

	case DIR::RIGHT:
		attAnimName += L"Right";
		break;
	}

	if (attAnim == GetAnimator()->FindAnimation(attAnimName))
	{
		if (attAnim->IsFinished())
		{
			// Effect의 콜라이더
			GetEffect()->GetCollider()->SetEnable(false);
			return true;
		}
	}

	// 충돌 강제 종료
	auto& rels = mEffect->GetRelations();
	for (int i = 0; i < rels.size(); ++i)
	{
		if (OBJECT_TYPE::PLAYER == rels[i].mOther->GetType())
		{
			CollisionMgr::GetInstance().CollisionForceQuit(rels[i].mOther->GetCollider(), mEffect->GetCollider());
		}
	}
	


	return false;
}
