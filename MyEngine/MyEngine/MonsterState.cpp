#include "pch.h"
#include "MonsterState.h"
#include "Player.h"
#include "Monster.h"
#include "AI.h"

MonsterState::MonsterState(MONSTER_STATE _eState)
	: mState(_eState)
{
}

bool MonsterState::PlayerCheck(MONSTER_TYPE _type, float _angle, float _range)
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		Vec2 monsterPos = monster->GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = monster->GetMonsterInfo();

		DIR dir = monster->GetDir();
		DIR prevDir = monster->GetPrevDir();


		switch (dir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - _range, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < _angle)
				{
					return true;
				}
			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + _range, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < _angle)
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
