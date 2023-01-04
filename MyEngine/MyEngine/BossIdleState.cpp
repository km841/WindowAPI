#include "pch.h"
#include "BossIdleState.h"
#include "AI.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"
#include "Animator.h"
#include "Animation.h"
#include "KeyMgr.h"
#include "BossMonster.h"

BossIdleState::BossIdleState()
	: MonsterState(MONSTER_STATE::BOSS_IDLE)
{

}

BossIdleState::~BossIdleState()
{
}

void BossIdleState::Update()
{
	AI* ai = GetOwnerAI();
	if (nullptr != ai)
	{
		Monster* bossMonster = ai->GetOwnerMonster();
		if (nullptr != bossMonster)
		{
			// 키입력에 따라 스킬로 넘어감
			// 1번 누르면 몬스터에게 enum값으로 해당 스킬이 정해짐
			// 스킬로 넘어가면 해당 스킬이 사용됨

			if (IS_JUST_PRESSED(KEY::ONE))
			{
				static_cast<BossMonster*>(bossMonster)->SetCurSkill(BOSS_SKILL::SKILL_1);
				EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::BOSS_SKILL);
			}

			if (IS_JUST_PRESSED(KEY::TWO))
			{
				static_cast<BossMonster*>(bossMonster)->SetCurSkill(BOSS_SKILL::SKILL_2);
				EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::BOSS_SKILL);
			}

			if (IS_JUST_PRESSED(KEY::THREE))
			{
				static_cast<BossMonster*>(bossMonster)->SetCurSkill(BOSS_SKILL::SKILL_3);
				EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::BOSS_SKILL);
			}
		}
	}


	
}

void BossIdleState::Render()
{
}

void BossIdleState::Enter()
{
	AI* ai = GetOwnerAI();
	if (nullptr != ai)
	{
		Monster* bossMonster = ai->GetOwnerMonster();
		if (nullptr != bossMonster)
		{
			bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetIdleAnimName(), true);
		}
	}
}

void BossIdleState::Exit()
{
	AI* ai = GetOwnerAI();
	if (nullptr != ai)
	{
		Monster* bossMonster = ai->GetOwnerMonster();
		if (nullptr != bossMonster)
		{
			bossMonster->GetAnimator()->GetCurAnimation()->Reset();
		}
	}
}
