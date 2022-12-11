#include "pch.h"
#include "DemonSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "Animator.h"
#include "Animation.h"
#include "Effect.h"
#include "Collider.h"
#include "EventRegisteror.h"
#include "SwordHitEffect.h"
#include "CollisionMgr.h"

DemonSword::DemonSword()
{
	// ShortSword의 공격력은 Player의 공격력의 영향을 받는다.

	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(51.f);
	SetYOffset(8.f);
	SetDuration(0.225f);

	ItemInfo info = {};
	info.mAtt = 10.f;
	SetItemInfo(info);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	SwordHitEffect* effect = new SwordHitEffect;
	effect->SetOwner(Player::GetPlayer());
	effect->SetSize(Vec2(120.f, 120.f));
	effect->SetOffset(Vec2(0.f, 40.f));

	effect->GetCollider()->SetSize(Vec2(50, 75));
	effect->GetCollider()->SetOffset(Vec2(0, -70));
	effect->GetCollider()->SetEnable(false);
	effect->SetAtt(info.mAtt);


	Texture* swordTex = ResourceMgr::GetInstance().Load<Texture>(L"DemonSword", L"Texture\\ShortSword3.bmp");
	Texture* swordEffectTex = ResourceMgr::GetInstance().Load<Texture>(L"DemonSwordEff", L"Texture\\ShortSword_Effect.bmp");

	Animation* swordEffect =
		effect->GetAnimator()->CreateAnimation(L"ShortSwordEffect", swordEffectTex, Vec2(0.f, 0.f), Vec2(120.f, 120.f), Vec2(120.f, 0.f), 0.075f, 3);
	swordEffect->SetOwner(effect->GetAnimator());

	effect->GetAnimator()->AddAnimation(L"ShortSwordEffect", swordEffect);
	SetEffect(effect);

	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	SetTexture(texture);
	SetTransTexture(transTexture);
}

DemonSword::~DemonSword()
{
	PlayerEffect* effect = GetEffect();
	if (nullptr != effect)
	{
		delete effect;
	}
}

void DemonSword::Initialize()
{
	Sword::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(GetTexture()->GetSize());
	EventRegisteror::GetInstance().CreateObject(GetEffect(), GetEffect()->GetType());
}

void DemonSword::Update()
{
	Sword::Update();
}

void DemonSword::Render()
{
	Sword::Render();
}
