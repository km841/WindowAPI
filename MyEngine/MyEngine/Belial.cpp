#include "pch.h"
#include "Belial.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "BelialCore.h"
#include "BelialHand.h"

Belial::Belial()
{
	mMonType = MONSTER_TYPE::BOSS_BELIAL;
	SetGravity(false);
	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_Tex", L"Texture\\Monster\\Belial\\Belial_Body_Anim.bmp");
	Texture* hitTex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Body_HitTex", L"Texture\\Monster\\Belial\\Belial_Body_HitAnim.bmp");

	SetBossName(L"벨리알");
	SetBossComment(L"감옥의 수문장");

	std::wstring idleAnimName = L"Belial_Idle";
	SetIdleAnimName(idleAnimName);

	GetCollider()->SetSize(Vec2(100, 100));
	GetCollider()->SetOffset(Vec2(25, -50));

	GetAnimator()->RegisterAnimation(
		idleAnimName,
		tex,
		Vec2(0, 0),
		Vec2(210, 297),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Open",
		tex,
		Vec2(0, 297),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->RegisterAnimation(
		L"Belial_Attack_Close",
		tex,
		Vec2(0, 681),
		Vec2(210, 384),
		Vec2(210, 0),
		0.1f,
		10
	);

	GetAnimator()->FindAnimation(idleAnimName)->SetTransMode(true, 3.f, TRANS_MODE::FADE_IN);
	GetAnimator()->FindAnimation(idleAnimName)->SetHitAnimation(hitTex);

	GetAnimator()->SelectAnimation(idleAnimName, true);

	// 애니메이션에서 현재 LT값을 가져와서 LT값에 대한 출력을 다른 스프라이트 파일로 대신함.
	// 덮어씌우는게 답일듯.
	// 덮어 씌우고 나서 해당 프레임의 애니메이션이 끝날 타이밍에 그 이미지도 지워 주면 됨
	// 애니메이션에 따로 저장해야 되나?
	// 피격 시 애니메이션에 연락을 주고 애니메이션이 해당 프레임에 맞는 피격 애니메이션을 출력하면 됨
	// 그리고 애니메이션 해당 프레임이 끝나게 되면 피격 애니메이션(빨간색) 제거.

	// 1. 피격 애니메이션 유무를 선택함.
	// 2. 피격 애니메이션 유무 값이 TRUE인 경우에는
	// 3. Owner가 피격 메시지를 전달할 경우 해당 LT값에 맞는 빨간 이미지를 덧씌운다.
	// 4. 그러려면 애니메이션에 텍스쳐를 하나 더 추가해야 함
	// 5. 1프레임으로 하면 너무 찰나의 순간이라 빨간색이 된게 티가 안날 수가 있음
	// 6. 시간으로 정해서 n초동안 빨간 애니메이션이 덧씌워지게 됨
	// 7. die인 경우에는? 애니메이션이 바뀌니까 상관이 없다.
	
	BelialCore* belialCore = new BelialCore;
	belialCore->SetOwner(this);
	belialCore->SetOffset(Vec2(25, 0));

	SetEffect(belialCore);
	// 후방 Core는 Effect
	// Hand는? 이펙트인데 소멸자에서 따로 처리


	mLeftHand = new BelialHand(BELIAL_HAND_TYPE::LEFT_HAND);
	mRightHand = new BelialHand(BELIAL_HAND_TYPE::RIGHT_HAND);
}

Belial::~Belial()
{
}

void Belial::Initialize()
{
	//BossHPHUD 활성화
	//BelialCore 소환
	//Hand 2개 소환

	Vec2 curPos = GetPos();
	curPos += Vec2(25, -50);
	
	Vec2 leftHandPos = curPos;
	Vec2 rightHandPos = curPos;

	leftHandPos.x -= 400.f;
	leftHandPos.y += 150.f;

	rightHandPos.x += 400.f;
	rightHandPos.y -= 100.f;

	mLeftHand->SetPos(leftHandPos);
	mRightHand->SetPos(rightHandPos);

	BossMonster::Initialize();

}

void Belial::Update()
{
	BossMonster::Update();

	if (nullptr != mLeftHand)
	{
		mLeftHand->Update();

	}

	if (nullptr != mRightHand)
	{
		mRightHand->Update();
	}

}

void Belial::Render()
{
	BossMonster::Render();

	if (nullptr != mLeftHand)
	{
		mLeftHand->Render();
	}

	if (nullptr != mRightHand)
	{
		mRightHand->Render();
	}
}

void Belial::Destroy()
{
	BossMonster::Destroy();

	if (nullptr != mLeftHand)
	{
		mLeftHand->Destroy();
		delete mLeftHand;
		mLeftHand = nullptr;
	}

	if (nullptr != mRightHand)
	{
		mRightHand->Destroy();
		delete mRightHand;
		mRightHand = nullptr;
	}


}

void Belial::OnCollision(Collider* _other)
{
}

void Belial::OnCollisionEnter(Collider* _other)
{
	BossMonster::OnCollisionEnter(_other);
}

void Belial::OnCollisionExit(Collider* _other)
{
}

bool Belial::Skill()
{
	return false;
}
