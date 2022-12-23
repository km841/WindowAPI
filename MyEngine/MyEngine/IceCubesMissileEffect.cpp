#include "pch.h"
#include "IceCubesMissileEffect.h"
#include "Player.h"
#include "IceBullet.h"
#include "EventRegisteror.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"

IceCubesMissileEffect::IceCubesMissileEffect()
	: mMaxDuration(0.2f)
	, mCurDuration(0.f)
	, mMaxBulletCount(4.f)
	, mCurBulletCount(0.f)
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* iceBulletHitTex = ResourceMgr::GetInstance().Load<Texture>(L"IceBulletHitTex", L"Texture\\IceBulletHit.bmp");
	GetAnimator()->RegisterAnimation(
		L"IceBulletHitAnim",
		iceBulletHitTex,
		Vec2(0.f, 0.f),
		Vec2(75.f, 75.f),
		Vec2(75.f, 0.f),
		0.05f,
		3
	);

	GetAnimator()->FindAnimation(L"IceBulletHitAnim")->SetEffectAnimation(true);
	GetAnimator()->FindAnimation(L"IceBulletHitAnim")->SetOffset(Vec2(0.f, -20.f));
}

IceCubesMissileEffect::~IceCubesMissileEffect()
{
}

void IceCubesMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void IceCubesMissileEffect::Update()
{
	MonsterMissileEffect::Update();
}

void IceCubesMissileEffect::Render()
{
	Effect::Render();
}

void IceCubesMissileEffect::Destroy()
{
}

bool IceCubesMissileEffect::Skill()
{
	// 몬스터의 임의 위치에서 IceBullet 3개 소환
	// 터지는 이펙트와 함께 발사

	if (mMaxBulletCount < mCurBulletCount)
	{
		mCurBulletCount = 0.f;
		mCurDuration = 0.f;
		mPlayerDir = ZERO_VECTOR;
		return false;
	}

	else
	{
		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			if (mMaxDuration < mCurDuration)
			{
				mCurBulletCount++;
				mCurDuration = 0.f;
				Vec2 playerPos = player->GetPos();
				Vec2 monsterPos = GetPos();
				Vec2 effectPos = GetPos();

				int randValue = (int)(rand() % 20);
				bool signValue = rand() % 2;

				
				if (mPlayerDir.IsZero())
				{
					mPlayerDir = playerPos - monsterPos;
					mPlayerDir.Norm();
				}

				float angle = atan2(mPlayerDir.y, mPlayerDir.x);

				if (signValue)
				{
					randValue = -randValue;
				}

				effectPos += (float)randValue;

				IceBullet* bullet = new IceBullet;
				bullet->SetDir(mPlayerDir);
				bullet->SetPos(effectPos);
				bullet->SetAngle(angle);
				bullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);
				bullet->Initialize();

				GetAnimator()->SelectAnimation(L"IceBulletHitAnim", false);
				GetAnimator()->GetCurAnimation()->Reset();
				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

			else
			{
				mCurDuration += DT;
			}

		}
	}


	return true;
}
