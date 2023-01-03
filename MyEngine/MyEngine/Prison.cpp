#include "pch.h"
#include "Prison.h"
#include "Map.h"
#include "BelialBossMap.h"
#include "ResourceMgr.h"
#include "Texture.h"

Prison::Prison()
	:Stage(STAGE_TYPE::PRISON)
{
	mInitPlayerPos = Vec2(TILE_SIZE * 5, GROUND_STANDARD);
	mSubBGTex = LOAD_TEXTURE(L"PrisonSubBG", L"Texture\\PrisonSubBG.bmp");
}

Prison::~Prison()
{
}

void Prison::Initialize()
{
	//AddMap(L"..\\Resource\\Map\\dungeon4.map");
	AddMap(L"..\\Resource\\Map\\Prison_StartMap_LRT.map");
	AddMap(L"..\\Resource\\Map\\Prison_Dungeon1_LR.map");
	AddMap(L"..\\Resource\\Map\\Prison_Dungeon2_RTB.map");
	AddMap(L"..\\Resource\\Map\\Prison_Dungeon3_L.map");
	AddMap(L"..\\Resource\\Map\\Prison_Dungeon4_LR.map");

	mCurMap = GetStartMap();
	// 재귀적으로 nullptr을 찾아서 조립

	SetBossSideMap(new Map(L"..\\Resource\\Map\\Prison_BossSide_R.map"));
	SetBossMap(new BelialBossMap(L"..\\Resource\\Map\\Prison_Boss_LR.map"));
	SetBossNextMap(new Map(L"..\\Resource\\Map\\Prison_BossNext_L.map"));
	
	ChainMaps(mCurMap);
	Stage::Initialize();
}

void Prison::Update()
{
	Stage::Update();
}

void Prison::Render()
{
	if (nullptr != mSubBGTex)
	{
		Vec2 bgSize = mSubBGTex->GetSize();
		TransparentBlt(
			BACK_BUF_DC,
			0, 0,
			(int)bgSize.x,
			(int)bgSize.y,
			mSubBGTex->GetDC(),
			0, 0,
			(int)bgSize.x,
			(int)bgSize.y,
			RGB_MAGENTA
		);
	}
}

void Prison::Destroy()
{
	Stage::Destroy();
}

void Prison::Enter()
{
	// 시작 맵으로 연결
	mCurMap->Enter();
}

void Prison::Exit()
{
	mCurMap->Exit();
}
