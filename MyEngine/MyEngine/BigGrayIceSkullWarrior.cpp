#include "pch.h"
#include "BigGrayIceSkullWarrior.h"
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
#include "IceCubesMissileEffect.h"
#include "IceBullet.h"

BigGrayIceSkullWarrior::BigGrayIceSkullWarrior()
	: mSkillEffect(nullptr)
{
	mToolID = TOOL_ID::BTN_ICE_GRAY_SKULL;
	mMonType = MONSTER_TYPE::GROUND_SKILL;
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"BigGraySkull_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"BigGraySkull_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"BigGraySkull_Att";
	SetAttAnimName(attAnimName);

	std::wstring skillAnimName = L"BigGraySkull_Skill";
	SetSkillAnimName(skillAnimName);

	std::wstring attAfterAnimName = L"BigGraySkull_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(moveAnimName);
	SetPatrolStateAnimName(moveAnimName);
	SetAttStateAnimName(attAnimName);

	Texture* animTex = LOAD_TEXTURE(L"BigGraySkullAnimTex", L"Texture\\Monster\\BigGraySkullAnim.bmp");
	Texture* hitAnimTex = LOAD_TEXTURE(L"BigGraySkullHitAnimTex", L"Texture\\Monster\\BigGraySkullHitAnim.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 90.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 180.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 270.f),
		Vec2(99.f, 90.f),
		Vec2(99.f, 0.f),
		0.1f,
		6
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 360.f),
		Vec2(210.f, 144.f),
		Vec2(210.f, 0.f),
		0.1f,
		12
	);

	attAnimLeft->SetFrameControl(0, Vec2(50, 0));
	attAnimLeft->SetFrameControl(1, Vec2(40, 0));
	attAnimLeft->SetFrameControl(2, Vec2(-43, 0));
	attAnimLeft->SetFrameControl(3, Vec2(-55, 0));
	attAnimLeft->SetFrameControl(4, Vec2(-60, 0));
	attAnimLeft->SetFrameControl(5, Vec2(-78, 0));
	attAnimLeft->SetFrameControl(6, Vec2(-63, 0));
	attAnimLeft->SetFrameControl(7, Vec2(-43, 0));
	attAnimLeft->SetFrameControl(8, Vec2(-53, 0));
	attAnimLeft->SetFrameControl(9, Vec2(-58, 0));
	attAnimLeft->SetFrameControl(10, Vec2(-43, 0));
	attAnimLeft->SetFrameControl(11, Vec2(-30, 0));

	//attAnimLeft->SetOffset(Vec2(-50, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 504.f),
		Vec2(210.f, 144.f),
		Vec2(210.f, 0.f),
		0.1f,
		12
	);

	attAnimRight->SetOffset(Vec2(50, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->RegisterAnimation(
		skillAnimName + L"Left",
		animTex,
		Vec2(0.f, 648.f),
		Vec2(120.f, 120.f),
		Vec2(120.f, 0.f),
		0.1f,
		13
	);

	GetAnimator()->RegisterAnimation(
		skillAnimName + L"Right",
		animTex,
		Vec2(0.f, 768.f),
		Vec2(120.f, 120.f),
		Vec2(120.f, 0.f),
		0.1f,
		13
	);

	GetAnimator()->FindAnimation(idleAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(idleAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(skillAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(skillAnimName + L"Right")->SetHitAnimation(hitAnimTex);



	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	mSkillEffect = new IceCubesMissileEffect;
	mSkillEffect->SetOwner(this);


	MonsterSwordEffect* effect = new MonsterSwordEffect;
	effect->SetOwner(this);
	effect->GetCollider()->SetOwner(effect);
	effect->GetCollider()->SetSize(Vec2(120, 100));
	effect->GetCollider()->SetOffset_Y(-50);
	effect->GetCollider()->SetEnable(false);
	SetEffect(effect);

	SetHPBarOffset(Vec2(-5.f, 15.f));
}

BigGrayIceSkullWarrior::~BigGrayIceSkullWarrior()
{
	if (nullptr != mSkillEffect)
	{
		delete mSkillEffect;
		mSkillEffect = nullptr;
	}
}

void BigGrayIceSkullWarrior::Initialize()
{
	Monster::Initialize();

	mSkillEffect->SetPos(GetPos());
	mSkillEffect->Initialize();
	mSkillEffect->SetOffset(Vec2(0.f, -30.f));
	EventRegisteror::GetInstance().CreateObject(mSkillEffect, mSkillEffect->GetType());

}

void BigGrayIceSkullWarrior::Update()
{
	Monster::Update();
}

void BigGrayIceSkullWarrior::Render()
{
	Monster::Render();
}

void BigGrayIceSkullWarrior::Destroy()
{
	Monster::Destroy();
}

void BigGrayIceSkullWarrior::GroundStateUpdate()
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

void BigGrayIceSkullWarrior::OnCollision(Collider* _other)
{
}

void BigGrayIceSkullWarrior::OnCollisionEnter(Collider* _other)
{

	Monster::OnCollisionEnter(_other);

}

void BigGrayIceSkullWarrior::OnCollisionExit(Collider* _other)
{
	if (0 == GetCollider()->GetColCnt())
		SetGround(false);
}

bool BigGrayIceSkullWarrior::Attack()
{
	// 공격 이펙트가 끝났는지
	// 공격 이펙트가 끝나면 충돌을 끝내야 함
	// 콜리전매니저에 플레이어와 충돌이 있다면 삭제

	if (IsDead())
		return false;

	Animation* attAnim = GetAnimator()->GetCurAnimation();

	if (11 == attAnim->GetCurFrame())
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
		case 2:
			GetEffect()->GetCollider()->SetEnable(true);
			break;

		case 4:
			GetEffect()->GetCollider()->SetEnable(false);
			break;
		}

		return true;
	}
}

bool BigGrayIceSkullWarrior::Skill()
{

	return mSkillEffect->Skill();
}

void BigGrayIceSkullWarrior::Trace()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		mPrevDir = mDir;

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = GetPos();
		// 방향 전환할 때 애니메이션 변환
		// 방향 전환은? 플레이어 위치 - 내 위치 의 부호에 따라 변환

		Vec2 dirVec = monsterPos - playerPos;
		float distance = dirVec.Len();

		if (distance < mInfo.mAttRange * 2.f && 
			distance > mInfo.mAttRange)
		{
			EventRegisteror::GetInstance().ChangeMonsterState(mAI, MONSTER_STATE::SKILL);
			return;
		}

		dirVec.Norm();

		if (0 > dirVec.x)
		{
			monsterPos.x += mInfo.mSpeed * DT;
			mDir = DIR::RIGHT;
		}

		else
		{
			monsterPos.x -= mInfo.mSpeed * DT;
			mDir = DIR::LEFT;
		}

		SetPos(monsterPos);

		if (mPrevDir != mDir)
		{
			const std::wstring& animName = GetMoveAnimName();
			switch (mDir)
			{
			case DIR::LEFT:
				GetAnimator()->SelectAnimation(animName + L"Left", true);
				break;

			case DIR::RIGHT:
				GetAnimator()->SelectAnimation(animName + L"Right", true);
				break;
			}
		}


	}

}

bool BigGrayIceSkullWarrior::DetectPlayer()
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

bool BigGrayIceSkullWarrior::DetectIntoAttRange()
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

void BigGrayIceSkullWarrior::RecogLineRender(PEN_TYPE _penType)
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

void BigGrayIceSkullWarrior::AttRangeLineRender(PEN_TYPE _penType)
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

void BigGrayIceSkullWarrior::Dead()
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