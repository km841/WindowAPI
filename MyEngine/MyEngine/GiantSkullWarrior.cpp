#include "pch.h"
#include "GiantSkullWarrior.h"
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

GiantSkullWarrior::GiantSkullWarrior()
	:mJumpMaxTime(1.5f)
	,mJumpCurTime(0.f)
	,mJump(false)
{
	mToolID = TOOL_ID::BTN_GIANT_SKULL;
	mMonType = MONSTER_TYPE::GROUND_MELEE;
	SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"GiantSkull_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"GiantSkull_Move";
	SetMoveAnimName(moveAnimName);
	
	std::wstring attAnimName = L"GiantSkull_Att";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"GiantSkull_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(moveAnimName);
	SetPatrolStateAnimName(moveAnimName);
	SetAttStateAnimName(attAnimName);
	
	Texture* animTex = LOAD_TEXTURE(L"GiantSkullAnimTex", L"Texture\\Monster\\GiantSkullAnim.bmp");
	Texture* hitAnimTex = LOAD_TEXTURE(L"GiantSkullHitAnimTex", L"Texture\\Monster\\GiantSkullHitAnim.bmp");

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
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimLeft->SetOffset(Vec2(-50, 0));

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 504.f),
		Vec2(213.f, 144.f),
		Vec2(213.f, 0.f),
		0.1f,
		12
	);

	attAnimRight->SetOffset(Vec2(50, 0));

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);

	GetAnimator()->FindAnimation(idleAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(idleAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Left")->SetHitAnimation(hitAnimTex);
	GetAnimator()->FindAnimation(attAnimName + L"Right")->SetHitAnimation(hitAnimTex);


	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	MonsterSwordEffect* effect = new MonsterSwordEffect;
	effect->SetOwner(this);
	effect->GetCollider()->SetOwner(effect);
	effect->GetCollider()->SetSize(Vec2(120, 100));
	effect->GetCollider()->SetOffset_Y(-50);
	effect->GetCollider()->SetEnable(false);
	SetEffect(effect);

	SetHPBarOffset(Vec2(-5.f, 15.f));
}

GiantSkullWarrior::~GiantSkullWarrior()
{
}

void GiantSkullWarrior::Initialize()
{
	Monster::Initialize();
}

void GiantSkullWarrior::Update()
{
	GroundStateUpdate();
	Monster::Update();

	if (true == mJump)
	{
		if (mJumpMaxTime < mJumpCurTime)
		{
			mJump = false;
			mJumpCurTime = 0.f;
		}

		else
		{
			mJumpCurTime += DT;
		}
	}

}

void GiantSkullWarrior::Render()
{
	Monster::Render();

}

void GiantSkullWarrior::Destroy()
{
	Monster::Destroy();
}

void GiantSkullWarrior::GroundStateUpdate()
{
	const std::vector<Relation>& relations = GetRelations();
	bool isGround = false;

	bool playerUnder = false;
	for (int i = 0; i < relations.size(); ++i)
	{
		if (OBJECT_TYPE::WALL == relations[i].mOther->GetType() ||
			OBJECT_TYPE::FOOTHOLD == relations[i].mOther->GetType())
		{
			// ???? ??????? ???? ????
			Vec2 pos = CameraMgr::GetInstance().GetTileCoord(GetPos());
			Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(relations[i].mOther->GetPos());


			COLLISION_TYPE colType = relations[i].mOther->GetCollider()->GetColliderType();
			if (pos == tilePos || COLLISION_TYPE::LINE == colType)
				isGround = true;

			// Wall???? ???????? y???? ?? ?? ????

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

void GiantSkullWarrior::OnCollision(Collider* _other)
{
}

void GiantSkullWarrior::OnCollisionEnter(Collider* _other)
{
	// ???????? ???? ?? ???????? ????, 
	// ???????? ?????? HP?? 0?? ???? Dead???????? ???? ???????????? ????
	// ???????????? ???? ?? DeleteObject..
	// if (isDead() && GetCurAnim()->isFinished())
	//   -> ????
	Monster::OnCollisionEnter(_other);

	

}

void GiantSkullWarrior::OnCollisionExit(Collider* _other)
{
	if (0 == GetCollider()->GetColCnt())
		SetGround(false);
}

bool GiantSkullWarrior::Attack()
{
	// ???? ???????? ????????
	// ???? ???????? ?????? ?????? ?????? ??
	// ?????????????? ?????????? ?????? ?????? ????

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

void GiantSkullWarrior::Trace()
{
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		mPrevDir = mDir;

		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = GetPos();
		// ???? ?????? ?? ?????????? ????
		// ???? ??????? ???????? ???? - ?? ???? ?? ?????? ???? ????

		Vec2 dirVec = monsterPos - playerPos;

		if (0 > dirVec.x)
		{

			if (dirVec.x > -10.f)
				monsterPos.x -= mInfo.mSpeed * DT;
			else
				monsterPos.x += mInfo.mSpeed * DT;
			
			
			mDir = DIR::RIGHT;
		}

		else
		{
			if (dirVec.x < 10.f)
				monsterPos.x += mInfo.mSpeed * DT;
			else
				monsterPos.x -= mInfo.mSpeed * DT;

			mDir = DIR::LEFT;
		}

		SetPos(monsterPos);



		if (false == mJump)
		{
			if (dirVec.Len() < 400.f &&
				playerPos.y < monsterPos.y - 150.f && 
				player->GetGround())
			{
				GetRigidBody()->SetVelocity_Y(-1000.f);
				mJump = true;
			}
		}



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

bool GiantSkullWarrior::DetectPlayer()
{
	float angle = 0.f;

	// 1. ?????????? ?????? + ?????????????? ????
	// 2. ?????????? ???????????? ????
	// ?? ?????? ???????? 2???? 1?????? ?????? ???? ?????? ???? ???? ?????? ???? ????
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
				//  angle = arccos ( (a??b) / (|a|*|b|) ) 
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
				//  angle = arccos ( (a??b) / (|a|*|b|) ) 
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

bool GiantSkullWarrior::DetectIntoAttRange()
{
	float angle = 0.f;

	// 1. ?????????? ?????? + ?????????????? ????
	// 2. ?????????? ???????????? ????
	// ?? ?????? ???????? 2???? 1?????? ?????? ???? ?????? ???? ???? ?????? ???? ????
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
				//  angle = arccos ( (a??b) / (|a|*|b|) ) 
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
				//  angle = arccos ( (a??b) / (|a|*|b|) ) 
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

void GiantSkullWarrior::RecogLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());


	// ?????? ???????? ?? ?????? ?????? ?? ?????? ??????
	// ??/?????? ???? ?????? ???????? ?????? ?????? ???? ???? ??????

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

void GiantSkullWarrior::AttRangeLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());
	// ?????? ???????? ?? ?????? ?????? ?? ?????? ??????
	// ??/?????? ???? ?????? ???????? ?????? ?????? ???? ???? ??????

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

void GiantSkullWarrior::Dead()
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

