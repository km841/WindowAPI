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
		MonsterInfo info = monster->GetMonsterInfo();

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = monster->GetPos();
		// ���� ��ȯ�� �� �ִϸ��̼� ��ȯ
		// ���� ��ȯ��? �÷��̾� ��ġ - �� ��ġ �� ��ȣ�� ���� ��ȯ

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

		// �÷��̾ ���Ͱ� �ٶ󺸴� ������ Ư�� �Ÿ�, Ư�� ���� �̸����� ������ ��
		// Attack State�� ����

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
		AI* ownerAI = GetOwnerAI();
		Monster* monster = ownerAI->GetOwnerMonster();
		Vec2 monsterPos = RENDER_POS(monster->GetPos());

		MonsterInfo info = monster->GetMonsterInfo();

		// ���͸� ȸ����Ų �� �Ÿ��� ���ؼ� �� ��ġ�� ���Ѵ�
		// ��/������ ���� ������ ó���ؾ� �ϹǷ� ���⿡ ���� ���� ���ϱ�

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
