#include "pch.h"
#include "AI.h"
#include "MonsterState.h"

void AI::Update()
{
	if (nullptr != mCurState)
		mCurState->Update();
}

void AI::Render()
{
	if (nullptr != mCurState)
		mCurState->Render();
}

void AI::AddState(MonsterState* _state)
{
	mStateMap.insert(std::make_pair(_state->GetMonsterState(), _state));
}

MonsterState* AI::FindState(MONSTER_STATE _eState)
{
	std::map<MONSTER_STATE, MonsterState*>::iterator iter = mStateMap.find(_eState);
	if (iter != mStateMap.end())
	{
		return iter->second;
	}

	return nullptr;
}


void AI::ChangeState(MONSTER_STATE _eState)
{
	MonsterState* state = FindState(_eState);
	if (nullptr == state)
		assert(nullptr);

	if (nullptr != mCurState)
		mCurState->Exit();

	mCurState = state;
	mCurState->Enter();
}
