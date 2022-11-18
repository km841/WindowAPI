#include "pch.h"
#include "ShortSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "Animator.h"
#include "Animation.h"
#include "Effect.h"

ShortSword::ShortSword()
{
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON_1);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(51.f);
	SetYOffset(8.f);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Effect* effect = new Effect;
	effect->SetOwner(this);
	effect->SetSize(Vec2(120.f, 120.f));
	effect->SetOffset(Vec2(30.f, 10.f));
	effect->CreateComponent(new Animator);
	effect->GetAnimator()->SetOwner(effect);

	Texture* swordTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* swordEffectTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSwordEff", L"Texture\\ShortSword_Effect.bmp");

	Animation* swordEffect = 
		effect->GetAnimator()->CreateAnimation(L"ShortSwordEffect", swordEffectTex, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(40.f, 0.f), 0.1f, 3);
	swordEffect->SetOwner(effect->GetAnimator());

	effect->GetAnimator()->AddAnimation(L"ShortSwordEffect", swordEffect);

	SetEffect(effect);
}

ShortSword::~ShortSword()
{
}

void ShortSword::Initialize()
{
	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	
	SetTexture(texture);
	SetTransTexture(transTexture);
	Sword::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(texture->GetSize());
}

void ShortSword::Update()
{
	// �ִϸ��̼� ������Ʈ
	// X, Y��ǥ �˾ƾ� ��
	// Į ���� �������� �̵��� ����
	SetPrevSwordState(GetSwordState());

	if (IS_JUST_LBUTTON_CLICKED)
	{
		ChangeSwordState();
	}

	if (GetPrevSwordState() != GetSwordState())
	{
		Animation* rotAnim = GetEffect()->GetAnimator()->FindAnimation(L"ShortSwordEffectRot");
		if (nullptr != rotAnim && rotAnim->IsFinished())
		{
			rotAnim->Reset();
		}
		GetEffect()->GetAnimator()->RotSelectAnimation(L"ShortSwordEffect", GetAngle(), false);
	}

	Effect* effect = GetEffect();
	if (nullptr != effect)
		effect->Update();

	Sword::Update();
}

void ShortSword::Render()
{

	// �ִϸ��̼� ����
	Sword::Render();

	Effect* effect = GetEffect();
	if (nullptr != effect)
	{
		Animation* anim = effect->GetAnimator()->FindAnimation(L"ShortSwordEffectRot");
		if (nullptr != anim)
		{

		Texture* tex = anim->GetTexture();

			BitBlt(BACK_BUF_DC,
				100, 100,
				tex->GetWidth(),
				tex->GetHeight(),
				tex->GetDC(),
				0, 0,
				SRCCOPY
			);
		}


		effect->Render();
	}
}
