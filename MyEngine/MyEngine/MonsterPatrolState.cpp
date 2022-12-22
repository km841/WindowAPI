#include "pch.h"
#include "MonsterPatrolState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"
#include "RigidBody.h"


MonsterPatrolState::MonsterPatrolState()
	:MonsterState(MONSTER_STATE::PATROL)
	, mDelayMaxTime(3.0f)
	, mDelayTime(0.f)
{
	
}

MonsterPatrolState::~MonsterPatrolState()
{
}

void MonsterPatrolState::Update()
{
	if (mDelayMaxTime > mDelayTime)
	{
		mDelayTime += DT;

		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		DIR dir = monster->GetDir();
		MonsterInfo info = monster->GetMonsterInfo();
		Vec2 monsterPos = monster->GetPos();

		switch (dir)
		{
		case DIR::LEFT:
			monsterPos.x -= info.mSpeed * DT;
			break;
		case DIR::RIGHT:
			monsterPos.x += info.mSpeed * DT;
			break;
		}

		monster->SetPos(monsterPos);

		bool detectFlag = monster->DetectPlayer();
		if (detectFlag)
		{
			// TRACE�� ENTER���� �ʱ⿡ �� �ʰ� ���
			// IDLE�� ���ٰ� TRACE�� ���� ��
			// IDLE�� ���ٰ� n�� �� ��� �����Ǿ� ������ TRACE, ������ �����Ǹ� �ٽ� PATROL
			//

			EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::IDLE);
		}


	}

	else
	{
		mDelayTime = 0.f;
		GetOwnerAI()->GetOwnerMonster()->ChangeDir();

		Monster* monster = GetOwnerAI()->GetOwnerMonster();
		DIR dir = monster->GetDir();

		const std::wstring& animName = monster->GetMoveAnimName();
		switch (dir)
		{
		case DIR::LEFT:
			monster->GetAnimator()->SelectAnimation(animName + L"Left", true);
			break;
		case DIR::RIGHT:
			monster->GetAnimator()->SelectAnimation(animName + L"Right", true);
			break;
		}
	}
}

void MonsterPatrolState::Render()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Monster* monster = GetOwnerAI()->GetOwnerMonster();
		monster->RecogLineRender(PEN_TYPE::GREEN);
	}
}

void MonsterPatrolState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetPatrolStateAnimName();
	DIR dir = monster->GetDir();
	switch (dir)
	{
	case DIR::LEFT:
		monster->GetAnimator()->SelectAnimation(animName + L"Left", true);
		break;
	case DIR::RIGHT:
		monster->GetAnimator()->SelectAnimation(animName + L"Right", true);
		break;
	}
}

void MonsterPatrolState::Exit()
{
}