#include "pch.h"
#include "RedGiantBat.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "Player.h"

RedGiantBat::RedGiantBat()
{
	SetSize(Vec2(192.f, 192.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"RedGiantBat_Move";
	SetMoveAnimName(idleAnimName);

	std::wstring moveAnimName = L"RedGiantBat_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"RedGiantBat_Att";
	SetAttAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"RedGiantBatAnimTex", L"Texture\\red_giant_bat_animation.bmp");

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
}

RedGiantBat::~RedGiantBat()
{
}

void RedGiantBat::Initialize()
{
	Monster::Initialize();
}

void RedGiantBat::Update()
{
	Monster::Update();
}

void RedGiantBat::Render()
{
	Monster::Render();

	wchar_t batGravity[COMMENT_MAX_SIZE] = {};
	swprintf_s(batGravity, L"Gravity : %s", GetGravity() ? L"O" : L"X");
	TextOut(BACK_BUF_DC, 10, 130, batGravity, (int)wcslen(batGravity));
}

void RedGiantBat::Destroy()
{
	Monster::Destroy();
}

void RedGiantBat::OnCollision(Collider* _other)
{
}

void RedGiantBat::OnCollisionEnter(Collider* _other)
{
}

void RedGiantBat::OnCollisionExit(Collider* _other)
{
}

bool RedGiantBat::Attack()
{
	return false;
}

bool RedGiantBat::DetectPlayer()
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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

bool RedGiantBat::DetectIntoAttRange()
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

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
				{
					return true;
				}
			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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
