#include "pch.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "TimeMgr.h"

MonsterTraceState::MonsterTraceState()
	: MonsterState(MONSTER_STATE::TRACE)
{

}

MonsterTraceState::~MonsterTraceState()
{
}

void MonsterTraceState::Update()
{
	// ���� ������ �i�ƿ�
	// Trace <-> Attack

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		AI* ai = GetOwnerAI();
		Monster* monster = ai->GetOwnerMonster();
		monster->Trace();

		//�÷��̾ ���Ͱ� �ٶ󺸴� ������ Ư�� �Ÿ�, Ư�� ���� �̸����� ������ ��
		//Attack State�� ����
		if (monster->DetectIntoAttRange())
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::ATTACK);
		}

		// Trace <-> Attack
		// Attack State�� �Ǵ� ����
		// -> Trace �� �÷��̾ ���ݹ��� ������ ������ ��
		// -> ���� ���°� Left�� ��� Left���� �ִϸ��̼�, Right�� ��� Right���� �ִϸ��̼�
		// -> �׷��� Attack State�� ���ڸ��� ���缭 �������� ���� ������ �����ϰ� �ణ�� �ĵ����� �Ŀ� �ٽ� Trace���·� ����

	}
}
		
void MonsterTraceState::Render()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Monster* monster = GetOwnerAI()->GetOwnerMonster();
		monster->AttRangeLineRender(PEN_TYPE::BLUE);
	}
}

void MonsterTraceState::Enter()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetMoveAnimName();
	DIR dir = monster->GetDir();
	switch (dir)
	{
	case DIR::LEFT:
		monster->GetAnimator()->SelectAnimation(animName + L"Left", true);
		break;
	case DIR::RIGHT:
		monster->GetAnimator()->SelectAnimation(animName + L"Right", true);
		break;
	}
}

void MonsterTraceState::Exit()
{

}
