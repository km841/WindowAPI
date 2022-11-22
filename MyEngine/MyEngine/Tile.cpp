#include "pch.h"
#include "Tile.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "Wall.h"
#include "Foothold.h"
#include "Collider.h"

Tile::Tile()
{
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	SetType(OBJECT_TYPE::TILE);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
	GetCollider()->SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	//GetCollider()->SetOffset(Vec2(TILE_SIZE / 2.f, TILE_SIZE / 2.f));
	
	
}

Tile::~Tile()
{
	if (nullptr != mCollisionComponent)
	{
		delete mCollisionComponent;
		mCollisionComponent = nullptr;
	}
}

void Tile::Initialize()
{
	GetCollider()->SetPos(GetPos());
	GetCollider()->SetSize(GetSize());
}

void Tile::Update()
{
	if (nullptr != mCollisionComponent)
	{
		mCollisionComponent->Update();
	}

	GameObject::Update();
}

void Tile::Render()
{
	static Texture* mTex = 
		ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map.bmp");

	Vec2 pos = GetPos();
	// �� ��ġ�� ī�޶󿡼� �Ⱥ��̸� ����X
	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 ltPos = CameraMgr::GetInstance().GetLookPos() - (resolution / 2.f);

	// ������ ����ȭ
	if (pos.x < ltPos.x - TILE_SIZE || pos.x >= (ltPos.x + resolution.x) ||
		pos.y < ltPos.y - TILE_SIZE || pos.y >= (ltPos.y + resolution.y))
	{
		return;
	}
	
	Vec2 renderPos = RENDER_POS(pos);
	TransparentBlt(
		BACK_BUF_DC,
		(int)renderPos.x - TILE_SIZE / 2.f,
		(int)renderPos.y - TILE_SIZE / 2.f,
		TILE_SIZE,
		TILE_SIZE,
		mTex->GetDC(),
		(int)mTileLT.x,
		(int)mTileLT.y,
		IMAGE_TILE_SIZE_X,
		IMAGE_TILE_SIZE_Y,
		RGB(255, 0, 255)
	);

	if (nullptr != mCollisionComponent)
	{
		mCollisionComponent->Render();
	}

	//GameObject::Render();
}

void Tile::Destroy()
{
}

void Tile::Save(FILE* _fp) const
{
	Vec2 pos = GetPos();
	Vec2 ltPos = GetLTPos();
	TILE_TYPE tileType = GetTileType();
	
	fwrite(&pos, sizeof(Vec2), 1, _fp);
	fwrite(&ltPos, sizeof(Vec2), 1, _fp);
	fwrite(&tileType, sizeof(TILE_TYPE), 1, _fp);
}

void Tile::Load(FILE* _fp)
{
	Vec2 pos;
	Vec2 ltPos;
	TILE_TYPE tileType;

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
		CreateFoothold();
		break;
	}

	Initialize();
}

void Tile::CreateWall()
{
	mCollisionComponent = new Wall;
	mCollisionComponent->SetOwner(this);
}

void Tile::CreateFoothold()
{
	mCollisionComponent = new Foothold;
	mCollisionComponent->SetOwner(this);
}

void Tile::OnCollision(Collider* _other)
{
	if (nullptr != mCollisionComponent)
		mCollisionComponent->GetCollider()->OnCollision(_other);
}

void Tile::OnCollisionEnter(Collider* _other)
{

	if (nullptr != mCollisionComponent)
		mCollisionComponent->GetCollider()->OnCollisionEnter(_other);
	
}

void Tile::OnCollisionExit(Collider* _other)
{
	if (nullptr != mCollisionComponent)
		mCollisionComponent->GetCollider()->OnCollisionExit(_other);
}

