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
			// TRACE의 ENTER에선 초기에 몇 초간 대기
			// IDLE로 갔다가 TRACE로 가야 함
			// IDLE로 갔다가 n초 후 계속 감지되어 있으면 TRACE, 감지가 해제되면 다시 PATROL
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

		// 벡터를 회전시킨 후 거리를 곱해서 점 위치를 구한다
		// 좌/우측에 따라 별도로 처리해야 하므로 방향에 따른 벡터 구하기

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