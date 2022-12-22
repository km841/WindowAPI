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

Minotaur::Minotaur()
{
	mMonType = MONSTER_TYPE::GROUND_MELEE;
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
		0.1f,
		7
	);

	attAnimLeft->SetOffset(Vec2(-50, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 750.f),
		Vec2(168.f, 150.f),
		Vec2(168.f, 0.f),
		0.1f,
		7
	);

	attAnimRight->SetOffset(Vec2(50, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	// 사정거리 안에 들어오면 대쉬하고 나서 방향에 따른 공격모션
	// PATROL 상태에도 가만히 있음
	// 뒤돌아 있어도 좌우 전부 감지
	// 아래나 위에 있어도 마찬가지
	// 따라서 PATROL로 있다가 플레이어가 감지되면 TRACE로 넘어감
	// TRACE에서는 MOVE로 돌격하며, TRACE가 끝나면 ATT
	// ATT이 끝나고 나면 ATT_AFTER 상태로 IDLE 애니메이션 적용
	// IDLE = IDLE
	// PATROL = IDLE
	// TRACE = MOVE
	// ATT = ATT
	// ATT_AFTER = IDLE
	// TRACE에서 가상함수로 각 몬스터의 추적패턴을 나눠두는게 좋을 것 같음

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
			// 위에 있는가? 까지 체크
			Vec2 pos = CameraMgr::GetInstance().GetTileCoord(GetPos());
			Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(relations[i].mOther->GetPos());


			COLLISION_TYPE colType = relations[i].mOther->GetCollider()->GetColliderType();
			if (pos == tilePos || COLLISION_TYPE::LINE == colType)
				isGround = true;

			// Wall인데 플레이어 y보다 더 큰 경우

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
}

void Minotaur::OnCollisionExit(Collider* _other)
{
}

bool Minotaur::Attack()
{
	// 공격 이펙트가 끝났는지
	// 공격 이펙트가 끝나면 충돌을 끝내야 함
	// 콜리전매니저에 플레이어와 충돌이 있다면 삭제

	if (IsDead())
		return false;

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

		case 5:
			GetEffect()->GetCollider()->SetEnable(false);
			break;
		}

		return true;
	}
}

void Minotaur::Trace()
{
	// 플레이어와의 거리를 계산하고 멀다면 돌격
	// 아니라면 Attack
}

bool Minotaur::DetectPlayer()
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
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

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
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
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
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


	// 벡터를 회전시킨 후 거리를 곱해서 점 위치를 구한다
	// 좌/우측에 따라 별도로 처리해야 하므로 방향에 따른 벡터 구하기

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
	// 벡터를 회전시킨 후 거리를 곱해서 점 위치를 구한다
	// 좌/우측에 따라 별도로 처리해야 하므로 방향에 따른 벡터 구하기

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
