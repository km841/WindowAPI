#pragma once
#include "Monster.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "MonsterPatrolState.h"
#include "MonsterAttState.h"
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
		case MONSTER_TYPE::MELEE:
		{
			monster = new T;
			monster->SetPos(_pos);
			monster->SetGround(false);

			info.mHP = 100;
			info.mSpeed = 50.f;
			info.mRecog = 300.f;
			info.mAttRange = 150.f;
			monster->SetMonsterInfo(info);

			AI* ai = new AI;
			ai->SetOwnerMonster(monster);
			
			monster->SetAI(ai);
			
			MonsterIdleState* idleState = new MonsterIdleState;
			idleState->SetOwnerAI(ai);

			MonsterTraceState* traceState = new MonsterTraceState;
			traceState->SetOwnerAI(ai);

			MonsterPatrolState* patrolState = new MonsterPatrolState;
			patrolState->SetOwnerAI(ai);

			MonsterAttState* attState = new MonsterAttState;
			attState->SetOwnerAI(ai);

			ai->AddState(idleState);
			ai->AddState(traceState);
			ai->AddState(patrolState);
			ai->AddState(attState);

			ai->ChangeState(MONSTER_STATE::PATROL);
		}
			break;

		}


		return monster;
	}


private:

};

