#include "pch.h"
#include "DungeonEatEvent.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "Player.h"
#include "Collider.h"
#include "ResourceMgr.h"
#include "EatState.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"

DungeonEatEvent::DungeonEatEvent()
	:mFixPos{}
{

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* dungeonEatTex =
		ResourceMgr::GetInstance().Load<Texture>(L"DUNGEON_EAT_ANIMATION", L"Texture\\dungeon_eat_animation.bmp");

	GetAnimator()->RegisterAnimation(
		L"DUNGEON_EAT_ANIM",
		dungeonEatTex,
		Vec2(0.f, 0.f),
		Vec2(351.f, 255.f),
		Vec2(351.f, 0.f),
		0.06f,
		28
	);

	SetSize(Vec2(351, 255));
}

DungeonEatEvent::~DungeonEatEvent()
{
}

void DungeonEatEvent::Initialize()
{
}

void DungeonEatEvent::Update()
{
	EventObject::Update();

	if (Vec2(0.f, 0.f) != GetFixPos())
		Player::GetPlayer()->SetPos(GetFixPos());
}

void DungeonEatEvent::Render()
{
	EventObject::Render();
}

void DungeonEatEvent::Destroy()
{
}

void DungeonEatEvent::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		int frame = GetAnimator()->GetCurAnimation()->GetCurFrame();

		if (9 == frame)
		{
			Player* player = Player::GetPlayer();
			if (nullptr != player)
			{
				player->SetState(PlayerState::Eat);
				player->AnimationUpdate();
			}
		}

		if (25 == frame)
		{
			if (!(CameraMgr::GetInstance().IsEffectProgress()))
			{
				CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_OUT, 1.5f);
				EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::DUNGEON1);
				SetFixPos(Vec2(0.f, 0.f));
			}
		}
	}
}

void DungeonEatEvent::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		GetAnimator()->SelectAnimation(L"DUNGEON_EAT_ANIM", false);
		SetFixPos(Player::GetPlayer()->GetPos());
	}
}

void DungeonEatEvent::OnCollisionExit(Collider* _other)
{
}
