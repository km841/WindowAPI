#include "pch.h"
#include "MinimapHUD.h"
#include "Texture.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "Player.h"
#include "LockedDoor.h"

MinimapHUD::MinimapHUD()
{
	mTex = ResourceMgr::GetInstance().CreateTexture(L"MinimapHUD", Vec2(300, 200));

	mMinimapSize = mTex->GetSize();
	SetPos(Vec2(WINDOW_WIDTH_SIZE - mMinimapSize.x, 0.f));

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;
}

MinimapHUD::~MinimapHUD()
{
}

void MinimapHUD::Initialize()
{
	HUD::Initialize();
}

void MinimapHUD::Update()
{
	HUD::Update();



}

void MinimapHUD::Render()
{
	if (GetState() && nullptr != mTex)
	{
		HUD::Render();
		Vec2 pos = GetPos();
		Vec2 size = mTex->GetSize();

		AlphaBlend(
			BACK_BUF_DC,
			(int)pos.x,
			(int)pos.y,
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			mBlendFunc
		);

		RECT limitSize = CameraMgr::GetInstance().GetCameraLimitRect();

		NPCRender(limitSize);
		TileRender(limitSize);
		MonsterRender(limitSize);
		DungeonObjectRender(limitSize);
		PlayerRender(limitSize);
	}
}

void MinimapHUD::Destroy()
{
	HUD::Destroy();
}

void MinimapHUD::MonsterRender(RECT _limitSize)
{
	Vec2 pos = GetPos();
	const std::vector<GameObject*> monsterGroup = SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::MONSTER);
	for (const auto& monster : monsterGroup)
	{
		Vec2 monsterPos = monster->GetPos();
		Vec2 minimapPos = pos + GetMinimapPos(_limitSize, monsterPos);

		if (monster->IsAlive())
		{
			Brush brush(BACK_BUF_DC, BRUSH_TYPE::RED);
			Pen pen(BACK_BUF_DC, PEN_TYPE::BLACK);
			Rectangle(BACK_BUF_DC,
				(int)(minimapPos.x),
				(int)(minimapPos.y - 11),
				(int)(minimapPos.x + 13),
				(int)(minimapPos.y + 2));
		}
	}
}

void MinimapHUD::TileRender(RECT _limitSize)
{
	Vec2 pos = GetPos();
	const std::vector<GameObject*> tileGroup = SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::TILE);
	for (const auto& tile : tileGroup)
	{
		Vec2 tilePos = tile->GetPos();
		Vec2 minimapPos = pos + GetMinimapPos(_limitSize, tilePos);

		Brush brush(BACK_BUF_DC, BRUSH_TYPE::WHITE);
		Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);

		Rectangle(BACK_BUF_DC,
			(int)(minimapPos.x),
			(int)(minimapPos.y),
			(int)(minimapPos.x + 13),
			(int)(minimapPos.y + 13));
	}
}

void MinimapHUD::NPCRender(RECT _limitSize)
{
	Vec2 pos = GetPos();
	const std::vector<GameObject*> npcGroup = SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::NPC);

	for (const auto& npc : npcGroup)
	{
		Vec2 npcPos = npc->GetPos();
		Vec2 minimapPos = pos + GetMinimapPos(_limitSize, npcPos);

		Brush brush(BACK_BUF_DC, BRUSH_TYPE::YELLOW);
		Pen pen(BACK_BUF_DC, PEN_TYPE::BLACK);

		Rectangle(BACK_BUF_DC,
			(int)(minimapPos.x),
			(int)(minimapPos.y - 11),
			(int)(minimapPos.x + 13),
			(int)(minimapPos.y + 2));
	}
}

void MinimapHUD::PlayerRender(RECT _limitSize)
{
	Vec2 pos = GetPos();
	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		Vec2 minimapPos = pos + GetMinimapPos(_limitSize, playerPos);

		Brush brush(BACK_BUF_DC, BRUSH_TYPE::BLUE);
		Pen pen(BACK_BUF_DC, PEN_TYPE::BLACK);
		Rectangle(BACK_BUF_DC,
			(int)(minimapPos.x),
			(int)(minimapPos.y - 11),
			(int)(minimapPos.x + 13),
			(int)(minimapPos.y + 2));

	}
}

void MinimapHUD::DungeonObjectRender(RECT _limitSize)
{
	Vec2 pos = GetPos();
	const std::vector<GameObject*> dungeonObjGroup = SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::DUNGEON_OBJECT);
	for (const auto& dungeonObj : dungeonObjGroup)
	{
		Vec2 dungeonObjPos = dungeonObj->GetPos();
		Vec2 minimapPos = pos + GetMinimapPos(_limitSize, dungeonObjPos);

		if (TOOL_ID::BTN_DOOR_0DEG == dungeonObj->GetToolID() ||
			TOOL_ID::BTN_DOOR_90DEG == dungeonObj->GetToolID() ||
			TOOL_ID::BTN_DOOR_180DEG == dungeonObj->GetToolID() ||
			TOOL_ID::BTN_DOOR_270DEG == dungeonObj->GetToolID())
		{
			ANGLE_TYPE angleType = static_cast<LockedDoor*>(dungeonObj)->GetAngleType();

			Brush brush(BACK_BUF_DC, BRUSH_TYPE::GREEN);
			Pen pen(BACK_BUF_DC, PEN_TYPE::NULL_COLOR);

			switch (angleType)
			{
			case ANGLE_TYPE::DEGREE_0_TYPE:
				Rectangle(BACK_BUF_DC,
					(int)(minimapPos.x - 6),
					(int)(minimapPos.y + 3),
					(int)(minimapPos.x + 23),
					(int)(minimapPos.y + 14));
				break;

			case ANGLE_TYPE::DEGREE_90_TYPE:
				Rectangle(BACK_BUF_DC,
					(int)(minimapPos.x - 6),
					(int)(minimapPos.y - 9),
					(int)(minimapPos.x + 8),
					(int)(minimapPos.y + 23));
				break;

			case ANGLE_TYPE::DEGREE_270_TYPE:
				Rectangle(BACK_BUF_DC,
					(int)(minimapPos.x - 6),
					(int)(minimapPos.y - 9),
					(int)(minimapPos.x + 8),
					(int)(minimapPos.y + 23));
				break;

			}
		}



	}
}

Vec2 MinimapHUD::GetMinimapPos(RECT _limitRect, Vec2 _targetPos)
{
	int width = _limitRect.right;
	int height = _limitRect.bottom;

	// limitRect에서 targetPos가 위치한 위치는 n%, n%이다.
	// 따라서 그걸 minimap을 기준으로 %를 구하면 된다.

	float ratio_x = _targetPos.x / width;
	float ratio_y = _targetPos.y / height;
	
	int minimap_pos_x = (int)(mMinimapSize.x * ratio_x);
	int minimap_pos_y = (int)(mMinimapSize.y * ratio_y);

	return Vec2(minimap_pos_x, minimap_pos_y);
}
