#include "pch.h"
#include "LockedDoor.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "CameraMgr.h"
#include "Player.h"
#include "Monster.h"
#include "RigidBody.h"
#include "Gold.h"


LockedDoor::LockedDoor()
	: mAngleType(ANGLE_TYPE::DEGREE_0_TYPE)
{
	SetType(OBJECT_TYPE::DUNGEON_OBJECT);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	Texture* deg0Tex = ResourceMgr::GetInstance().Load<Texture>(L"LockedDoor_0Deg_Tex", L"Texture\\LockedDoor_0Deg_Anim.bmp");
	Texture* deg90Tex = ResourceMgr::GetInstance().Load<Texture>(L"LockedDoor_90Deg_Tex", L"Texture\\LockedDoor_90Deg_Anim.bmp");
	Texture* deg270Tex = ResourceMgr::GetInstance().Load<Texture>(L"LockedDoor_270Deg_Tex", L"Texture\\LockedDoor_270Deg_Anim.bmp");

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	GetAnimator()->RegisterAnimation(
		L"LockedDoor_0Degree",
		deg0Tex,
		Vec2(0, 0),
		Vec2(198, 60),
		Vec2(198, 0),
		0.1f,
		23
	);

	GetAnimator()->RegisterAnimation(
		L"LockedDoor_90Degree",
		deg90Tex,
		Vec2(0, 0),
		Vec2(60, 198),
		Vec2(60, 0),
		0.1f,
		23
	);

	GetAnimator()->RegisterAnimation(
		L"LockedDoor_270Degree",
		deg270Tex,
		Vec2(0, 0),
		Vec2(60, 198),
		Vec2(60, 0),
		0.1f,
		23
	);


}

LockedDoor::~LockedDoor()
{
}

void LockedDoor::Initialize()
{

	GameObject::Initialize();
}

void LockedDoor::Update()
{
	Animation* curAnim = GetAnimator()->GetCurAnimation();
	if (nullptr != curAnim)
	{
		switch (mAngleType)
		{
		case ANGLE_TYPE::DEGREE_0_TYPE:
		{
			if (L"LockedDoor_0Degree" == curAnim->GetName())
			{
				GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
				Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
				GetCollider()->SetSize(size);
				GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
			}
		}
			break;
		case ANGLE_TYPE::DEGREE_90_TYPE:
		{
			if (L"LockedDoor_90Degree" == curAnim->GetName())
			{
				GetAnimator()->SelectAnimation(L"LockedDoor_90Degree", false);
				Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
				GetCollider()->SetSize(size);
				GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
			}
		}
			break;
		case ANGLE_TYPE::DEGREE_270_TYPE:
		{
			if (L"LockedDoor_270Degree" == curAnim->GetName())
			{
				GetAnimator()->SelectAnimation(L"LockedDoor_270Degree", false);
				Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
				GetCollider()->SetSize(size);
				GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
			}
		}
			break;
		}
	}

	else
	{
		switch (mAngleType)
		{
		case ANGLE_TYPE::DEGREE_0_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);
			GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
		}
			break;
		case ANGLE_TYPE::DEGREE_90_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_90Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);
			GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
		}
			break;
		case ANGLE_TYPE::DEGREE_270_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_270Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);
			GetCollider()->SetOffset(Vec2(0.f, -(size.y / 2.f)));
		}
			break;
		}
	}

	curAnim = GetAnimator()->GetCurAnimation();
	int frame = curAnim->GetCurFrame();
	
	if (!mFlag)
	{
		switch (frame)
		{
		case 15:
			curAnim->SetCurFrame(8);
		}
	}

	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerColPos = player->GetCollider()->GetPos();
		Vec2 playerTilePos = CameraMgr::GetInstance().GetTileCoord(playerColPos);
		Vec2 myTilePos = CameraMgr::GetInstance().GetTileCoord(GetPos());

		Vec2 topTilePos = Vec2(myTilePos.x, myTilePos.y - TILE_SIZE);
		if (playerTilePos == topTilePos)
		{
			mPlayerAbobeMe = true;
		}
		else
			mPlayerAbobeMe = false;
	}
	GameObject::Update();
}

void LockedDoor::Render()
{
	Vec2 pos = RENDER_POS(GetPos());

	GameObject::Render();
}

void LockedDoor::Destroy()
{
	GameObject::Destroy();
}

void LockedDoor::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		Vec2 dirVec = otherPos - pos;

		float diff_x = (size.x / 2.f + otherSize.x / 2.f) - abs(pos.x - otherPos.x);
		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		if (diff_x < diff_y)
		{
			int sign = 1;
			if (dirVec.x < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.x += (diff_x + 1) * sign;
			otherPos.x += (diff_x + 1) * sign;
		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			if (2.f < diff_y)
			{
				otherObjPos.y += (diff_y)*sign;
				otherPos.y += (diff_y)*sign;
			}

		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		Vec2 dirVec = otherPos - pos;

		float diff_x = (size.x / 2.f + otherSize.x / 2.f) - abs(pos.x - otherPos.x);
		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);


		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		if (diff_x < diff_y)
		{

			int sign = 1;
			if (dirVec.x < 0.f)
			{
				sign = -sign;
			}

			if (5.f < diff_x)
			{
				otherObjPos.x += (diff_x + 1) * sign;
				otherPos.x += (diff_x + 1) * sign;
			}

		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			if (5.f < diff_y)
			{
				otherObjPos.y += (diff_y)*sign;
				otherPos.y += (diff_y)*sign;
			}
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}

	if (OBJECT_TYPE::DROP_GOLD == _other->GetOwner()->GetType())
	{
		Vec2 pos = GetCollider()->GetPos();
		Vec2 size = GetCollider()->GetSize();

		Vec2 otherPos = _other->GetPos();
		Vec2 otherSize = _other->GetSize();

		Vec2 dirVec = otherPos - pos;

		float diff_x = (size.x / 2.f + otherSize.x / 2.f) - abs(pos.x - otherPos.x);
		float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);

		Vec2 otherObjPos = _other->GetOwner()->GetPos();
		if (diff_x < diff_y)
		{
			int sign = 1;
			if (dirVec.x < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.x += (diff_x + 1) * sign;
			otherPos.x += (diff_x + 1) * sign;
		}

		else
		{
			int sign = 1;
			if (dirVec.y < 0.f)
			{
				sign = -sign;
			}

			otherObjPos.y += (diff_y)*sign;
			otherPos.y += (diff_y)*sign;
		}

		_other->GetOwner()->SetPos(otherObjPos);
		_other->SetPos(otherPos);
	}
}

void LockedDoor::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		static_cast<Player*>(_other->GetOwner())->InGround();
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		Monster* monster = static_cast<Monster*>(_other->GetOwner());
		monster->GetRigidBody()->SetVelocity_Y_Zero();
		static_cast<Monster*>(_other->GetOwner())->SetGround(true);

	}

	if (OBJECT_TYPE::DROP_GOLD == _other->GetOwner()->GetType())
	{
		Gold* gold = static_cast<Gold*>(_other->GetOwner());
		gold->GetRigidBody()->SetVelocity_Zero();
		static_cast<Gold*>(_other->GetOwner())->SetGround(true);
	}
}

void LockedDoor::OnCollisionExit(Collider* _other)
{
}
