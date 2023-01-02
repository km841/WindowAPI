#include "pch.h"
#include "DungeonMapUI.h"
#include "Texture.h"
#include "ResourceMgr.h"


DungeonMapUI::DungeonMapUI()
	:UI(false)
{
	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::DUNGEON_MAP);

	mTex = LOAD_TEXTURE(L"DungeonMap", L"Texture\\MapBase.bmp");
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"DungeonMapBase", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mBlendFunc = {};			
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 200;
}

DungeonMapUI::~DungeonMapUI()
{
}

void DungeonMapUI::Initialize()
{
}

void DungeonMapUI::Update()
{


	UI::Update();
}

void DungeonMapUI::Render()
{
	if (!GetState())
		return;
	

	if (nullptr != mBaseTex && nullptr != mTex)
	{
		Vec2 baseSize = mBaseTex->GetSize();

		AlphaBlend(BACK_BUF_DC,
			0, 0,
			(int)baseSize.x,
			(int)baseSize.y,
			mBaseTex->GetDC(),
			0, 0,
			(int)baseSize.x,
			(int)baseSize.y,
			mBlendFunc
		);


		Vec2 size = mTex->GetSize();
		TransparentBlt(
			BACK_BUF_DC,
			0, 0, 
			(int)size.x,
			(int)size.y,
			mTex->GetDC(),
			0, 0, 
			(int)size.x,
			(int)size.y,
			RGB_MAGENTA
		);
	}

	

	UI::Render();

	SetState(false);
}
