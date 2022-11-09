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

	Vec2 pos = GetPos();
	// 내 위치가 카메라에서 안보이면 렌더X
	Vec2 resolution = APP_INSTANCE.GetResolution();
	Vec2 ltPos = CameraMgr::GetInstance().GetLookPos() - (resolution / 2.f);

	// 렌더링 최적화
	if (pos.x < ltPos.x - TILE_SIZE || pos.x >= (ltPos.x + resolution.x) ||
		pos.y < ltPos.y - TILE_SIZE || pos.y >= (ltPos.y + resolution.y))
	{
		return;
	}
	
	Vec2 renderPos = RENDER_POS(pos);
	TransparentBlt(
		BACK_BUF_DC,
		(int)renderPos.x,
		(int)renderPos.y,
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

