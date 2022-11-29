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
		MonsterInfo info = monster->GetMonsterInfo();

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = monster->GetPos();
		// 방향 전환할 때 애니메이션 변환
		// 방향 전환은? 플레이어 위치 - 내 위치 의 부호에 따라 변환

		Vec2 dirVec = monsterPos - playerPos;
		DIR dir = monster->GetDir();

		if ( 0 > dirVec.x )
		{
			monsterPos.x += info.mSpeed * DT;
			monster->SetPrevDir(dir);
			monster->SetDir(DIR::RIGHT);
		}

		else
		{
			monsterPos.x -= info.mSpeed * DT;
			monster->SetPrevDir(dir);
			monster->SetDir(DIR::LEFT);
		}

		monster->SetPos(monsterPos);

		// 플레이어가 몬스터가 바라보는 방향의 특정 거리, 특정 각도 미만으로 들어왔을 때
		// Attack State로 변경

		bool detectFlag = PlayerCheck(10.f, info.mAttRange);
		
		if (detectFlag)
		{
			EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::ATTACK);
		}









		dir = monster->GetDir();

		if (monster->GetPrevDir() != dir)
		{
			const std::wstring& animName = monster->GetMoveAnimName();
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
		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		Vec2 monsterPos = RENDER_POS(monster->GetPos());

		MonsterInfo info = monster->GetMonsterInfo();

		// 벡터를 회전시킨 후 거리를 곱해서 점 위치를 구한다
		// 좌/우측에 따라 별도로 처리해야 하므로 방향에 따른 벡터 구하기

		DIR dir = monster->GetDir();
		Vec2 dirVec = {};
		Vec2 dirAngleVec = {};
		switch (dir)
		{
		case DIR::LEFT:
			dirVec = Vec2(-1, 0);
			dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(10.f));
			break;

		case DIR::RIGHT:
			dirVec = Vec2(1, 0);
			dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(-10.f));
			break;
	}

		Pen pen(BACK_BUF_DC, PEN_TYPE::BLUE);
		dirAngleVec *= info.mAttRange;
		dirAngleVec = RENDER_POS(dirAngleVec + monster->GetPos());

		dirVec *= info.mAttRange;
		dirVec = RENDER_POS(dirVec + monster->GetPos());

		float offset = 30.f;

		MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
		LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

		MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
		LineTo(BACK_BUF_DC, (int)dirVec.x, (int)(dirVec.y - offset));
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
