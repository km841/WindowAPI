#include "pch.h"
#include "MonsterIdleState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"

MonsterIdleState::MonsterIdleState()
	: MonsterState(MONSTER_STATE::IDLE)
{
}

MonsterIdleState::~MonsterIdleState()
{
}

void MonsterIdleState::Update()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		Vec2 monsterPos = monster->GetPos();
		Vec2 playerPos = player->GetPos();

		DIR dir = monster->GetDir();
		DIR prevDir = monster->GetPrevDir();

		if (dir != prevDir)
		{
			switch (dir)
			{
			case DIR::LEFT:
				monster->GetAnimator()->SelectAnimation(monster->GetIdleAnimName() + L"Left", true);
				break;
			case DIR::RIGHT:
				monster->GetAnimator()->SelectAnimation(monster->GetIdleAnimName() + L"Right", true);
				break;
			}
		}
		// 플레이어가 인식범위 안이고,
		// 각도가 n도 미만이라면 인식

		MonsterInfo info = monster->GetMonsterInfo();
		// 몬스터가 left일 땐 플레이어 < 몬스터
		// 몬스터가 right일 땐 플레이어 > 몬스터

		bool detectFlag = false;
		float angle = 0.f;

		// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
		// 2. 몬스터에서 플레이어와의 벡터
		// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리

		

		switch (dir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - info.mRecog, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				if (angle < 20.f)
				{
					detectFlag = true;
				}
			}
		}


			break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + info.mRecog, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				if (angle < 20.f)
				{
					detectFlag = true;
				}
			}
		}
			break;
		}

		//wchar_t szBuffer[256] = {};
		//swprintf_s(szBuffer, L"angle : %f", Math::RadianToDegree(angle));
		//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

		if (detectFlag)
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::TRACE);
		}
	}
}

void MonsterIdleState::Render()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		Vec2 monsterPos = monster->GetPos();

		MonsterInfo info = monster->GetMonsterInfo();

		// 벡터를 회전시킨 후 거리를 곱해서 점 위치를 구한다
		// 좌/우측에 따라 별도로 처리해야 하므로 방향에 따른 벡터 구하기

		DIR dir = monster->GetDir();
		Vec2 dirVec = {};
		switch (dir)
		{
		case DIR::LEFT:
			dirVec = Vec2(-1, 0);
			break;

		case DIR::RIGHT:
			dirVec = Vec2(1, 0);
			break;
		}

		//Pen pen(BACK_BUF_DC, PEN_TYPE::GREEN);
		//dirVec = Math::RotateVector(dirVec, 20.f);
		//dirVec *= info.mRecog;
		//dirVec.x  = (DIR::LEFT == dir ? -1 : 1);
		//MoveToEx(BACK_BUF_DC, monsterPos.x, monsterPos.y, NULL);
		//LineTo(BACK_BUF_DC, dirVec.x, dirVec.y);
	}
}

void MonsterIdleState::Enter()
{
}

void MonsterIdleState::Exit()
{
}
