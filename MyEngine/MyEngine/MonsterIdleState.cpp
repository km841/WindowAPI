#include "pch.h"
#include "MonsterIdleState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"

MonsterIdleState::MonsterIdleState()
	: MonsterState(MONSTER_STATE::IDLE)
	, mMaxStayTime(.5f)
	, mStayTime(0.f)
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

		DIR dir = monster->GetDir();
		switch (dir)
		{
		case DIR::LEFT:
			monster->GetAnimator()->SelectAnimation(monster->GetIdleAnimName() + L"Left", true);
			break;
		case DIR::RIGHT:
			monster->GetAnimator()->SelectAnimation(monster->GetIdleAnimName() + L"Right", true);
			break;
		}
		
		// 플레이어가 인식범위 안이고,
		// 각도가 n도 미만이라면 인식

		MonsterInfo info = monster->GetMonsterInfo();

		// n초 후 이걸 검사
		// 플레이어를 체크하는 로직.. 몬스터 타입별로?
		// 몬스터에서 가상함수로 구현?
		// 공중은 정면과 아래 각도를 봄
		// 지상은 지금과 동일

		bool detectFlag = monster->DetectPlayer();

		if (mMaxStayTime > mStayTime)
		{
			mStayTime += DT;
		}

		else
		{
			if (detectFlag)
			{
				if (nullptr != ownerAI->FindState(MONSTER_STATE::TRACE))
				{
					if (nullptr != ownerAI->FindState(MONSTER_STATE::TRACE))
						EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::TRACE);
					else
						EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::ATTACK);
				}
			}

			else
			{
				if (nullptr != ownerAI->FindState(MONSTER_STATE::PATROL))
				{
					EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::PATROL);
				}
				
			}
		}

	}
}

void MonsterIdleState::Render()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Monster* monster = GetOwnerAI()->GetOwnerMonster();
		monster->RecogLineRender(PEN_TYPE::RED);
	}
}

void MonsterIdleState::Enter()
{
}

void MonsterIdleState::Exit()
{
	mStayTime = 0.f;
}