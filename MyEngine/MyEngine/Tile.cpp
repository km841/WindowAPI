#include "pch.h"
#include "Tile.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"

Tile::Tile()
{
	SetSize(Vec2(TILE_SIZE, TILE_SIZE));
	SetType(OBJECT_TYPE::TILE);
}

Tile::~Tile()
{

}

void Tile::Initialize()
{
}

void Tile::Update()
{
}

void Tile::Render()
{
	static Texture* mTex = 
		ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map.bmp");

	Vec2 pos = RENDER_POS(GetPos());

	TransparentBlt(
		BACK_BUF_DC,
		(int)pos.x,
		(int)pos.y,
		TILE_SIZE,
		TILE_SIZE,
		mTex->GetDC(),
		(int)mTileLT.x,
		(int)mTileLT.y,
		IMAGE_TILE_SIZE,
		IMAGE_TILE_SIZE,
		RGB(255, 0, 255)
	);
}

void Tile::Destroy()
{
}

void Tile::Save(FILE* _fp) const
{
	Vec2 pos = GetPos();
	Vec2 ltPos = GetLTPos();
	
	fwrite(&pos, sizeof(Vec2), 1, _fp);
	fwrite(&ltPos, sizeof(Vec2), 1, _fp);
}

void Tile::Load(FILE* _fp)
{
	Vec2 pos;
	Vec2 ltPos;

	fread(&pos, sizeof(Vec2), 1, _fp);
	fread(&ltPos, sizeof(Vec2), 1, _fp);

	SetPos(pos);
	SetLTPos(ltPos);
}

