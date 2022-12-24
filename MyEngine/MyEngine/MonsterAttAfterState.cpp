#include "pch.h"
#include "MonsterAttAfterState.h"
#include "Monster.h"
#include "AI.h"
#include "Animator.h"
#include "Animation.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"

MonsterAttAfterState::MonsterAttAfterState()
	:MonsterState(MONSTER_STATE::ATTACK_AFTER)
{

}

MonsterAttAfterState::~MonsterAttAfterState()
{
}

void MonsterAttAfterState::Update()
{
	AI* ai = GetOwnerAI();
	Monster* monster = ai->GetOwnerMonster();

	MonsterInfo& info = monster->GetMonsterInfo();
	if (info.mAttDelay < info.mCurDelay)
	{
		info.mCurDelay = 0.f;

		if (nullptr != ai->FindState(MONSTER_STATE::TRACE))
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::TRACE);
		else
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::IDLE);
	}

	else
	{
		info.mCurDelay += DT;
	}

}

void MonsterAttAfterState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetAttAfterAnimName();
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

void MonsterAttAfterState::Exit()
{
}
