#include "pch.h"
#include "SnowMountain.h"
#include "Map.h"

SnowMountain::SnowMountain()
	:Stage(STAGE_TYPE::SNOW_MOUNTAIN)
{
	mInitPlayerPos = Vec2(TILE_SIZE * 5, GROUND_STANDARD);
}

SnowMountain::~SnowMountain()
{
}

void SnowMountain::Initialize()
{
	AddMap(L"..\\Resource\\Map\\start_map_TR.map");


	mCurMap = GetStartMap();

	Stage::Initialize();
}

void SnowMountain::Update()
{
	Stage::Update();
}

void SnowMountain::Render()
{
	// ´«¹ß ³¯¸®±â
}

void SnowMountain::Destroy()
{
	Stage::Destroy();
}

void SnowMountain::Enter()
{
	mCurMap->Enter();
}

void SnowMountain::Exit()
{
	mCurMap->Exit();
}
