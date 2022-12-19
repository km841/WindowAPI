#include "pch.h"
#include "MonsterDeadState.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "Animation.h"
#include "EventRegisteror.h"

MonsterDeadState::MonsterDeadState()
	: MonsterState(MONSTER_STATE::DEAD)
{
}

MonsterDeadState::~MonsterDeadState()
{
}

void MonsterDeadState::Update()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	if (monster->GetAnimator()->GetCurAnimation()->IsFinished())
	{
		//EventRegisteror::GetInstance().DeleteObject(monster);
		monster->SetObjState(OBJECT_STATE::DEAD);
	}
}

void MonsterDeadState::Render()
{
}

void MonsterDeadState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	monster->GetAnimator()->SelectAnimation(L"MonsterDeadAnim", false);
}

void MonsterDeadState::Exit()
{
}
