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
#include "SwordHitEffect.h"
#include "CollisionMgr.h"

ShortSword::ShortSword()
	:mCurDuration(0.f)
	,mAttFlag(false)
{
	// ShortSword�� ���ݷ��� Player�� ���ݷ��� ������ �޴´�.

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
	

	Texture* swordTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* swordEffectTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSwordEff", L"Texture\\ShortSword_Effect.bmp");
	Texture* swordEquipTex = ResourceMgr::GetInstance().Load<Texture>(L"ShortSwordEquip", L"Texture\\ShortSwordEquip.bmp");
	

	Animation* swordEffect = 
		effect->GetAnimator()->CreateAnimation(L"ShortSwordEffect", swordEffectTex, Vec2(0.f, 0.f), Vec2(120.f, 120.f), Vec2(120.f, 0.f), 0.075f, 3);
	swordEffect->SetOwner(effect->GetAnimator());

	effect->GetAnimator()->AddAnimation(L"ShortSwordEffect", swordEffect);
	SetEffect(effect);

	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	SetTexture(texture);
	SetTransTexture(transTexture);
	SetEquipedTexture(swordEquipTex);
}

ShortSword::~ShortSword()
{
	PlayerEffect* effect = GetEffect();
	if (nullptr != effect)
	{
		delete effect;
	}
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
	// �ִϸ��̼� ������Ʈ
	// X, Y��ǥ �˾ƾ� ��
	// Į ���� �������� �̵��� ����

	SetPrevSwordState(GetSwordState());

	// ���� ������
	if (GetDuration() > mCurDuration)
	{
		mCurDuration += DT;
	}
	else
	{
		// �浹ü�� �����ִ� �ð�
		if (true == mAttFlag)
		{
			// �� �б�� ���Դٴ°� ������ ������ �ߴٴ� �Ű� ���õ� Duration�� �Ѿ�����̹Ƿ�
			// �ִϸ��̼��� ������ ���� �ִϸ��̼��� ���۵� �Ŷ�� ��
			mAttFlag = false;
			GetEffect()->GetCollider()->SetEnable(false);
			// ���Ͱ� �ִٸ� �浹�� ������Ŵ
			
			auto& rels = GetEffect()->GetRelations();
			for (int i = 0; i < rels.size(); ++i)
			{
				if (OBJECT_TYPE::MONSTER == rels[i].mOther->GetType())
				{
					CollisionMgr::GetInstance().CollisionForceQuit(rels[i].mOther->GetCollider(), GetEffect()->GetCollider());
					break;
				}
			}

			
		}

		if (IS_JUST_LBUTTON_CLICKED)
		{
			ChangeSwordState();
			CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::SHAKE, 0.01f);
			mCurDuration = 0.f;

			GetEffect()->GetCollider()->SetEnable(true);
			mAttFlag = true;
			// Į Effect �浹ü�� ������ �浹ü �浹
			// Į Effect �浹ü�� ��� ���ǵǾ�� �ϴ°�?
			// Į Effect �浹ü�� ���ݽ� Effect ��ġ�� ��� �浹ü�� ������
			// �浹�� �Ͼ�� �� ��� �浹ü Disable
			// ���� ��� �߻� ������ ��� ����?
			// ���� ������? �浹ü�� ũ�⸦ �� ũ�� ��Ƽ� �浹�ǰԲ� ��
			// ��/�쿡 ���� offset ���� ��
			// �浹ü�� ����� �Ѵ�?


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

		//wchar_t buf[256] = {};
		//swprintf_s(buf, L"%f", degree);
		//SetWindowText(APP_INSTANCE.GetHwnd(), buf);

		if (abs(degree) > 115.f)
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
		
		GetEffect()->SetAngle(angle);
		GetEffect()->SetOffset(basicOffset + effDirVec * 30.f);
		GetEffect()->GetAnimator()->RotSelectAnimation(L"ShortSwordEffect", angle, false);
	}

	//Effect* effect = GetEffect();
	//if (nullptr != effect)
	//	effect->Update();

	Sword::Update();
}

void ShortSword::Render()
{

	// �ִϸ��̼� ����
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

void ShortSword::Change()
{
	mAttFlag = false;
	GetEffect()->GetCollider()->SetEnable(false);
	// ���Ͱ� �ִٸ� �浹�� ������Ŵ

	auto& rels = GetEffect()->GetRelations();
	for (int i = 0; i < rels.size(); ++i)
	{
		if (OBJECT_TYPE::MONSTER == rels[i].mOther->GetType())
		{
			CollisionMgr::GetInstance().CollisionForceQuit(rels[i].mOther->GetCollider(), GetEffect()->GetCollider());
			break;
		}
	}

}
