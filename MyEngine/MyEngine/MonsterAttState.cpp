#include "pch.h"
#include "MonsterAttState.h"
#include "Monster.h"
#include "AI.h"
#include "Animator.h"
#include "Player.h"
#include "Animation.h"
#include "EventRegisteror.h"

MonsterAttState::MonsterAttState()
	:MonsterState(MONSTER_STATE::ATTACK)
{

}

MonsterAttState::~MonsterAttState()
{

}

void MonsterAttState::Update()
{
	AI* ai = GetOwnerAI();
	Monster* monster = ai->GetOwnerMonster();

	if (monster->GetAnimator()->GetCurAnimation()->IsFinished())
	{
		// reset ÇÏ°í trace·Î
		EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::TRACE);
		monster->GetAnimator()->GetCurAnimation()->Reset();
	}
}

void MonsterAttState::Enter()
{
	// 213 x 144
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetAttAnimName();
	DIR dir = monster->GetDir();
	switch (dir)
	{
	case DIR::LEFT:
		monster->GetAnimator()->SelectAnimation(animName + L"Left", false);
		break;
	case DIR::RIGHT:
		monster->GetAnimator()->SelectAnimation(animName + L"Right", false);
		break;
	}
	
}

void MonsterAttState::Exit()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();

}
