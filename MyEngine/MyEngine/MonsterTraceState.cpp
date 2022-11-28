#include "pch.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"

MonsterTraceState::MonsterTraceState()
	: MonsterState(MONSTER_STATE::TRACE)
{

}

MonsterTraceState::~MonsterTraceState()
{
}

void MonsterTraceState::Update()
{
	// ���� ������ �i�ƿ�
	// Trace <-> Attack

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		AI* ai = GetOwnerAI();
		Monster* monster = ai->GetOwnerMonster();
		MonsterInfo info = monster->GetMonsterInfo();

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = monster->GetPos();
		// ���� ��ȯ�� �� �ִϸ��̼� ��ȯ
		// ���� ��ȯ��? �÷��̾� ��ġ - �� ��ġ �� ��ȣ�� ���� ��ȯ

		Vec2 dirVec = monsterPos - playerPos;
		DIR dir = monster->GetDir();

		if (dirVec.x < 0)
		{
			monsterPos.x += info.mSpeed * DT;
			monster->SetPrevDir(dir);
			monster->SetDir(DIR::RIGHT);
		}

		else
		{
			monsterPos.x -= info.mSpeed * DT;
			monster->SetPrevDir(dir);
			monster->SetDir(DIR::LEFT);
		}

		monster->SetPos(monsterPos);
		dir = monster->GetDir();

		if (monster->GetPrevDir() != dir)
		{
			const std::wstring& animName = monster->GetWalkAnimName();
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

}

void MonsterTraceState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetWalkAnimName();
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

void MonsterTraceState::Exit()
{

}
