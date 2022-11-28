#include "pch.h"
#include "MonsterTraceState.h"

MonsterTraceState::MonsterTraceState()
	: MonsterState(MONSTER_STATE::TRACE)
{

}

MonsterTraceState::~MonsterTraceState()
{
}

void MonsterTraceState::Update()
{
	// 플레이어 위치를 추적하며 움직인다.
	// 움직일 때 애니메이션을 변경해줘야 함
	// 1. 상태가 바뀌었을 때
	// 2. 방향이 바뀌었을 때
	// 이 두 상황을 어떻게 체크할것인가가 가장 핵심

	int a = 0;
}

void MonsterTraceState::Enter()
{

}

void MonsterTraceState::Exit()
{

}
