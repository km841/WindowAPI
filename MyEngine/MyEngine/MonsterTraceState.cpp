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
		dirVec.Norm();
		DIR dir = monster->GetDir();

		switch (monster->GetMonsterType())
		{
		case MONSTER_TYPE::GROUND_MELEE:
		{
			monster->SetPrevDir(dir);

			if (0 > dirVec.x)
			{
				monsterPos.x += info.mSpeed * DT;
				monster->SetDir(DIR::RIGHT);
			}

			else
			{
				monsterPos.x -= info.mSpeed * DT;
				monster->SetDir(DIR::LEFT);
			}
		}
			break;

		case MONSTER_TYPE::FLY_RANGE:
		{
			monster->SetPrevDir(dir);

			if (abs(playerPos.x - monsterPos.x) < info.mAttRange &&
				(playerPos - monsterPos).Len() > info.mAttRange)
			{
				if (0 > dirVec.x)
				{
					monster->SetDir(DIR::RIGHT);
				}

				else
				{
					monster->SetDir(DIR::LEFT);
				}
				
				monsterPos -= dirVec * info.mSpeed * DT;
			}

			else
			{
				if (0 > dirVec.x)
				{
					monsterPos.x += info.mSpeed * DT;
					monster->SetDir(DIR::RIGHT);
				}

				else
				{
					monsterPos.x -= info.mSpeed * DT;
					monster->SetDir(DIR::LEFT);
				}
			}
		}
			break;
		}



		monster->SetPos(monsterPos);

		 //�÷��̾ ���Ͱ� �ٶ󺸴� ������ Ư�� �Ÿ�, Ư�� ���� �̸����� ������ ��
		 //Attack State�� ����

		bool detectFlag = monster->DetectIntoAttRange();
		
		if (detectFlag)
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::ATTACK);
		}

		dir = monster->GetDir();

		if (monster->GetPrevDir() != dir)
		{
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
		

		// Trace <-> Attack
		// Attack State�� �Ǵ� ����
		// -> Trace �� �÷��̾ ���ݹ��� ������ ������ ��
		// -> ���� ���°� Left�� ��� Left���� �ִϸ��̼�, Right�� ��� Right���� �ִϸ��̼�
		// -> �׷��� Attack State�� ���ڸ��� ���缭 �������� ���� ������ �����ϰ� �ణ�� �ĵ����� �Ŀ� �ٽ� Trace���·� ����



			}

}
		
void MonsterTraceState::Render()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Monster* monster = GetOwnerAI()->GetOwnerMonster();
		monster->AttRangeLineRender(PEN_TYPE::BLUE);
	}
}

void MonsterTraceState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetMoveAnimName();
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
