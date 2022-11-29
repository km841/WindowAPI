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
	, mMaxStayTime(1.5f)
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
		
		// �÷��̾ �νĹ��� ���̰�,
		// ������ n�� �̸��̶�� �ν�

		MonsterInfo info = monster->GetMonsterInfo();

		// n�� �� �̰� �˻�
		bool detectFlag = PlayerCheck(10.f, info.mRecog);

		if (mMaxStayTime > mStayTime)
		{
			mStayTime += DT;
		}

		else
		{
			if (detectFlag)
			{
				EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::TRACE);
			}

			else
			{
				EventRegisteror::GetInstance().ChangeMonsterState(ownerAI, MONSTER_STATE::PATROL);
			}
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
		Vec2 monsterPos = RENDER_POS(monster->GetPos());

		MonsterInfo info = monster->GetMonsterInfo();

		// ���͸� ȸ����Ų �� �Ÿ��� ���ؼ� �� ��ġ�� ���Ѵ�
		// ��/������ ���� ������ ó���ؾ� �ϹǷ� ���⿡ ���� ���� ���ϱ�

		DIR dir = monster->GetDir();
		Vec2 dirVec = {};
		Vec2 dirAngleVec = {};
		switch (dir)
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

		Pen pen(BACK_BUF_DC, PEN_TYPE::RED);
		dirAngleVec *= info.mRecog;
		dirAngleVec = RENDER_POS(dirAngleVec + monster->GetPos());

		dirVec *= info.mRecog;
		dirVec = RENDER_POS(dirVec + monster->GetPos());

		float offset = 30.f;
		MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
		LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

		MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
		LineTo(BACK_BUF_DC, (int)dirVec.x, (int)(dirVec.y - offset));
	}
}

void MonsterIdleState::Enter()
{
}

void MonsterIdleState::Exit()
{
	mStayTime = 0.f;
}