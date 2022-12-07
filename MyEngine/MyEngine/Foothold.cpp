#include "pch.h"
#include "Foothold.h"
#include "Collider.h"
#include "Tile.h"
#include "Player.h"
#include "RigidBody.h"
#include "CameraMgr.h"
#include "Monster.h"
#include "LineCollider.h"

Foothold::Foothold()
{
	SetType(OBJECT_TYPE::FOOTHOLD);
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	CreateComponent(new LineCollider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, TILE_SIZE));
}

Foothold::~Foothold()
{
}

void Foothold::Initialize()
{
	GetCollider()->SetPos(GetPos());
}

void Foothold::Update()
{

	GameObject::Update();
	
	Player* player =Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 playerTilePos = CameraMgr::GetInstance().GetTileCoord(player->GetCollider()->GetPos());
		Vec2 myTilePos = CameraMgr::GetInstance().GetTileCoord(GetPos());

		Vec2 topTilePos= Vec2(myTilePos.x, myTilePos.y - TILE_SIZE);
		if (playerTilePos == topTilePos)
		{
			mPlayerAbobeMe = true;
		}
		else
			mPlayerAbobeMe = false;
	}

}

void Foothold::Render()
{
	GameObject::Render();



}

void Foothold::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		LineCollider* collider = static_cast<LineCollider*>(GetCollider());
		Vec2 testVec = Vec2(1, 0);

		switch (collider->GetLineType())
		{
		case LINE_TYPE::FLAT:
		{
			//if (false == _other->GetOwner()->GetGround())
			//	static_cast<Player*>(_other->GetOwner())->InGround();

			if (mPlayerAbobeMe)
			{
				Vec2 pos = GetCollider()->GetPos();
				Vec2 size = GetCollider()->GetSize();

				Vec2 otherPos = _other->GetPos();
				Vec2 otherSize = _other->GetSize();

				float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);
				Vec2 objectPos = _other->GetOwner()->GetPos();
				if (diff_y > 0.f)
				{
					if (diff_y < 3.f)
						return;

					objectPos.y -= 1;
					_other->GetOwner()->SetPos(objectPos);
				}
			}

		}

			break;

		case LINE_TYPE::DEGREE_45:
		{
			Vec2 leftDot = collider->GetLeftDotPos();
			Vec2 rightDot = collider->GetRightDotPos();
			float length = (leftDot - rightDot).Len();
			
			Vec2 otherPos = _other->GetPos();
			Vec2 otherSize = _other->GetSize();
			Vec2 playerEdge = Vec2(otherPos.x + otherSize.x / 2.f, otherPos.y + otherSize.y / 2.f);

			float distance = Math::LineToDotDistance(leftDot, rightDot, playerEdge);

			Vec2 objectPos = _other->GetOwner()->GetPos();
			if (distance > 5.f)
			{
				otherPos.y -= 1;
				objectPos.y -= 1;
				_other->SetPos(otherPos);
				_other->GetOwner()->SetPos(objectPos);
			}

		}
			break;

		case LINE_TYPE::DEGREE_135:
		{
			Vec2 leftDot = collider->GetLeftDotPos();
			Vec2 rightDot = collider->GetRightDotPos();
			float length = (leftDot - rightDot).Len();


			Vec2 otherPos = _other->GetPos();
			Vec2 otherSize = _other->GetSize();
			Vec2 playerEdge = Vec2(otherPos.x - otherSize.x / 2.f, otherPos.y + otherSize.y / 2.f);

			float distance = Math::LineToDotDistance(leftDot, rightDot, playerEdge);
			Vec2 objectPos = _other->GetOwner()->GetPos();
			if (distance > 5.f)
			{
				otherPos.y -= 1;
				objectPos.y -= 1;
				_other->SetPos(otherPos);
				_other->GetOwner()->SetPos(objectPos);
			}


			//wchar_t distanceComment[COMMENT_MAX_SIZE] = {};
			//swprintf_s(distanceComment, L"distance: %f", distance);
			//TextOut(BACK_BUF_DC, 10, 130, distanceComment, (int)wcslen(distanceComment));

			//SetWindowText(APP_INSTANCE.GetHwnd(), distanceComment);

		}
			break;
		}
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		LineCollider* collider = static_cast<LineCollider*>(GetCollider());
		Vec2 testVec = Vec2(1, 0);



		switch (collider->GetLineType())
		{
		case LINE_TYPE::FLAT:
		{
			//if (false == _other->GetOwner()->GetGround())
			//	static_cast<Player*>(_other->GetOwner())->InGround();

			Vec2 pos = GetCollider()->GetPos();
			Vec2 size = GetCollider()->GetSize();

			Vec2 otherPos = _other->GetPos();
			Vec2 otherSize = _other->GetSize();

			float diff_y = (size.y / 2.f + otherSize.y / 2.f) - abs(pos.y - otherPos.y);
			Vec2 objectPos = _other->GetOwner()->GetPos();
			if (diff_y > 0.f)
			{
				if (diff_y < 3.f)
					return;

				objectPos.y -= 1;
				_other->GetOwner()->SetPos(objectPos);
			}
		}

		break;

		case LINE_TYPE::DEGREE_45:
		{
			Vec2 leftDot = collider->GetLeftDotPos();
			Vec2 rightDot = collider->GetRightDotPos();
			float length = (leftDot - rightDot).Len();

			Vec2 otherPos = _other->GetPos();
			Vec2 otherSize = _other->GetSize();
			Vec2 playerEdge = Vec2(otherPos.x + otherSize.x / 2.f, otherPos.y + otherSize.y / 2.f);

			float distance = Math::LineToDotDistance(leftDot, rightDot, playerEdge);

			Vec2 objectPos = _other->GetOwner()->GetPos();
			if (distance > 5.f)
			{
				otherPos.y -= 1;
				objectPos.y -= 1;
				_other->SetPos(otherPos);
				_other->GetOwner()->SetPos(objectPos);
			}

		}
		break;

		case LINE_TYPE::DEGREE_135:
		{
			Vec2 leftDot = collider->GetLeftDotPos();
			Vec2 rightDot = collider->GetRightDotPos();
			float length = (leftDot - rightDot).Len();


			Vec2 otherPos = _other->GetPos();
			Vec2 otherSize = _other->GetSize();
			Vec2 playerEdge = Vec2(otherPos.x - otherSize.x / 2.f, otherPos.y + otherSize.y / 2.f);

			float distance = Math::LineToDotDistance(leftDot, rightDot, playerEdge);
			Vec2 objectPos = _other->GetOwner()->GetPos();
			if (distance > 5.f)
			{
				otherPos.y -= 1;
				objectPos.y -= 1;
				_other->SetPos(otherPos);
				_other->GetOwner()->SetPos(objectPos);
			}


			//wchar_t distanceComment[COMMENT_MAX_SIZE] = {};
			//swprintf_s(distanceComment, L"distance: %f", distance);
			//TextOut(BACK_BUF_DC, 10, 130, distanceComment, (int)wcslen(distanceComment));

			//SetWindowText(APP_INSTANCE.GetHwnd(), distanceComment);

		}
		break;
		}
	}
}

void Foothold::OnCollisionEnter(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		Player* player = Player::GetPlayer();
	/*	player->InGround();*/
		player->SetCollisionType(COLLISION_TYPE::LINE);

		LineCollider* collider = static_cast<LineCollider*>(GetCollider());
		Vec2 dirVec = Vec2(1, 0);

		if (player->NotInDash())
		{
			if (LINE_TYPE::FLAT == collider->GetLineType())
			{
				if (mPlayerAbobeMe)
					player->InGround();
			}
			else
			{
				player->InGround();
			}
		}

		switch (collider->GetLineType())
		{
		case LINE_TYPE::DEGREE_45:
			dirVec = Math::RotateVector(dirVec, Math::DegreeToRadian(360.f - 46.f));
			break;

		case LINE_TYPE::DEGREE_135:
			dirVec = Math::RotateVector(dirVec, Math::DegreeToRadian(46.f));
			break;
		}
		
		Vec2 otherPos = _other->GetPos();
		player->SetDirectionVector(dirVec);
	}

	if (OBJECT_TYPE::MONSTER == _other->GetOwner()->GetType())
	{
		static_cast<Monster*>(_other->GetOwner())->SetGround(true);
	}
}

void Foothold::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		//Player::GetPlayer()->SetDirectionVector(ZERO_VECTOR);
		//Player::GetPlayer()->SetCollisionType(COLLISION_TYPE::NONE);
	}
}
