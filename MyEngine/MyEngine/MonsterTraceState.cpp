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
	// �÷��̾� ��ġ�� �����ϸ� �����δ�.
	// ������ �� �ִϸ��̼��� ��������� ��
	// 1. ���°� �ٲ���� ��
	// 2. ������ �ٲ���� ��
	// �� �� ��Ȳ�� ��� üũ�Ұ��ΰ��� ���� �ٽ�

	int a = 0;
}

void MonsterTraceState::Enter()
{

}

void MonsterTraceState::Exit()
{

}
