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
#include "Collider.h"
#include "EventRegisteror.h"

ShortSword::ShortSword()
	:mCurDuration(0.f)
{
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(51.f);
	SetYOffset(8.f);
	SetDuration(0.225f);

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Effect* effect = new Effect;
	effect->SetOwner(Player::GetPlayer());
	effect->SetSize(Vec2(120.f, 120.f));
	effect->SetOffset(Vec2(0.f, 40.f));
	effect->CreateComponent(new Animator);
	effect->GetAnimator()->SetOwner(effect);
	effect->CreateComponent(new Collider);
	effect->GetCollider()->SetOwner(effect);
	effect->GetCollider()->SetSize(Vec2(30, 75));
	effect->GetCollider()->SetOffset(Vec2(0, -70));
	effect->GetCollider()->SetEnable(false);
	

	Texture* swordTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* swordEffectTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSwordEff", L"Texture\\ShortSword_Effect.bmp");

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

ShortSword::~ShortSword()
{
	Effect* effect = GetEffect();
	if (nullptr != effect)
		delete effect;
}

void ShortSword::Initialize()
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

void ShortSword::Update()
{
	// 애니메이션 업데이트
	// X, Y좌표 알아야 함
	// 칼 현재 각도에서 이동한 각도
	SetPrevSwordState(GetSwordState());

	if (GetEffect()->GetCollider()->GetEnable())
	{
		GetEffect()->GetCollider()->SetEnable(false);
	}

	// 공격 딜레이
	if (GetDuration() > mCurDuration)
	{
		mCurDuration += DT;
	}
	else
	{
		if (IS_JUST_LBUTTON_CLICKED)
		{
			ChangeSwordState();
			CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::SHAKE, 0.01f);
			mCurDuration = 0.f;

			GetEffect()->GetCollider()->SetEnable(true);

			// 칼 Effect 충돌체와 몬스터의 충돌체 충돌
			// 칼 Effect 충돌체는 어떻게 정의되어야 하는가?
			// 칼 Effect 충돌체는 공격시 Effect 위치에 잠깐 충돌체를 가진다
			// 충돌이 일어나면 그 즉시 충돌체 Disable
			// 공격 모션 발생 시점을 어떻게 잡지?
			// 공격 범위는? 충돌체의 크기를 꽤 크게 잡아서 충돌되게끔 함
			// 좌/우에 따라 offset 값을 줌
			// 충돌체가 원운동을 한다?

			
		}
	}

	if (GetPrevSwordState() != GetSwordState())
	{
		Animation* rotAnim = GetEffect()->GetAnimator()->FindAnimation(L"ShortSwordEffectRot");
		if (nullptr != rotAnim && rotAnim->IsFinished())
		{
			rotAnim->Reset();
		}
		Vec2 dirVec = {1.f, 0.f};
		DIR dir = Player::GetPlayer()->GetPlayerDir();

		Vec2 mousePos = MOUSE_POS;
		Vec2 effectPos = RENDER_POS(GetEffect()->GetPos());
		Vec2 effDirVec = mousePos - effectPos;

		effDirVec.Norm();
		mousePos.Norm();

		float angle = GetAngle();
		float degree = Math::RadianToDegree(angle);

		wchar_t buf[256] = {};
		swprintf_s(buf, L"%f", degree);
		SetWindowText(APP_INSTANCE.GetHwnd(), buf);

		if (abs(degree) > 150.f)
		{
			Vec2 effColOffset = GetEffect()->GetCollider()->GetOffset();
			GetEffect()->GetCollider()->SetOffset_Y(20.f);
		}
		else
		{
			GetEffect()->GetCollider()->SetOffset_Y(-20.f);
		}

		Player* player = Player::GetPlayer();
		DIR playerDir = player->GetPlayerDir();
		Vec2 basicOffset = {};

		switch (playerDir)
		{
		case DIR::LEFT:
			basicOffset = Vec2(-25.f, -15.f);
			GetEffect()->GetCollider()->SetOffset_X(-15.f);
			break;

		case DIR::RIGHT:
			basicOffset = Vec2(25.f, -15.f);
			GetEffect()->GetCollider()->SetOffset_X(15.f);
			break;
		}
		
		GetEffect()->SetOffset(basicOffset + effDirVec * 13.f);
		GetEffect()->GetAnimator()->RotSelectAnimation(L"ShortSwordEffect", angle, false);
	}

	//Effect* effect = GetEffect();
	//if (nullptr != effect)
	//	effect->Update();

	Sword::Update();
}

void ShortSword::Render()
{

	// 애니메이션 렌더
	Sword::Render();

	//Effect* effect = GetEffect();
	//if (nullptr != effect)
	//{
	//	Animation* anim = effect->GetAnimator()->FindAnimation(L"ShortSwordEffectRot");
	//	if (nullptr != anim)
	//	{
	//		Texture* tex = anim->GetTexture();
	//		Vec2 effPos = RENDER_POS(effect->GetPos());
	//	}


	//	effect->Render();
	//}
}
