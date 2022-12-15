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
#include "KeyMgr.h"
#include "EventRegisteror.h"
#include "Particle.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"


LockedDoor::LockedDoor()
	: mAngleType(ANGLE_TYPE::DEGREE_0_TYPE)
	, mDelayTime(0.f)
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
		0.05f,
		23
	);

	GetAnimator()->RegisterAnimation(
		L"LockedDoor_90Degree",
		deg90Tex,
		Vec2(0, 0),
		Vec2(60, 198),
		Vec2(60, 0),
		0.05f,
		23
	);

	GetAnimator()->RegisterAnimation(
		L"LockedDoor_270Degree",
		deg270Tex,
		Vec2(0, 0),
		Vec2(60, 198),
		Vec2(60, 0),
		0.05f,
		23
	);

	GetAnimator()->FindAnimation(L"LockedDoor_0Degree")->SetEffectAnimation(true);
	GetAnimator()->FindAnimation(L"LockedDoor_90Degree")->SetEffectAnimation(true);
	GetAnimator()->FindAnimation(L"LockedDoor_270Degree")->SetEffectAnimation(true);


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
		case ANGLE_TYPE::DEGREE_180_TYPE:
		{
			if (L"LockedDoor_0Degree" == curAnim->GetName())
			{
				GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
				Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
				GetCollider()->SetSize(size);

				mDir = Vec2(0, 1);
			}
		}
		case ANGLE_TYPE::DEGREE_0_TYPE:
		{
			if (L"LockedDoor_0Degree" == curAnim->GetName())
			{
				GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
				Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
				GetCollider()->SetSize(size);

				mDir = Vec2(0, -1);
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

				mDir = Vec2(-1, 0);
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

				mDir = Vec2(1, 0);
			}
		}
			break;
		}
	}

	else
	{
		switch (mAngleType)
		{
		case ANGLE_TYPE::DEGREE_180_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);

			mDir = Vec2(0, 1);
		}
		break;
		case ANGLE_TYPE::DEGREE_0_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_0Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);

			mDir = Vec2(0, -1);
		}
			break;
		case ANGLE_TYPE::DEGREE_90_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_90Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);

			mDir = Vec2(-1, 0);
		}
			break;
		case ANGLE_TYPE::DEGREE_270_TYPE:
		{
			GetAnimator()->SelectAnimation(L"LockedDoor_270Degree", false);
			Vec2 size = GetAnimator()->GetCurAnimation()->GetAnimInfo()[0].mSlice;
			GetCollider()->SetSize(size);

			mDir = Vec2(1, 0);
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

	else
	{
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			GetCollider()->SetEnable(false);
			// 충돌 해제
			// 

			const std::vector<Relation> rels = GetRelations();
			for (auto& rel : rels)
			{
				CollisionMgr::GetInstance().CollisionForceQuit(GetCollider(), rel.mOther->GetCollider());
				if (OBJECT_TYPE::PLAYER == rel.mOther->GetType())
				{
					Player::GetPlayer()->OutGround();
				}
			}

			if (mDelayTime > 0.05f)
			{
				mDelayTime = 0.f;
				Vec2 pos = GetPos();
				Vec2 size = GetCollider()->GetSize();

				Vec2 ltPos = pos - size / 2.f;
				float rand_x = ltPos.x + (rand() % (int)(size.x));
				float rand_y = ltPos.y + (rand() % (int)(size.y));

				Particle* particle = new Particle;
				particle->SetPos(Vec2(rand_x, rand_y));
				particle->SetDir(mDir);

				EventRegisteror::GetInstance().CreateObject(particle, particle->GetType());
			}
			else
			{
				mDelayTime += DT;
			}
		}

	}

	GameObject::Update();
}

void LockedDoor::Render()
{
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
