#pragma once
#include "Monster.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "MonsterPatrolState.h"
#include "MonsterAttState.h"
#include "MonsterDeadState.h"
#include "MonsterAttAfterState.h"
#include "MonsterSkillState.h"
#include "BossIdleState.h"
#include "BossSkillState.h"
#include "AI.h"

class MonsterFactory
{
public:

	template<typename T>
	static Monster* CreateMonster(MONSTER_TYPE _type, Vec2 _pos)
	{
		MonsterInfo info = {};
		Monster* monster = nullptr;
		
		switch (_type)
		{
		case MONSTER_TYPE::GROUND_MELEE:
		{
			monster = new T;
			monster->SetPos(_pos);
			monster->SetGround(false);

			info.mAtt = 5;
			info.mMaxHP = 100;
			info.mSpeed = 100.f;
			info.mRecog = 300.f;
			info.mAttRange = 150.f;
			info.mAttDelay = 2.f;
			info.mCurDelay = 0.f;

			monster->SetMonsterInfo(info);
			
			AI* ai = new AI;
			ai->SetOwnerMonster(monster);
			monster->SetAI(ai);
		
			ai->AddStates(
				new MonsterIdleState,
				new MonsterTraceState,
				new MonsterPatrolState,
				new MonsterDeadState,
				new MonsterAttState,
				new MonsterAttAfterState
			);

			ai->ChangeState(MONSTER_STATE::IDLE);
		}
			break;

		case MONSTER_TYPE::GROUND_SKILL:
		{
			monster = new T;
			monster->SetPos(_pos);
			monster->SetGround(false);

			info.mAtt = 5;
			info.mMaxHP = 100;
			info.mSpeed = 50.f;
			info.mRecog = 300.f;
			info.mAttRange = 150.f;
			info.mAttDelay = 2.f;
			info.mCurDelay = 0.f;

			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);
			monster->SetAI(ai);

			ai->AddStates(
				new MonsterIdleState,
				new MonsterTraceState,
				new MonsterPatrolState,
				new MonsterDeadState,
				new MonsterAttState,
				new MonsterAttAfterState,
				new MonsterSkillState
			);

			ai->ChangeState(MONSTER_STATE::IDLE);
		}
		break;

		case MONSTER_TYPE::GROUND_CHARGE:
		{
			monster = new T;
			monster->SetPos(_pos);
			monster->SetGround(false);

			info.mAtt = 5;
			info.mMaxHP = 100;
			info.mSpeed = 50.f;
			info.mRecog = 300.f;
			info.mAttRange = 150.f;
			info.mAttDelay = 2.f;
			info.mCurDelay = 0.f;

			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);

			monster->SetAI(ai);
			ai->AddStates(
				new MonsterIdleState,
				new MonsterDeadState,
				new MonsterAttState,
				new MonsterAttAfterState
			);

			ai->ChangeState(MONSTER_STATE::IDLE);
		}
			break;

		case MONSTER_TYPE::GROUND_OP_CHARGE:
		{
			monster = new T;
			monster->SetPos(_pos);
			monster->SetGround(false);

			info.mAtt = 5;
			info.mMaxHP = 100;
			info.mSpeed = 50.f;
			info.mRecog = 300.f;
			info.mAttRange = 150.f;
			info.mAttDelay = 2.f;
			info.mCurDelay = 0.f;

			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);

			monster->SetAI(ai);
			ai->AddStates(
				new MonsterIdleState,
				new MonsterDeadState,
				new MonsterTraceState,
				new MonsterAttState,
				new MonsterAttAfterState
			);

			ai->ChangeState(MONSTER_STATE::IDLE);
		}
		break;

			
			


		case MONSTER_TYPE::FLY_RANGE:
		{
			monster = new T;
			monster->SetPos(_pos);
			//monster->SetGround(true);

			info.mAtt = 1;
			info.mMaxHP = 100;
			info.mSpeed = 100.f;
			info.mRecog = 400.f;
			info.mAttRange = 300.f;
			info.mAttDelay = 2.f;
			info.mCurDelay = 0.f;

			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);

			monster->SetAI(ai);

			ai->AddStates(
				new MonsterIdleState,
				new MonsterTraceState,
				new MonsterPatrolState,
				new MonsterDeadState,
				new MonsterAttState,
				new MonsterAttAfterState
			);

			ai->ChangeState(MONSTER_STATE::IDLE);
		}
			break;

		case MONSTER_TYPE::BOSS_BELIAL:
		{
			monster = new T;
			monster->SetPos(_pos);

			info.mAtt = 1;
			info.mMaxHP = 1500;
			info.mCurHP = 1500;

			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);
			monster->SetAI(ai);

			ai->AddStates(
				new BossIdleState,
				new BossSkillState
			);

			ai->ChangeState(MONSTER_STATE::BOSS_IDLE);
		}
		break;

		}


		return monster;
	}


private:

};

