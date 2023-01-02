#include "pch.h"
#include "DustEffect.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "Monster.h"
#include "EventRegisteror.h"

DustEffect::DustEffect()
	:mTex(nullptr)
{
	mTex = LOAD_TEXTURE(L"MinoDust", L"Texture\\MinoDashEffect.bmp");

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->RegisterAnimation(
		L"MinoDashAnim_Left",
		mTex,
		Vec2(0, 0),
		Vec2(276, 108),
		Vec2(276, 0),
		0.1f,
		8
	);

	GetAnimator()->RegisterAnimation(
		L"MinoDashAnim_Right",
		mTex,
		Vec2(0, 108),
		Vec2(276, 108),
		Vec2(276, 0),
		0.1f,
		8
	);

	GetAnimator()->FindAnimation(L"MinoDashAnim_Left")->SetTransMode(true, 0.8f, TRANS_MODE::FADE_OUT);
	GetAnimator()->FindAnimation(L"MinoDashAnim_Right")->SetTransMode(true, 0.8f, TRANS_MODE::FADE_OUT);
}

DustEffect::~DustEffect()
{
}

void DustEffect::Initialize()
{
	Monster* monster = static_cast<Monster*>(GetOwner());
	Vec2 monsterPos = monster->GetPos();
	switch (monster->GetDir())
	{
	case DIR::LEFT:
		GetAnimator()->SelectAnimation(L"MinoDashAnim_Left", false);
		monsterPos.x += 50.f;
		break;

	case DIR::RIGHT:
		GetAnimator()->SelectAnimation(L"MinoDashAnim_Right", false);
		monsterPos.x -= 50.f;
		break;
	}
	
	SetPos(monsterPos);
}

void DustEffect::Update()
{
	GameObject::Update();

	if (GetAnimator()->GetCurAnimation()->IsFinished())
	{
		SetObjState(OBJECT_STATE::DEAD);
	}
}

void DustEffect::Render()
{
	GameObject::Render();
}

void DustEffect::SetDustAnimation()
{

	
}
