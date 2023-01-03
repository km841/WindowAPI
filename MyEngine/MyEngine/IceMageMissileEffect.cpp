#include "pch.h"
#include "IceMageMissileEffect.h"
#include "Animator.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Player.h"
#include "IceBullet.h"
#include "Animation.h"
#include "EventRegisteror.h"

IceMageMissileEffect::IceMageMissileEffect()
	: mAttFlag(false)
	, mAttCompleteFlag(false)
	, mBulletMaxSize(6)
	, mInitDegree(30.f)
	, mDegreeOffset(60.f)
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* iceBulletHitTex = LOAD_TEXTURE(L"IceCristalAnimTex", L"Texture\\IceCristalAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"IceCristalAnim",
		iceBulletHitTex,
		Vec2(0.f, 0.f),
		Vec2(93.f, 108.f),
		Vec2(93.f, 0.f),
		0.05f,
		21
	);
}

IceMageMissileEffect::~IceMageMissileEffect()
{
}

void IceMageMissileEffect::Initialize()
{
	MonsterMissileEffect::Initialize();
}

void IceMageMissileEffect::Update()
{
	GameObject::Update();
}

void IceMageMissileEffect::Render()
{
	GameObject::Render();
}

bool IceMageMissileEffect::Attack()
{
	// 플레이어 위치로 이동
	// 크리스탈을 소환하고 
	// 애니메이션이 끝나고 n프레임에 6방향으로 미사일 생성
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		

		if (false == mAttFlag)
		{
			SetPos(player->GetPos());
			mAttFlag = true;
			
			GetAnimator()->SelectAnimation(L"IceCristalAnim", false);
			GetAnimator()->GetCurAnimation()->Reset();
		}

		else
		{
			Animation* anim = GetAnimator()->GetCurAnimation();
			if (nullptr != anim)
			{
				if (anim->IsFinished())
				{
					mAttCompleteFlag = false;
					mAttFlag = false;
					return false;
				}

				switch (anim->GetCurFrame())
				{
				case 17:
				{
					if (false == mAttCompleteFlag)
					{
						Vec2 playerPos = player->GetPos();
						Vec2 initDir = Vec2(1, 0);

						for (int i = 0; i < mBulletMaxSize; ++i)
						{
							float curAngle = Math::DegreeToRadian(mInitDegree + (mDegreeOffset * i));
							
							IceBullet* bullet = new IceBullet;
							bullet->SetPos(GetPos());
							bullet->SetBulletWayType(BULLET_WAY_TYPE::LINEAR);
							bullet->SetDir(Math::RotateVector(initDir, curAngle));
							bullet->SetAngle(curAngle);

							bullet->Initialize();
							EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
						}
						mAttCompleteFlag = true;
					}
				}
				break;

				}
			}
		}
	}

	return true;
}
