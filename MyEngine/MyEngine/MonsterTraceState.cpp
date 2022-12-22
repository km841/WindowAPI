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
	// 죽을 때까지 쫒아옴
	// Trace <-> Attack

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		AI* ai = GetOwnerAI();
		Monster* monster = ai->GetOwnerMonster();
		monster->Trace();

		//플레이어가 몬스터가 바라보는 방향의 특정 거리, 특정 각도 미만으로 들어왔을 때
		//Attack State로 변경
		if (monster->DetectIntoAttRange())
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::ATTACK);
		}

		// Trace <-> Attack
		// Attack State가 되는 조건
		// -> Trace 중 플레이어가 공격범위 안으로 들어왔을 때
		// -> 현재 상태가 Left인 경우 Left공격 애니메이션, Right인 경우 Right공격 애니메이션
		// -> 그러면 Attack State는 그자리에 멈춰서 프레임이 끝날 때까지 실행하고 약간의 후딜레이 후에 다시 Trace상태로 변경

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
