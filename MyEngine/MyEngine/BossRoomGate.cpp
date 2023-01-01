#include "pch.h"
#include "BossRoomGate.h"
#include "Collider.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "Animation.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "DungeonScene.h"
#include "EventRegisteror.h"
#include "Map.h"

BossRoomGate::BossRoomGate()
	:mState(DOOR_STATE::OPEN)
	,mPrevState(DOOR_STATE::OPEN)
	,mCollision(false)
{
	SetType(OBJECT_TYPE::DUNGEON_OBJECT);
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30, 30));
	GetCollider()->SetOffset(Vec2(0, -15));

	mKeyTex = ResourceMgr::GetInstance().Load<Texture>(L"F_KEY", L"Texture\\F.bmp");
}

BossRoomGate::~BossRoomGate()
{
}

void BossRoomGate::Initialize()
{
	GameObject::Initialize();
}

void BossRoomGate::Update()
{
	GameObject::Update();

	Animation* anim = GetAnimator()->GetCurAnimation();
	if (nullptr != anim)
	{
		int frame = anim->GetCurFrame();

		if (9 == frame)
		{
			anim->SetFrameFix(true);
		}
	}

	if (mCollision && (DOOR_STATE::OPEN == mState))
	{
		if (IS_JUST_PRESSED(KEY::F))
		{
			// Side Room ÀÌµ¿
			Scene* scene = SceneMgr::GetInstance().GetCurScene();
			if (SCENE_TYPE::DUNGEON == scene->GetSceneType())
			{
				Stage* curStage = static_cast<DungeonScene*>(scene)->GetCurStage();

				if (false == curStage->IsClear())
				{
					Map* sideMap = curStage->GetBossSideMap();

					if (nullptr != curStage && nullptr != sideMap)
					{
						EventRegisteror::GetInstance().TransitionToMap(curStage, sideMap);
					}
				}

				else
				{
					// GameClear
					//Map* nextMap = curStage->GetBossNextMap();

					//if (nullptr != curStage && nullptr != nextMap)
					//{
					//	EventRegisteror::GetInstance().TransitionToMap(curStage, nextMap);
					//}
				}

			}
		}
	}

	mPrevState = mState;
}

void BossRoomGate::Render()
{
	GameObject::Render();


	if (DOOR_STATE::OPEN == mState)
	{
		if (nullptr != mKeyTex &&
			true == mCollision)
		{
			Vec2 fKeyPos = GetPos();
			fKeyPos.y -= 110.f;

			fKeyPos = RENDER_POS(fKeyPos);
			Vec2 textureSize = mKeyTex->GetSize();

			TransparentBlt(
				BACK_BUF_DC,
				(int)(fKeyPos.x - ((textureSize.x * TIMES) / 2.f)),
				(int)(fKeyPos.y - ((textureSize.y * TIMES) / 2.f)),
				(int)(textureSize.x * TIMES),
				(int)(textureSize.y * TIMES),
				mKeyTex->GetDC(),
				0, 0,
				(int)textureSize.x,
				(int)textureSize.y,
				RGB(255, 0, 255)
			);
		}
	}
}

void BossRoomGate::Destroy()
{
	GameObject::Destroy();
}

void BossRoomGate::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = true;
	}
	
}

void BossRoomGate::OnCollisionEnter(Collider* _other)
{
}

void BossRoomGate::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = false;
	}
}
