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

	// �� ���ǹ� ��ü�� �����Լ��� ���������°���
	// ���� �̰� �ذ����翡�� �״�� ����ǰ�
	// ���㰰�� ���Ÿ� ����������.. ���� ������Ʈ�� ������ �����ؼ� �Ҹ�Ǹ� �׶� Trace��
	// ����ü�� �ϳ��� �������� ������ ������� ó���ϴ� ���
	// �׳� for�����鼭 ���ο� ������Ʈ�� ��������� �����ϰ� ���� �Ҹ������ true

	// ������ ���������� �˸��� �����ʿ��� �����ϴ� �����Լ�
	// monster->AttackEnter������ ���Ͱ� �� �����Ӷ� ���� ���� �ϴ��� ����
	// monster->AttackExit������ ������ 
	// ���ݽð��� �� ������ ����?
	// �ִϸ��̼��� 2ȸ �̻� ����Ǿ�� �ϴ� ���?
	// bool�� ��ȯ�ϴ� Attack�̶�� �Լ��� �׳� �ΰ� �� �ȿ��� �������� ������ �˻��Ѵ�.
	// ���⼭�� �� ������ ���� ó���� ���ش�.

	if (!monster->Attack())
	{
		EventRegisteror::GetInstance().ChangeMonsterState(ai, MONSTER_STATE::TRACE);
	}

	// reset �ϰ� trace��
	
	// �� �� ���� Effect�� �浹ü�� Off��
	// ���Ϳ� ���� ���� �ٸ� ó��
	// �� ó���� �����Լ��� �����? �������(��� ó���� ���ݾִϸ��̼� �ȿ��� �� ó���Ǿ�� ��)
	// �ƴϸ� bool �Լ�������� �� �Լ��� true�� �Ǹ� �� �� ���� ����
	// 1. �ذ������� ���: ���� �ִϸ��̼� ���� �浹ü�� On ��Ų��.
	
	// ���͵� ����Ʈ�� ������ �ϰ�,
	// ���Ͱ� AttState�� �� Ư�� �����ӿ� �浹ü�� Enable�Ͽ� �÷��̾� �浹ü�� �浹�ϵ��� ��
	// �׷� ���Ÿ� ���ʹ� ��� ó��?
	// ���Ÿ� ���ʹ� Ư�� �����ӿ� ������Ʈ�� ������Ŵ
	// ������Ų ������Ʈ�� �������� ���� ���ư�
	// Effect�� �� ������Ʈ ��ü�� �ǹ��ϸ�, ������Ʈ�� �������� ����? 
	// AttState���� �װ� ó����
	// �ִϸ��̼��� ���ӵǴ� ���� �� ź�˿� ���� �ִϸ��̼ǵ� �߻��Ǿ�� ��
	// �׷���... std::vector�� �������־���Ѵ�
	// Effect�� Update�� Render���� ź�˿� ���� Update�� Render�� �������־�� ��
	// ���ӿ�����Ʈ�� mDead ���� ���¸� Ȱ���ؼ� ��� ���� üũ
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

	// Ư�� �ִϸ��̼� �����ӿ� �浹ü�� ������ ��

	// Ư�� �������� �� �̰� ����ŵ� ����
	
	// ���� ����- �����Լ��� ó��
	
}

void MonsterAttState::Exit()
{
	Monster* monster = GetOwnerAI()->GetOwnerMonster();
	monster->GetAnimator()->GetCurAnimation()->Reset();
}
