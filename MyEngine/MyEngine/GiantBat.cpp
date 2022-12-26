#include "pch.h"
#include "GiantBat.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "MultipleMissileEffect.h"
#include "Player.h"
#include "CameraMgr.h"
#include "TimeMgr.h"

GiantBat::GiantBat()
{
	mToolID = TOOL_ID::BTN_GIANT_BAT;
	mMonType = MONSTER_TYPE::FLY_RANGE;
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"GiantBat_Move";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"GiantBat_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"GiantBat_Att";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"GiantBat_Move";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(moveAnimName);
	SetPatrolStateAnimName(moveAnimName);
	SetAttStateAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"GiantBatAnimTex", L"Texture\\giant_bat_animation.bmp");

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 192.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 384.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 576.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);

	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	MultipleMissileEffect* effect = new MultipleMissileEffect;
	effect->SetOwner(this);
	SetEffect(effect);

	//SetAttFixFrame(3);
}

GiantBat::~GiantBat()
{
}

void GiantBat::Initialize()
{
	Monster::Initialize();
}

void GiantBat::Update()
{
	Monster::Update();
	if (nullptr != mEffect)
	{
		mEffect->Update();
	}
}

void GiantBat::Render()
{
	Monster::Render();
}

void GiantBat::Destroy()
{
	Monster::Destroy();
}

void GiantBat::OnCollision(Collider* _other)
{
}

void GiantBat::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void GiantBat::OnCollisionExit(Collider* _other)
{
}

bool GiantBat::Attack()
{
	return mEffect->Attack();
}

void GiantBat::Trace()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		mPrevDir = mDir;

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = GetPos();
		Vec2 dirVec = monsterPos - playerPos;
		dirVec.Norm();

		if (abs(playerPos.x - monsterPos.x) < mInfo.mAttRange &&
			(playerPos - monsterPos).Len() > mInfo.mAttRange)
		{
			if (0 > dirVec.x)
			{
				mDir = DIR::RIGHT;
			}

			else
			{
				mDir = DIR::LEFT;
			}

			monsterPos -= dirVec * mInfo.mSpeed * DT;
		}

		else
		{
			if (0 > dirVec.x)
			{
				monsterPos.x += mInfo.mSpeed * DT;
				mDir = DIR::RIGHT;
			}

			else
			{
				monsterPos.x -= mInfo.mSpeed * DT;
				mDir = DIR::LEFT;
			}
		}

		SetPos(monsterPos);

		if (mPrevDir != mDir)
		{
			const std::wstring& animName = GetMoveAnimName();
			switch (mDir)
			{
			case DIR::LEFT:
				GetAnimator()->SelectAnimation(animName + L"Left", true);
				break;

			case DIR::RIGHT:
				GetAnimator()->SelectAnimation(animName + L"Right", true);
				break;
			}
		}
	}
}

bool GiantBat::DetectPlayer()
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -150 ~ -180 (하단 150, 좌측면 180) // 우측도 마찬가지

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				// 플레이어 위치에서 내 위치를 뺀 벡터

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	return false;
}

bool GiantBat::DetectIntoAttRange()
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -140 ~ -180 (하단 150, 좌측면 180) // 우측도 마찬가지

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x - mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = attRangeVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				// 플레이어 위치에서 내 위치를 뺀 벡터

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x + mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = monsterPos - attRangeVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	//wchar_t szBuffer[256] = {};
	//swprintf_s(szBuffer, L"angle : %f", angle);
	//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
	return false;
}

void GiantBat::RecogLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
	{
	case DIR::LEFT:
		dirVec = Vec2(-1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(10.f));
		break;

	case DIR::RIGHT:
		dirVec = Vec2(1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(-10.f));
		break;
	}

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mRecog;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mRecog;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mRecog - offset));
}

void GiantBat::AttRangeLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
	{
	case DIR::LEFT:
		dirVec = Vec2(-1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(10.f));
		break;

	case DIR::RIGHT:
		dirVec = Vec2(1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(-10.f));
		break;
	}

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mAttRange;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mAttRange;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mAttRange - offset));
}

void GiantBat::Dead()
{
	GetCollider()->SetEnable(false);

	MonsterEffect* effect = GetEffect();
	if (nullptr != effect)
	{
		if (nullptr != effect->GetCollider())
		{
			effect->GetCollider()->SetEnable(false);
		}
	}

	GameObject::Dead();
}