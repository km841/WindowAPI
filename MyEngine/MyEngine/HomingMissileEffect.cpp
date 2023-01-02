#include "pch.h"
#include "HomingMissileEffect.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "MagicWandBullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"
#include "Collider.h"
#include "Monster.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraMgr.h"
#include "Item.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "LaraMagicWand.h"
#include "Sound.h"

HomingMissileEffect::HomingMissileEffect()
	: mAngleLimit(Math::DegreeToRadian(3.f))
	, mReload(false)
	, mReloadMaxDelay(1.0f)
	, mReloadDelay(0.f)
	, mAcc(0.f)
	, mVelocity(0.f)
	, mAnimStart(false)
	, mSound(nullptr)
	, mSkillSound(nullptr)
	, mReloadBeginSound(nullptr)
	, mReloadEndSound(nullptr)
{
	mSound = LOAD_SOUND(L"LaraShotSound", L"Sound\\LaraMagicWandShot.wav");
	mSkillSound = LOAD_SOUND(L"LaraSkillSound", L"Sound\\LaraMagicWandSkill.wav");
	mReloadBeginSound = LOAD_SOUND(L"ReloadBegin", L"Sound\\ReloadBegin.wav");
	mReloadEndSound = LOAD_SOUND(L"ReloadEnd", L"Sound\\ReloadEnd.wav");

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	//SetOffset(Vec2(15.f, -25.f));

	mReloadBaseTex = LOAD_TEXTURE(L"ReloadBaseTex", L"Texture\\ReloadBase.bmp");
	mReloadTex = LOAD_TEXTURE(L"ReloadBarTex", L"Texture\\ReloadBar.bmp");

	Texture* laraBulletTex = LOAD_TEXTURE(L"LaraBulletAnim", L"Texture\\LaraBulletAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"LaraBulletHit",
		laraBulletTex,
		Vec2(0.f, 39.f),
		Vec2(108.f, 105.f),
		Vec2(108.f, 0.f),
		0.025f,
		7
	);

	GetAnimator()->FindAnimation(L"LaraBulletHit")->SetEffectAnimation(true);
	GetAnimator()->FindAnimation(L"LaraBulletHit")->SetOffset(Vec2(15.f, -25.f));


	Texture* reloadAnim = LOAD_TEXTURE(L"ReloadTex", L"Texture\\ReloadAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"ReloadAnim",
		reloadAnim,
		Vec2(0, 0),
		Vec2(81, 27),
		Vec2(81, 0),
		0.05f,
		4
	);


	mOffset = Vec2(0.f, -70.f);
	GetAnimator()->FindAnimation(L"ReloadAnim")->SetOffset(mOffset);
	GetAnimator()->FindAnimation(L"ReloadAnim")->SetEffectAnimation(true);
	mVelocity = (mReloadBaseTex->GetWidth() - 5) / mReloadMaxDelay;
}

HomingMissileEffect::~HomingMissileEffect()
{
}

void HomingMissileEffect::Update()
{
	Effect::Update();
	// 좌클릭이 눌리면 탄환 발사

	LaraMagicWand* ownerItem = static_cast<LaraMagicWand*>(GetOwnerItem());
	CoolDownUpdate();

	if (true == mAnimStart)
	{
		mReloadDelay = 0.f;
		mAcc = 0.f;
		mAnimStart = false;
		static_cast<Item*>(GetOwnerItem())->Reload();
		
		if (nullptr != mReloadEndSound)
			mReloadEndSound->Play(false);
	}

	if (mReload)
	{
		if (mReloadMaxDelay < mReloadDelay)
		{
			// 장전애니메이션

			if (false == mAnimStart)
			{
				mAnimStart = true;
				mReload = false;
				GetAnimator()->SelectAnimation(L"ReloadAnim", false);
				GetAnimator()->GetCurAnimation()->Reset();
			}
		}

		else
		{
			mReloadDelay += DT;
			mAcc += mVelocity * DT;
		}
	}

	if (IS_JUST_LBUTTON_CLICKED && false == mReload)
	{
		ShotBullet();
		GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
		GetAnimator()->GetCurAnimation()->Reset();
		if (nullptr != mSound)
		{
			mSound->Play(false);
		}
	}

	if (IS_JUST_PRESSED(KEY::Q) && false == ownerItem->GetCoolDownFlag())
	{
		SkillActivation();
		if (nullptr != mSkillSound)
		{
			mSkillSound->Play(false);
		}
	}
	
}

void HomingMissileEffect::Render()
{
	Effect::Render();

	if (mReload)
	{
		Vec2 baseSize = mReloadBaseTex->GetSize();
		Vec2 barSize = mReloadTex->GetSize();

		Vec2 pos = RENDER_POS(GetPos());
		Vec2 reloadBasePos = pos + mOffset;

		BitBlt(
			BACK_BUF_DC,
			(int)(reloadBasePos.x - baseSize.x / 2.f),
			(int)(reloadBasePos.y - baseSize.y / 2.f),
			(int)(baseSize.x),
			(int)(baseSize.y),
			mReloadBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);

		BitBlt(
			BACK_BUF_DC,
			(int)((reloadBasePos.x - (baseSize.x / 2.f)) + mAcc),
			(int)((reloadBasePos.y - (barSize.y / 2.f))),
			(int)(barSize.x),
			(int)(barSize.y),
			mReloadBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);
	}
}

void HomingMissileEffect::Destroy()
{
}

void HomingMissileEffect::Change()
{
	std::vector<MagicWandBullet*>::iterator iter = mBullets.begin();

	for (; iter != mBullets.end();)
	{
		EventRegisteror::GetInstance().DeleteObject(*iter);
		iter = mBullets.erase(iter);
	}

	mBullets.clear();
}

void HomingMissileEffect::CoolDownUpdate()
{
	LaraMagicWand* ownerItem = static_cast<LaraMagicWand*>(GetOwnerItem());
	if (ownerItem->GetCoolDownFlag())
	{
		float& curCoolDown = ownerItem->GetCurCoolDown();

		if (ownerItem->GetMaxCoolDown() < curCoolDown)
		{
			curCoolDown = 0.f;
			ownerItem->SetCoolDownFlag(false);

		}
		else
		{
			curCoolDown += DT;
		}
	}
}

void HomingMissileEffect::ShotBullet()
{
	Item* owner = static_cast<Item*>(GetOwnerItem());
	ItemInfo& info = owner->GetItemInfo();

	if (0.f < info.mAmmo)
	{
		info.mAmmo--;

		MagicWandBullet* bullet = new MagicWandBullet;
		bullet->SetPos(GetPos());

		Vec2 mousePos = MOUSE_POS;
		Vec2 playerPos = RENDER_POS(Player::GetPlayer()->GetPos());

		Vec2 dirVec = mousePos - playerPos;
		dirVec.Norm();

		bullet->SetInitDirVector(dirVec);
		EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());


	}

	else if (0.f == info.mAmmo)
	{
		mReload = true;
		
		if (nullptr != mReloadBeginSound)
			mReloadBeginSound->Play(false);
	}
}

void HomingMissileEffect::SkillActivation()
{
	LaraMagicWand* ownerItem = static_cast<LaraMagicWand*>(GetOwnerItem());
	ownerItem->SetCoolDownFlag(true);
	// 8방향
	Vec2 dirArray[] = {
		Vec2(-1, -1),
		Vec2(0, -1),
		Vec2(1, -1),
		Vec2(1, 0),
		Vec2(1, 1),
		Vec2(0, 1),
		Vec2(-1, 1),
		Vec2(-1, 0),
	};

	for (int i = 0; i < std::size(dirArray); ++i)
	{
		MagicWandBullet* bullet = new MagicWandBullet;
		bullet->SetPos(GetPos());
		bullet->SetInitDirVector(dirArray[i]);
		EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
	}
}
