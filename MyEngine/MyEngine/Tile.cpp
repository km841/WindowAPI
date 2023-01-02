#include "pch.h"
#include "Tile.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "Wall.h"
#include "Foothold.h"
#include "Collider.h"
#include "EventRegisteror.h"
#include "LineCollider.h"

Tile::Tile()
	: mTileLT{}
	, mTileType{}
	, mCollisionComponent{}
{
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	SetType(OBJECT_TYPE::TILE);	
}

Tile::~Tile()
{

}

Tile::Tile(Tile&& _other)
	: mCollisionComponent(_other.mCollisionComponent)
	, mTileType(_other.mTileType)
	, mTileLT(_other.mTileLT)
	, GameObject(std::move(_other))
{
	_other.mCollisionComponent = nullptr;
	
}

void Tile::Initialize()
{
	if (nullptr != mCollisionComponent)
	{
		EventRegisteror::GetInstance().CreateObject(mCollisionComponent, mCollisionComponent->GetType());
	}
}

void Tile::Update()
{
	GameObject::Update();
}

void Tile::Render()
{
	static Texture* mTex = 
		LOAD_TEXTURE(L"TileMap", L"Texture\\Map.bmp");

	Vec2 pos = GetPos();
	// 내 위치가 카메라에서 안보이면 렌더X
	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 ltPos = CameraMgr::GetInstance().GetLookPos() - (resolution / 2.f);

	// 렌더링 최적화
	if (pos.x < ltPos.x - TILE_SIZE || pos.x >= (ltPos.x + resolution.x) + TILE_SIZE ||
		pos.y < ltPos.y - TILE_SIZE || pos.y >= (ltPos.y + resolution.y) + TILE_SIZE)
	{
		return;
	}
	
	Vec2 renderPos = RENDER_POS(pos);
	TransparentBlt(
		BACK_BUF_DC,
		(int)(renderPos.x - TILE_SIZE / 2.f),
		(int)(renderPos.y - TILE_SIZE / 2.f),
		TILE_SIZE,
		TILE_SIZE,
		mTex->GetDC(),
		(int)mTileLT.x,
		(int)mTileLT.y,
		IMAGE_TILE_SIZE_X,
		IMAGE_TILE_SIZE_Y,
		RGB(255, 0, 255)
	);

	GameObject::Render();
}

void Tile::Destroy()
{
	if (nullptr != mCollisionComponent)
	{
		delete mCollisionComponent;
		mCollisionComponent = nullptr;
	}
}

void Tile::Save(FILE* _fp) const
{
	Vec2 pos = GetPos();
	Vec2 ltPos = GetLTPos();
	TILE_TYPE tileType = GetTileType();
	
	fwrite(&pos, sizeof(Vec2), 1, _fp);
	fwrite(&ltPos, sizeof(Vec2), 1, _fp);
	fwrite(&tileType, sizeof(TILE_TYPE), 1, _fp);

	if (TILE_TYPE::FOOTHOLD == tileType)
	{
		LINE_TYPE lineType = static_cast<LineCollider*>(GetCollisionComponent()->GetCollider())->GetLineType();
		fwrite(&lineType, sizeof(lineType), 1, _fp);
	}
}

void Tile::Load(FILE* _fp)
{
	Vec2 pos;
	Vec2 ltPos;
	TILE_TYPE tileType;
	LINE_TYPE lineType;

	fread(&pos, sizeof(Vec2), 1, _fp);
	fread(&ltPos, sizeof(Vec2), 1, _fp);
	fread(&tileType, sizeof(TILE_TYPE), 1, _fp);

	SetPos(pos);
	SetLTPos(ltPos);
	SetTileType(tileType);

	switch (tileType)
	{
	case TILE_TYPE::WALL:
		CreateWall();
		break;
	case TILE_TYPE::FOOTHOLD:
	{
		fread(&lineType, sizeof(LINE_TYPE), 1, _fp);
		CreateFoothold();
		static_cast<LineCollider*>(GetCollisionComponent()->GetCollider())->SetLineType(lineType);
	}
		break;
	}

	Initialize();
}

void Tile::CreateWall()
{
	mCollisionComponent = new Wall;
	mCollisionComponent->SetPos(GetPos());
	//mCollisionComponent->SetOwner(this);
}

void Tile::CreateFoothold()
{
	mCollisionComponent = new Foothold;
	mCollisionComponent->SetPos(GetPos());
	//mCollisionComponent->SetOwner(this);
}

void Tile::OnCollision(Collider* _other)
{

}

void Tile::OnCollisionEnter(Collider* _other)
{
	
}

void Tile::OnCollisionExit(Collider* _other)
{

}

