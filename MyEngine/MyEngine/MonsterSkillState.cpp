#include "pch.h"
#include "MonsterSkillState.h"
#include "Monster.h"
#include "AI.h"
#include "Animator.h"
#include "Animation.h"
#include "EventRegisteror.h"

MonsterSkillState::MonsterSkillState()
	:MonsterState(MONSTER_STATE::SKILL)
{

}

MonsterSkillState::~MonsterSkillState()
{
}

void MonsterSkillState::Update()
{
	AI* ai = GetOwnerAI();
	Monster* monster = ai->GetOwnerMonster();
	if (!monster->Skill())
	{
		EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::ATTACK_AFTER);
	}
}

void MonsterSkillState::Render()
{
}

void MonsterSkillState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetSkillAnimName();
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

void MonsterSkillState::Exit()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	monster->GetAnimator()->GetCurAnimation()->Reset();
}
