#include "pch.h"
#include "MonsterAttState.h"
#include "Monster.h"
#include "AI.h"
#include "Animator.h"
#include "Player.h"
#include "Animation.h"
#include "EventRegisteror.h"

MonsterAttState::MonsterAttState()
	:MonsterState(MONSTER_STATE::ATTACK)
{

}

MonsterAttState::~MonsterAttState()
{

}

void MonsterAttState::Update()
{
	AI* ai = GetOwnerAI();
	Monster* monster = ai->GetOwnerMonster();

	// 이 조건문 자체를 가상함수로 만들어버리는거임
	// 지금 이건 해골전사에서 그대로 쓰면되고
	// 박쥐같은 원거리 공격유닛은.. 만든 오브젝트의 수명을 추적해서 소멸되면 그때 Trace로
	// 투사체가 하나던 여러개던 동일한 방법으로 처리하는 방법
	// 그냥 for문돌면서 내부에 오브젝트가 어떤상태인지 점검하고 전부 소멸됐으면 true

	// 공격이 끝났는지를 알리는 몬스터쪽에서 제공하는 가상함수
	// monster->AttackEnter에서는 몬스터가 몇 프레임때 무슨 일을 하는지 서술
	// monster->AttackExit에서는 몬스터의 
	// 공격시간이 긴 몬스터의 경우는?
	// 애니메이션이 2회 이상 진행되어야 하는 경우?
	// bool을 반환하는 Attack이라는 함수를 그냥 두고 그 안에서 끝났는지 유무를 검사한다.
	// 여기서는 그 유무에 따른 처리를 해준다.

	if (!monster->Attack())
	{
		EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::TRACE);
	}

	// reset 하고 trace로
	
	// 이 때 몬스터 Effect의 충돌체가 Off됨
	// 몬스터에 따른 각기 다른 처리
	// 이 처리를 가상함수로 만들면? 제약사항(모든 처리가 공격애니메이션 안에서 다 처리되어야 함)
	// 아니면 bool 함수를만들고 그 함수가 true가 되면 그 때 상태 변경
	// 1. 해골전사의 경우: 공격 애니메이션 동안 충돌체를 On 시킨다.
	
	// 몬스터도 이펙트를 가지게 하고,
	// 몬스터가 AttState일 때 특정 프레임에 충돌체를 Enable하여 플레이어 충돌체와 충돌하도록 함
	// 그럼 원거리 몬스터는 어떻게 처리?
	// 원거리 몬스터는 특정 프레임에 오브젝트를 생성시킴
	// 생성시킨 오브젝트는 목적지를 향해 날아감
	// Effect는 그 오브젝트 자체를 의미하며, 오브젝트가 여러개의 경우는? 
	// AttState에서 그걸 처리함
	// 애니메이션이 지속되는 동안 그 탄알에 대한 애니메이션도 발생되어야 함
	// 그러면... std::vector로 가지고있어야한다
	// Effect의 Update와 Render에서 탄알에 대한 Update와 Render를 진행해주어야 함
	// 게임오브젝트의 mDead 변수 상태를 활용해서 모든 상태 체크
}

void MonsterAttState::Enter()
{
	// 213 x 144
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	const std::wstring& animName = monster->GetAttAnimName();
	DIR dir = monster->GetDir();
	switch (dir)
	{
	case DIR::LEFT:
		monster->GetAnimator()->SelectAnimation(animName + L"Left", false);
		break;
	case DIR::RIGHT:
		monster->GetAnimator()->SelectAnimation(animName + L"Right", false);
		break;
	}

	// 특정 애니메이션 프레임에 충돌체가 켜져야 함

	// 특정 프레임일 때 이게 실행돼도 되잖
	
	// 공격 개시- 가상함수로 처리
	
}

void MonsterAttState::Exit()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	monster->GetAnimator()->GetCurAnimation()->Reset();
}
