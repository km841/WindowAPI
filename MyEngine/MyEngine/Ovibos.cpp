#include "pch.h"
#include "Ovibos.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "Player.h"
#include "TimeMgr.h"

Ovibos::Ovibos()
	: mMaxDashDuration(1.0f)
	, mCurDashDuration(0.f)
{
	mToolID = TOOL_ID::BTN_OVIBOS;
	mMonType = MONSTER_TYPE::GROUND_CHARGE;
	//SetSize(Vec2(99.f, 90.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetRigidBody()->SetMass(1.f);

	std::wstring idleAnimName = L"Ovibos_Idle";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"Ovibos_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"Ovibos_Move";
	SetAttAnimName(attAnimName);

	std::wstring attAfterAnimName = L"Ovibos_Idle";
	SetAttAfterAnimName(attAfterAnimName);

	SetTraceStateAnimName(idleAnimName);
	SetPatrolStateAnimName(idleAnimName);
	SetAttStateAnimName(moveAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"OvibosAnimTex", L"Texture\\ovibos_animation.bmp");

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(96.f, 66.f),
		Vec2(96.f, 0.f),
		0.1f,
		9
	);

	GetAnimator()->RegisterAnimation(
		idleAnimName + L"Right",
		animTex,
		Vec2(0.f, 66.f),
		Vec2(96.f, 66.f),
		Vec2(96.f, 0.f),
		0.1f,
		9
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 132.f),
		Vec2(105.f, 69.f),
		Vec2(105.f, 0.f),
		0.25f,
		6
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 201.f),
		Vec2(105.f, 69.f),
		Vec2(105.f, 0.f),
		0.25f,
		6
	);

	//GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetFrameDuration(3, 0.5f);
	//GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetFrameDuration(3, 0.5f);
	//GetAnimator()->FindAnimation(moveAnimName + L"Left")->SetFrameDuration(4, 1.0f);
	//GetAnimator()->FindAnimation(moveAnimName + L"Right")->SetFrameDuration(4, 1.0f);

	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	SetHPBarOffset(Vec2(-5.f, 15.f));
}

Ovibos::~Ovibos()
{
}

void Ovibos::Initialize()
{
	Monster::Initialize();
	mInfo.mSpeed = 0.f;
	mInfo.mRecog = 500.f;
	mInfo.mAttRange = mInfo.mRecog;
}

void Ovibos::Update()
{
	Monster::Update();
	GroundStateUpdate();
}

void Ovibos::Render()
{
	Monster::Render();
}

void Ovibos::Destroy()
{
	//Monster::Destroy();
}

void Ovibos::GroundStateUpdate()
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

void Ovibos::OnCollision(Collider* _other)
{
}

void Ovibos::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void Ovibos::OnCollisionExit(Collider* _other)
{
}

bool Ovibos::Attack()
{
	// 플레이어가 있는 방향으로 돌진

	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		Vec2 monsterPos = GetPos();

		if (false == mAttFlag)
		{
			mAttFlag = true;
			

			if (playerPos.x - monsterPos.x > 0.f)
			{
				mPlayerDir = Vec2(1, 0);
				mDir = DIR::RIGHT;
				GetAnimator()->SelectAnimation(GetAttAnimName() + L"Right", false);
			}
			else
			{
				mPlayerDir = Vec2(-1, 0);
				mDir = DIR::LEFT;
				GetAnimator()->SelectAnimation(GetAttAnimName() + L"Left", false);
			}
		}

		else
		{
			if (mMaxDashDuration < mCurDashDuration)
			{
				mCurDashDuration = 0.f;
				mAttFlag = false;
				mPlayerDir = ZERO_VECTOR;

				return false;
			}

			else
			{

				mCurDashDuration += DT;
				monsterPos.x += mPlayerDir.x * 500.f * DT;
				SetPos(monsterPos);

				//if (50.f > (monsterPos - playerPos).Len())
				//{
				//	mCurDashDuration = 0.f;
				//	mAttFlag = false;
				//	mPlayerDir = ZERO_VECTOR;
				//	return false;
				//}
			}
		}
	}

	return true;

}

void Ovibos::Trace()
{
	//자신과 플레이어의 방향에 따라 mDir 변경
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

bool Ovibos::DetectPlayer()
{
	return false;
}

bool Ovibos::DetectIntoAttRange()
{
	return false;
}

void Ovibos::RecogLineRender(PEN_TYPE _penType)
{
}

void Ovibos::AttRangeLineRender(PEN_TYPE _penType)
{
}

void Ovibos::Dead()
{
}
