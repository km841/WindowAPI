#include "pch.h"
#include "BossSkillState.h"
#include "AI.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"
#include "Animator.h"
#include "Animation.h"
#include "KeyMgr.h"
#include "BossMonster.h"

BossSkillState::BossSkillState()
	:MonsterState(MONSTER_STATE::BOSS_SKILL)
{
}

BossSkillState::~BossSkillState()
{
}

void BossSkillState::Update()
{
	AI* ai = GetOwnerAI();
	if (nullptr != ai)
	{

		Monster* bossMonster = ai->GetOwnerMonster();
		if (!bossMonster->Skill())
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::BOSS_IDLE);
		}
	}

}

void BossSkillState::Render()
{
}

void BossSkillState::Enter()
{
	AI* ai = GetOwnerAI();
	if (nullptr != ai)
	{
		Monster* bossMonster = ai->GetOwnerMonster();
		if (nullptr != bossMonster)
		{
			bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetSkillAnimName(), false);
		}
	}
}

void BossSkillState::Exit()
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
