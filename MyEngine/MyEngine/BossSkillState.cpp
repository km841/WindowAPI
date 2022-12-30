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
	, mStartFlag(false)
{
}

BossSkillState::~BossSkillState()
{
}

void BossSkillState::Update()
{
	AI* ai = GetOwnerAI();
	Monster* bossMonster = ai->GetOwnerMonster();

	MonsterInfo& monInfo = bossMonster->GetMonsterInfo();
	int fixFrame = bossMonster->GetAttFixFrame();

	if (false == monInfo.mAttFinFlag)
	{
		if (0 != fixFrame)
		{
			int frame = bossMonster->GetAnimator()->GetCurAnimation()->GetCurFrame();
			if (fixFrame == frame)
			{
				bossMonster->GetAnimator()->GetCurAnimation()->SetCurFrame(fixFrame);
				bossMonster->GetAnimator()->GetCurAnimation()->SetFrameFix(true);

				mStartFlag = true;
			}
		}

		else
		{
			mStartFlag = true;
		}

		if (true == mStartFlag)
		{
			if (!bossMonster->Skill())
			{
				if (0 != fixFrame)
					bossMonster->GetAnimator()->GetCurAnimation()->SetFrameFix(false);

				monInfo.mAttFinFlag = true;
			}
		}

	}

	else
	{
		if (bossMonster->GetAnimator()->GetCurAnimation()->IsFinished())
		{
			mStartFlag = false;
			monInfo.mAttFinFlag = false;
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
		BossMonster* bossMonster = static_cast<BossMonster*>(ai->GetOwnerMonster());
		if (nullptr != bossMonster)
		{
			switch (bossMonster->GetCurSkill())
			{
			case BOSS_SKILL::SKILL_1:
				bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetSkill01AnimName(), false);
				break;

			case BOSS_SKILL::SKILL_2:
				bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetSkill02AnimName(), false);
				break;

			case BOSS_SKILL::SKILL_3:
				bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetSkill03AnimName(), false);
				break;
			}

			if (nullptr == bossMonster->GetAnimator()->GetCurAnimation())
			{
				bossMonster->GetAnimator()->SelectAnimation(bossMonster->GetIdleAnimName(), false);
			}
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
