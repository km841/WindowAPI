#include "pch.h"
#include "DungeonMapUI.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "DungeonScene.h"
#include "Map.h"


DungeonMapUI::DungeonMapUI()
	: UI(false)
	, mInfoTex(nullptr)
	, mTex(nullptr)
	, mBaseTex(nullptr)
	, mUnitMapTex(nullptr)
	, mUnitMapLightTex(nullptr)
	, mFloorInfoTex(nullptr)
{
	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::DUNGEON_MAP);

	mTex = LOAD_TEXTURE(L"DungeonMap", L"Texture\\MapBase.bmp");
	mInfoTex = LOAD_TEXTURE(L"DungeonMapInfo", L"Texture\\DungeonMapInfo.bmp");
	mUnitMapTex = LOAD_TEXTURE(L"UnitMap", L"Texture\\CleanUnitMap.bmp");
	mUnitMapLightTex = LOAD_TEXTURE(L"UnitMapLight", L"Texture\\CleanUnitMapLight.bmp");
	mFloorInfoTex = LOAD_TEXTURE(L"FloorInfo", L"Texture\\FloorInfo.bmp");
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"DungeonMapBase", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mBlendFunc = {};			
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = 0;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 200;

	mCenterPos = Vec2(WINDOW_WIDTH_SIZE / 2, WINDOW_HEIGHT_SIZE / 2);
	mCenterPos.x += 0;
	mCenterPos.y += 50;
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

		if (nullptr != mInfoTex)
		{
			Vec2 infoOrgSize = mInfoTex->GetSize();
			Vec2 infoSize = (infoOrgSize / 5.f) * 4.f;

			TransparentBlt(
				BACK_BUF_DC,
				150, 640,
				(int)infoSize.x,
				(int)infoSize.y,
				mInfoTex->GetDC(),
				0, 0,
				(int)infoOrgSize.x,
				(int)infoOrgSize.y,
				RGB_MAGENTA
			);
		}

		if (nullptr != mFloorInfoTex)
		{
			Vec2 infoOrgSize = mFloorInfoTex->GetSize();
			Vec2 infoSize = infoOrgSize / 2.f;

			TransparentBlt(
				BACK_BUF_DC,
				580, 640,
				(int)infoSize.x,
				(int)infoSize.y,
				mFloorInfoTex->GetDC(),
				0, 0,
				(int)infoOrgSize.x,
				(int)infoOrgSize.y,
				RGB_MAGENTA
			);
		}

		if (nullptr != mUnitMapTex)
		{
			Vec2 unitMapSize = mUnitMapTex->GetSize();

			Scene* scene = SceneMgr::GetInstance().GetCurScene();
			DungeonScene* dungeonScene = nullptr;
			if (nullptr != scene &&
				SCENE_TYPE::DUNGEON == scene->GetSceneType())
			{
				dungeonScene = static_cast<DungeonScene*>(scene);

				Stage* curStage = dungeonScene->GetCurStage();
				if (nullptr != curStage)
				{
					Map* curMap = curStage->GetCurMap();
					mVisited.push_back(curMap);

					if (nullptr != curMap)
					{
						
						TransparentBlt(
							BACK_BUF_DC,
							(int)(mCenterPos.x - unitMapSize.x / 2.f),
							(int)(mCenterPos.y - unitMapSize.y / 2.f),
							(int)(unitMapSize.x),
							(int)(unitMapSize.y),
							mUnitMapLightTex->GetDC(),
							0, 0,
							(int)unitMapSize.x,
							(int)unitMapSize.y,
							RGB_MAGENTA
						);
						

					}


					for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
					{
						Map* nextMap = curMap->GetMapLink((WARP_POINT)i);
						bool isPassage = curMap->IsPassage((WARP_POINT)i);
						Vec2 centerPos = mCenterPos;

						if (nullptr != nextMap)
						{
							switch ((WARP_POINT)i)
							{
							case WARP_POINT::LEFT:
								centerPos.x -= unitMapSize.x;
								break;

							case WARP_POINT::RIGHT:
								centerPos.x += unitMapSize.x;
								break;

							case WARP_POINT::TOP:
								centerPos.y -= unitMapSize.y;
								break;

							case WARP_POINT::BOTTOM:
								centerPos.y += unitMapSize.y;
								break;
							}

							DrawUnitMap(nextMap, centerPos);
						}

						if (true == isPassage)
						{
							switch ((WARP_POINT)i)
							{
							case WARP_POINT::LEFT:
							{
								Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
								Rectangle(
									BACK_BUF_DC,
									(int)(mCenterPos.x - unitMapSize.x / 2.f - 10.f),
									(int)(mCenterPos.y - 2.f),
									(int)(mCenterPos.x - unitMapSize.x / 2.f + 10.f),
									(int)(mCenterPos.y + 2.f)
								);
							}
							break;

							case WARP_POINT::RIGHT:
							{

								Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
								Rectangle(
									BACK_BUF_DC,
									(int)(mCenterPos.x + unitMapSize.x / 2.f - 10.f),
									(int)(mCenterPos.y - 2.f),
									(int)(mCenterPos.x + unitMapSize.x / 2.f + 10.f),
									(int)(mCenterPos.y + 2.f)
								);

							}
							break;

							case WARP_POINT::TOP:
							{
								Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
								Rectangle(
									BACK_BUF_DC,
									(int)(mCenterPos.x - 2.f),
									(int)(mCenterPos.y - unitMapSize.y / 2.f - 10.f),
									(int)(mCenterPos.x + 2.f),
									(int)(mCenterPos.y - unitMapSize.y / 2.f + 10.f)
								);

							}
							break;

							case WARP_POINT::BOTTOM:
							{
								Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
								Rectangle(
									BACK_BUF_DC,
									(int)(mCenterPos.x - 2.f),
									(int)(mCenterPos.y + unitMapSize.y / 2.f - 10.f),
									(int)(mCenterPos.x + 2.f),
									(int)(mCenterPos.y + unitMapSize.y / 2.f + 10.f)
								);

							}
							break;
							}

						}
						
	
					}

					mVisited.clear();
				}


			}
		}
	}

	

	UI::Render();

	//SetState(false);
}

void DungeonMapUI::DrawUnitMap(Map* _curMap, Vec2 _drawPos)
{
	if (nullptr == _curMap)
		return;

	if (false == _curMap->IsClear())
		return;

	if (mVisited.end() != std::find(mVisited.begin(), mVisited.end(), _curMap))
		return;

	mVisited.push_back(_curMap);

	

	Vec2 unitMapSize = mUnitMapTex->GetSize();
	

	if (nullptr != _curMap)
	{
		TransparentBlt(
			BACK_BUF_DC,
			(int)(_drawPos.x - unitMapSize.x / 2.f),
			(int)(_drawPos.y - unitMapSize.y / 2.f),
			(int)(unitMapSize.x),
			(int)(unitMapSize.y),
			mUnitMapTex->GetDC(),
			0, 0,
			(int)unitMapSize.x,
			(int)unitMapSize.y,
			RGB_MAGENTA
		);
		
	}		

	for (int i = 0; i < (UINT)WARP_POINT::END; ++i)
	{
		Map* nextMap = _curMap->GetMapLink((WARP_POINT)i);
		bool isPassage = _curMap->IsPassage((WARP_POINT)i);

		if (nullptr != nextMap)
		{
			switch ((WARP_POINT)i)
			{
			case WARP_POINT::LEFT:
			{
				Vec2 mapPos = Vec2(_drawPos.x - unitMapSize.x, _drawPos.y);
				DrawUnitMap(nextMap, mapPos);
			}
				break;

			case WARP_POINT::RIGHT:
			{
				Vec2 mapPos = Vec2(_drawPos.x + unitMapSize.x, _drawPos.y);
				DrawUnitMap(nextMap, mapPos);
			}			
				break;

			case WARP_POINT::TOP:
			{
				Vec2 mapPos = Vec2(_drawPos.x, _drawPos.y - unitMapSize.y);
				DrawUnitMap(nextMap, mapPos);
			}
				break;

			case WARP_POINT::BOTTOM:
			{
				Vec2 mapPos = Vec2(_drawPos.x, _drawPos.y + unitMapSize.y);
				DrawUnitMap(nextMap, mapPos);
			}
				break;
			}
		}


		if (true == isPassage)
		{
			switch ((WARP_POINT)i)
			{
			case WARP_POINT::LEFT:
			{
				Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
				Rectangle(
					BACK_BUF_DC,
					(int)(_drawPos.x - unitMapSize.x / 2.f - 10.f),
					(int)(_drawPos.y - 2.f),
					(int)(_drawPos.x - unitMapSize.x / 2.f + 10.f),
					(int)(_drawPos.y + 2.f)
				);
			}
			break;

			case WARP_POINT::RIGHT:
			{

				Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
				Rectangle(
					BACK_BUF_DC,
					(int)(_drawPos.x + unitMapSize.x / 2.f - 10.f),
					(int)(_drawPos.y - 2.f),
					(int)(_drawPos.x + unitMapSize.x / 2.f + 10.f),
					(int)(_drawPos.y + 2.f)
				);

			}
			break;

			case WARP_POINT::TOP:
			{
				Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
				Rectangle(
					BACK_BUF_DC,
					(int)(_drawPos.x - 2.f),
					(int)(_drawPos.y - unitMapSize.y / 2.f - 10.f),
					(int)(_drawPos.x + 2.f),
					(int)(_drawPos.y - unitMapSize.y / 2.f + 10.f)
				);

			}
			break;

			case WARP_POINT::BOTTOM:
			{
				Pen pen(BACK_BUF_DC, PEN_TYPE::WHITE);
				Rectangle(
					BACK_BUF_DC,
					(int)(_drawPos.x - 2.f),
					(int)(_drawPos.y + unitMapSize.y / 2.f - 10.f),
					(int)(_drawPos.x + 2.f),
					(int)(_drawPos.y + unitMapSize.y / 2.f + 10.f)
				);

			}
			break;
			}

		}

	}


}
