#include "pch.h"
#include "Minotaur.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "MonsterSwordEffect.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "DustEffect.h"

Minotaur::Minotaur()
	:mMinoState(MINOTAUR_STATE::NONE)
	, mDistance(0.f)
{
	mMonType = MONSTER_TYPE::GROUND_OP_CHARGE;
	//SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"Minotaur_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"Minotaur_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"Minotaur_Att";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"Minotaur_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(idleAnimName);
	SetPatrolStateAnimName(idleAnimName);
	SetAttStateAnimName(moveAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"MinotaurAnimTex", L"Texture\\MinoAnim.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 150.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 300.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.1f,
		8
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 450.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.1f,
		8
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 600.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.07f,
		7
	);

	attAnimLeft->SetOffset(Vec2(-20, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 750.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.07f,
		7
	);

	attAnimRight->SetOffset(Vec2(-15, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);

	GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetFrameDuration(3, 0.5f);
	GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetFrameDuration(3, 0.5f);
	GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetFrameDuration(4, 1.0f);
	GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetFrameDuration(4, 1.0f);
	attAnimLeft->SetFrameDuration(2, 1.0f);
	attAnimRight->SetFrameDuration(2, 1.0f);

	attAnimLeft->SetFrameControl(0, Vec2(64.f, 0.f));
	attAnimRight->SetFrameControl(0, Vec2(10.f, 0.f));

	attAnimLeft->SetFrameControl(1, Vec2(64.f, 0.f));
	attAnimRight->SetFrameControl(1, Vec2(10.f, 0.f));

	attAnimLeft->SetFrameControl(2, Vec2(64.f, 0.f));
	attAnimRight->SetFrameControl(2, Vec2(10.f, 0.f));

	attAnimLeft->SetFrameControl(5, Vec2(4.f, 0.f));
	attAnimLeft->SetFrameControl(6, Vec2(9.f, 0.f));

	attAnimRight->SetFrameControl(5, Vec2(5.f, 0.f));
	attAnimRight->SetFrameControl(6, Vec2(5.f, 0.f));



	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	// �����Ÿ� �ȿ� ������ �뽬�ϰ� ���� ���⿡ ���� ���ݸ��
	// PATROL ���¿��� ������ ����
	// �ڵ��� �־ �¿� ���� ����
	// �Ʒ��� ���� �־ ��������
	// ���� PATROL�� �ִٰ� �÷��̾ �����Ǹ� TRACE�� �Ѿ
	// TRACE������ MOVE�� �����ϸ�, TRACE�� ������ ATT
	// ATT�� ������ ���� ATT_AFTER ���·� IDLE �ִϸ��̼� ����
	// IDLE = IDLE
	// PATROL = IDLE
	// TRACE = MOVE
	// ATT = ATT
	// ATT_AFTER = IDLE
	// TRACE���� �����Լ��� �� ������ ���������� �����δ°� ���� �� ����

	MonsterSwordEffect* effect = new MonsterSwordEffect;
	effect->SetOwner(this);
	effect->GetCollider()->SetOwner(effect);
	effect->GetCollider()->SetSize(Vec2(120, 100));
	effect->GetCollider()->SetOffset_Y(-50);
	effect->GetCollider()->SetEnable(false);
	SetEffect(effect);

	SetHPBarOffset(Vec2(-5.f, 15.f));
}

Minotaur::~Minotaur()
{
}

void Minotaur::Initialize()
{
	Monster::Initialize();
	mInfo.mSpeed = 0.f;
	mInfo.mRecog = 500.f;
	mInfo.mAttRange = mInfo.mRecog;
}

void Minotaur::Update()
{
	GroundStateUpdate();
	Monster::Update();
}

void Minotaur::Render()
{
	Monster::Render();
}

void Minotaur::Destroy()
{
	Monster::Destroy();

	for (int i = 0; i < mDustEffects.size(); ++i)
	{
		if (nullptr != mDustEffects[i])
		{
			delete mDustEffects[i];
			mDustEffects[i] = nullptr;
		}
	}

}

void Minotaur::GroundStateUpdate()
{
	const std::vector<Relation>& relations = GetRelations();
	bool isGround = false;

	bool playerUnder = false;
	for (int i = 0; i < relations.size(); ++i)
	{
		if (OBJECT_TYPE::WALL == relations[i].mOther->GetType() ||
			OBJECT_TYPE::FOOTHOLD == relations[i].mOther->GetType())
		{
			// ���� �ִ°�? ���� üũ
			Vec2 pos = CameraMgr::GetInstance().GetTileCoord(GetPos());
			Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(relations[i].mOther->GetPos());


			COLLISION_TYPE colType = relations[i].mOther->GetCollider()->GetColliderType();
			if (pos == tilePos || COLLISION_TYPE::LINE == colType)
				isGround = true;

			// Wall�ε� �÷��̾� y���� �� ū ���

			if (GetPos() < relations[i].mOther->GetPos() &&
				OBJECT_TYPE::WALL == relations[i].mOther->GetType())
			{
				//playerUnder = true;
			}
		}

		if (OBJECT_TYPE::DUNGEON_OBJECT == relations[i].mOther->GetType())
		{
			isGround = true;
		}
	}

	if (!isGround)
	{
		SetGround(false);
	}
}

void Minotaur::OnCollision(Collider* _other)
{
}

void Minotaur::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void Minotaur::OnCollisionExit(Collider* _other)
{
}

bool Minotaur::Attack()
{
	// ���� ����Ʈ�� ��������
	// ���� ����Ʈ�� ������ �浹�� ������ ��
	// �ݸ����Ŵ����� �÷��̾�� �浹�� �ִٸ� ����

	if (IsDead())
		return false;

	if (MINOTAUR_STATE::NONE == mMinoState)
	{
		mMinoState = MINOTAUR_STATE::CHARGE;
		
		Player* player = Player::GetPlayer();
		if (nullptr != player)
		{
			Vec2 playerPos = player->GetPos();
			Vec2 monsterPos = GetPos();
			mPlayerDir = playerPos - monsterPos;
		}
	}

	else if (MINOTAUR_STATE::ATTACK == mMinoState)
	{
		Animation* attAnim = GetAnimator()->GetCurAnimation();

		if (7 == attAnim->GetCurFrame())
		{
			auto& rels = mEffect->GetRelations();
			for (int i = 0; i < rels.size(); ++i)
			{
				if (OBJECT_TYPE::PLAYER == rels[i].mOther->GetType())
				{
					CollisionMgr::GetInstance().CollisionForceQuit(rels[i].mOther->GetCollider(), mEffect->GetCollider());
					break;
				}
			}

			mPlayerDir = ZERO_VECTOR;
			mMinoState = MINOTAUR_STATE::NONE;
			return false;
		}

		else
		{
			switch (mDir)
			{
			case DIR::LEFT:
				GetEffect()->GetCollider()->SetOffset_X(-80);
				break;

			case DIR::RIGHT:
				GetEffect()->GetCollider()->SetOffset_X(80);
				break;
			}

			int curFrame = attAnim->GetCurFrame();
			switch (curFrame)
			{
			case 3:
				GetEffect()->GetCollider()->SetEnable(true);
				break;

			case 4:
				GetEffect()->GetCollider()->SetEnable(false);
				break;
			}
		}
	}

	else if (MINOTAUR_STATE::CHARGE == mMinoState)
	{
		// �÷��̾� ��ġ�� ����
		// �������� 4�� ��

		Animation* anim = GetAnimator()->GetCurAnimation();
		if (nullptr != anim)
		{
			int frame = anim->GetCurFrame();

			if (anim->IsFinished())
			{
				ChangeMinoAttackState();
			}

			if (4 == frame)
			{
				Player* player = Player::GetPlayer();
				if (nullptr != player)
				{
					Vec2 playerPos = player->GetPos();
					Vec2 monsterPos = GetPos();
					
					if (mPlayerDir.x > 0.f)
						monsterPos.x += 600.f * DT;
					else
						monsterPos.x -= 600.f * DT;


					SetPos(monsterPos);

					mDistance += 600.f * DT;
					if (mDistance > 100.f)
					{
						mDistance = 0.f;
						DustEffect* dust = new DustEffect;
						dust->SetOwner(this);
						dust->Initialize();

						mDustEffects.push_back(dust);

						EventRegisteror::GetInstance().CreateObject(dust, dust->GetType());
					}

					if (50.f > abs(playerPos.x - monsterPos.x))
					{
						ChangeMinoAttackState();
					}
				}
			}
		}
	}

	return true;
}

void Minotaur::ChangeMinoAttackState()
{
	mMinoState = MINOTAUR_STATE::ATTACK;
	Animation* anim = GetAnimator()->GetCurAnimation();

	if (nullptr != anim)
	{
		anim->Reset();

		switch (mDir)
		{
		case DIR::LEFT:
			GetAnimator()->SelectAnimation(GetAttAnimName() + L"Left", false);
			break;

		case DIR::RIGHT:
			GetAnimator()->SelectAnimation(GetAttAnimName() + L"Right", false);
			break;
		}
	}
}

void Minotaur::Trace()
{
	//�ڽŰ� �÷��̾��� ���⿡ ���� mDir ����
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		mPrevDir = mDir;
		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = GetPos();

		if (playerPos.x - monsterPos.x > 0.f)
		{
			mDir = DIR::RIGHT;
		}

		else
		{
			mDir = DIR::LEFT;
		}
	}
}

bool Minotaur::DetectPlayer()
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
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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

bool Minotaur::DetectIntoAttRange()
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

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
				{
					return true;
				}
			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				//  angle = arccos ( (a��b) / (|a|*|b|) ) 
				angle = acos(detectVec.Dot(targetVec) / (detectLen * targetLen));
				angle = Math::RadianToDegree(angle);
				if (angle < 10)
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

void Minotaur::RecogLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());


	// ���͸� ȸ����Ų �� �Ÿ��� ���ؼ� �� ��ġ�� ���Ѵ�
	// ��/������ ���� ������ ó���ؾ� �ϹǷ� ���⿡ ���� ���� ���ϱ�

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
	LineTo(BACK_BUF_DC, (int)dirVec.x, (int)(dirVec.y - offset));
}

void Minotaur::AttRangeLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());
	// ���͸� ȸ����Ų �� �Ÿ��� ���ؼ� �� ��ġ�� ���Ѵ�
	// ��/������ ���� ������ ó���ؾ� �ϹǷ� ���⿡ ���� ���� ���ϱ�

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
	LineTo(BACK_BUF_DC, (int)dirVec.x, (int)(dirVec.y - offset));
}

void Minotaur::Dead()
{
	GetCollider()->SetEnable(false);

	MonsterEffect* effect = GetEffect();
	if (nullptr != effect)
	{
		if (nullptr != effect->GetCollider())
		{
			effect->GetCollider()->SetEnable(false);
		}
	}

	GameObject::Dead();
}


