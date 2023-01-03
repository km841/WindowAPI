#include "pch.h"
#include "DungeonMapUI.h"
#include "Texture.h"
#include "ResourceMgr.h"


DungeonMapUI::DungeonMapUI()
	:UI(false)
	, mInfoTex(nullptr)
	, mTex(nullptr)
	, mBaseTex(nullptr)
{
	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::DUNGEON_MAP);

	mTex = LOAD_TEXTURE(L"DungeonMap", L"Texture\\MapBase.bmp");
	mInfoTex = LOAD_TEXTURE(L"DungeonMapInfo", L"Texture\\DungeonMapInfo.bmp");
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
	// DungeonMap은 Stage와 연동해서 맵 정보를 가지고 있어야 한다.
	// 현재 맵에 정보를 가져와서 맵에 표시해주고 Clear가 된 맵도 표시가 되어야 한다.
	// 맵에 비밀통로 오브젝트도 인식하여야 함
	// 비밀통로 오브젝트는 따로 ui로 만들어야 함
	// DungeonMap->Stage에서 Map을 가져와서 Clear한 맵들만 그려줌 -> Clear한 맵 중에 비밀통로가 있는 경우
	// 해당 위치에 비밀통로 UI를 삽입함
	// 비밀통로 UI도 자신을 소유한 맵의 정보를 가지고 있기 때문에
	// 비밀통로가 클릭되면 해당 오브젝트 현재 맵의 Exit-> 이동된 맵의 Enter를 거쳐 해당 오브젝트의 위치로 순간이동한다.
	// 그럼 Map은 IsSecretPassage 함수를 통해 비밀통로 여부를 반환해야 함
	// 맵이 로드된 후 해당 오브젝트 여부에 따라 불값을 세팅하고,
	// 그게 체크되어 있으면 해당 맵에 마크를 띄워준다.
	// ChildUI로 UnitMap을 가지고 있는다.
	// 


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

		if (nullptr != mInfoTex)
		{
			Vec2 infoOrgSize = mInfoTex->GetSize();
			Vec2 infoSize = (infoOrgSize / 5.f) * 4.f;

			TransparentBlt(
				BACK_BUF_DC,
				150, 600,
				infoSize.x,
				infoSize.y,
				mInfoTex->GetDC(),
				0, 0,
				infoOrgSize.x,
				infoOrgSize.y,
				RGB_MAGENTA
			);
		}




	}

	

	UI::Render();

	SetState(false);
}
