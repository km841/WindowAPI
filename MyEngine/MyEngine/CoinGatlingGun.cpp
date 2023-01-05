#include "pch.h"
#include "CoinGatlingGun.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Player.h"
#include "MouseMgr.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"
#include "CoinBullet.h"
#include "TimeMgr.h"
#include "Sound.h"
#include "Collider.h"

CoinGatlingGun::CoinGatlingGun()
	: mAttDelay(false)
	, mAttMaxDelay(0.01f)
	, mAttCurDelay(0.f)
	, mReady(false)
	, mReadyMaxTime(0.5f)
	, mReadyCurTime(0.f)
	, mReadyStart(false)
	, mReadySound(nullptr)
	, mShotSound(nullptr)
{
	mReadySound = LOAD_SOUND(L"GatlingReady", L"Sound\\GatlingReady.wav");
	mShotSound = LOAD_SOUND(L"GatlingShot", L"Sound\\GatlingShot.wav");

	SetType(OBJECT_TYPE::DROP_ITEM);
	SetItemType(ITEM_TYPE::WEAPON);
	SetOffset(Vec2(40.f, 5.f));
	SetLeftDirOffset(30.f);
	SetRightDirOffset(50.f);
	SetYOffset(12.f);

	ItemInfo info = {};
	info.mMinAtt = 5.f;
	info.mMaxAtt = 10.f;
	info.mAttSpeed = 20.f;
	info.mMaxAmmo = 0.f;
	info.mAmmo = info.mMaxAmmo;
	info.mItemName = L"코인 건";
	info.mItemComment = L"'돈이 많을수록 강해진다'";
	info.mRarity = RARITY::RARE;
	info.mWeaponType = WEAPON_TYPE::TWO_HAND;
	SetItemInfo(info);

	Texture* texture = LOAD_TEXTURE(L"CoinGunTex", L"Texture\\CoinGunLeft.bmp");
	mEquipTex = LOAD_TEXTURE(L"CoinGunEquipTex", L"Texture\\CoinGunEquipTex.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"CoinGunTrans", texture->GetSize());

	Texture* leftTex = LOAD_TEXTURE(L"CoinGunLeftTex", L"Texture\\CoinGunLeft.bmp");
	Texture* rightTex = LOAD_TEXTURE(L"CoinGunRightTex", L"Texture\\CoinGunRight.bmp");

	SetTexture(texture);
	SetTransTexture(transTexture);
	SetEquipedTexture(mEquipTex);
	SetLeftTexture(leftTex);
	SetRightTexture(rightTex);

	SetAngleOffset(PI / 2.f);

	//SetFallen(false);
}

CoinGatlingGun::~CoinGatlingGun()
{
}

void CoinGatlingGun::Initialize()
{
	Weapon::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(GetTexture()->GetSize());
}

void CoinGatlingGun::Update()
{
	if (mHasFallen)
	{
		GameObject::Update();
	}

	else
	{
		DIR dir = Player::GetPlayer()->GetPlayerDir();
		SetDir(dir);
		if (IS_JUST_LBUTTON_RELEASED)
		{
			mReadyCurTime = 0.f;
			mReadyStart = false;
			mReady = false;
		}


		if (false == mAttDelay)
		{
			if (IS_LBUTTON_CLICKED)
			{
				if (false == mReadyStart)
				{
					mReadyStart = true;
					if (nullptr != mReadySound)
					{
						mReadySound->Play(false);
					}
					// 사운드
				}

				if (false == mReady)
				{
					if (mReadyMaxTime < mReadyCurTime)
					{	
						mReady = true;
					}

					else
					{
						mReadyCurTime += DT;
					}
				}
				else
				{
					mAttDelay = true;
					CoinBullet* bullet = new CoinBullet;

					Vec2 curPos = GetPos();
					curPos.y -= 10.f;

					DIR dir = Player::GetPlayer()->GetPlayerDir();

					bullet->SetPos(curPos);

					Vec2 mousePos = MOUSE_POS;
					Vec2 playerPos = RENDER_POS(Player::GetPlayer()->GetPos());

					Vec2 dirVec = mousePos - playerPos;
					dirVec.Norm();

					bullet->SetDir(dirVec);
					EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());

					if (nullptr != mShotSound)
					{
						mShotSound->Play(false);
					}

					Player::GetPlayer()->DecreaseMoney();
					CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::SHAKE, 0.01f);
				}


			}
		}

		else
		{
			if (mAttMaxDelay < mAttCurDelay)
			{
				mAttCurDelay = 0.f;
				mAttDelay = false;
			}

			else
			{
				mAttCurDelay += DT;
			}
		}

		

		Weapon::Update();
	}
}

void CoinGatlingGun::Render()
{
	if (mHasFallen)
	{
		Vec2 pos = RENDER_POS(GetPos());
		Vec2 size = mEquipTex->GetSize();

		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - size.x / 2.f),
			(int)(pos.y - size.y / 2.f),
			(int)(size.x),
			(int)(size.y),
			mEquipTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255)
		);

		GameObject::Render();
	}

	else
	{
		Weapon::Render();
	}
}

void CoinGatlingGun::Destroy()
{
}
