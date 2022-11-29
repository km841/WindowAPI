#include "pch.h"
#include "MonsterPatrolState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"


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

		bool detectFlag = PlayerCheck(10.f, info.mRecog);
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

		Pen pen(BACK_BUF_DC, PEN_TYPE::GREEN);
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

void MonsterPatrolState::Enter()
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

void MonsterPatrolState::Exit()
{
}