#include "pch.h"
#include "RedGiantBat.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "Player.h"
#include "RotateMissileEffect.h"
#include "EventRegisteror.h"

RedGiantBat::RedGiantBat()
{
	SetSize(Vec2(192.f, 192.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -50.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"RedGiantBat_Move";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"RedGiantBat_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"RedGiantBat_Att";
	SetAttAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"RedGiantBatAnimTex", L"Texture\\red_giant_bat_animation.bmp");

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 192.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 384.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 576.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	RotateMissileEffect* effect = new RotateMissileEffect;
	effect->SetOwner(this);
	SetEffect(effect);
	
}

RedGiantBat::~RedGiantBat()
{
}

void RedGiantBat::Initialize()
{
	Monster::Initialize();
}

void RedGiantBat::Update()
{
	Monster::Update();
	if (nullptr != mEffect)
	{
		mEffect->Update();
	}




}

void RedGiantBat::Render()
{
	Monster::Render();


	// Update���� �̻����� ������ �� ��ü���� ���� ���� ���������� �浹�ؾ� �ϹǷ�
	// �� �̻��ϵ��� Update�ϰ� Render���� �ʿ䰡 ����.

	//wchar_t batGravity[COMMENT_MAX_SIZE] = {};
	//swprintf_s(batGravity, L"targetVec.x : %f, targetVec.y : %f", mTargetVec.x, mTargetVec.y);
	//TextOut(BACK_BUF_DC, 10, 130, batGravity, (int)wcslen(batGravity));
}

void RedGiantBat::Destroy()
{
	Monster::Destroy();
}

void RedGiantBat::OnCollision(Collider* _other)
{
}

void RedGiantBat::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void RedGiantBat::OnCollisionExit(Collider* _other)
{
}

bool RedGiantBat::Attack()
{
	
	// ����Ʈ
	// ����Ʈ�� Attack�� ���� ������ ����?
	// ����Ʈ�� 

	// Effect�� Attack���� Ư�� ���ݹ���� �����ϸ�
	// Effect�� �� ������ ����� ������ Update�� ����
	// Effect�� ������ �� ������ Attack�� False�� ��ȯ�Ѵ�.

	// Attack�� AttackState�� Update���� �˻��ϸ�
	// Attack�� ���۰� ���� ������
	// ������?  

	// Monster�� Update���� Effect�� Update�� �����ָ�
	// Effect�� Update�ȿ����� ������ ���ݿ��� �ؾ� �� �ϵ��� �ؾ� �Ѵ�
	// ź���� ȸ����Ű���� Effect�� ���ο��� for���� ���� ź���� ��ġ�� �����ؾ� ��
	// ź�� �̵��� Effect�� Update���� ��ġ�� �������ִ� ��


	// SwordEffect�� �׳��浹ü�� �����״����ָ�Ǵ°Ϳ�����
	// MissileEffect�� ���� �̻����� ������ ��
	// �� ���� �� Effect���� ������ �ֵ����� �Ѱ��־�� �Ѵٴ� ��
	// - Effect�� Update������ �?
	// - Missile�� �����
	// - Missile�� ����°� ���� Monster�� �ִϸ��̼� �����Ӱ� �������� ������ ����
	// - ȸ��ź�� ���� Ư�� �߻����� ��� �����ؾ��ϴ°�?
	// - MissileEffect�� ����Լ��� ���� ����
	// - MissileEffect�� �׷� ��� ���Ÿ� ������ ���������� �����ϰ� �־�� �ϳ�?
	// - ȸ��ź, ����ź �� �ܼ��� ź���� ���⼭ �����ϰ� Monster�� Attack�ȿ��� �����
	// - Attack �ȿ��� Ư�� �����ӿ� ���缭 �����Ϸ���?
	// - �������� ��ȿ�ϰ� �ۿ��Ϸ��� �ִϸ��̼� ������ ���۽���, ��������� ���Ͱ�ü�� ������ �����ؾ� ��
	


	return mEffect->Attack();
}

bool RedGiantBat::DetectPlayer()
{
	float angle = 0.f;

	// 1. ���Ϳ��� ���� + �νĹ��������� ����
	// 2. ���Ϳ��� �÷��̾���� ����
	// �� ���͸� ���ؼ� 2���� 1������ ������ �۰� ���̵� ª�� ��� �ν��� �ɷ� ó��
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -150 ~ -180 (�ϴ� 150, ������ 180) // ������ ��������

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				// �÷��̾� ��ġ���� �� ��ġ�� �� ����

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	return false;
}

bool RedGiantBat::DetectIntoAttRange()
{
	float angle = 0.f;

	// 1. ���Ϳ��� ���� + �νĹ��������� ����
	// 2. ���Ϳ��� �÷��̾���� ����
	// �� ���͸� ���ؼ� 2���� 1������ ������ �۰� ���̵� ª�� ��� �ν��� �ɷ� ó��
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -140 ~ -180 (�ϴ� 150, ������ 180) // ������ ��������

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x - mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = attRangeVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				// �÷��̾� ��ġ���� �� ��ġ�� �� ����

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x + mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = monsterPos - attRangeVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	//wchar_t szBuffer[256] = {};
	//swprintf_s(szBuffer, L"angle : %f", angle);
	//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
	return false;
}

void RedGiantBat::RecogLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
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

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mRecog;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mRecog;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mRecog - offset));
}

void RedGiantBat::AttRangeLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
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

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mAttRange;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mAttRange;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mAttRange - offset));
}
