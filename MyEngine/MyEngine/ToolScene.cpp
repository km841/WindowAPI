#include "pch.h"
#include "ToolScene.h"
#include "ResourceMgr.h"
#include "ToolUI.h"
#include "Texture.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "IconUI.h"
#include "MouseMgr.h"
#include "Tile.h"
#include "CheckButtonUI.h"
#include "KeyMgr.h"
#include "Wall.h"
#include "Foothold.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "LineCollider.h"

ToolScene::ToolScene()
	: mCheckedObjectType(OBJECT_TYPE::TILE_BG)
	, mCheckedTileType(TILE_TYPE::NONE)
{
	mSceneType = SCENE_TYPE::TOOL;
}

ToolScene::~ToolScene()
{
}

void ToolScene::Initialize()
{
	mDefaultTexture = ResourceMgr::GetInstance().Load<Texture>(L"TileMap", L"Texture\\Map3.bmp");
	assert(mDefaultTexture);

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;

	Scene::Initialize();
}

void ToolScene::Update()
{
	if (OBJECT_TYPE::TILE_BG == mCheckedObjectType)
	{
		mCheckedTileType = TILE_TYPE::NONE;
		CheckMenuRadioItem(APP_INSTANCE.GetColMenuHandle(), 0, 2, 2, MF_BYPOSITION);
	}

	IconUI* selectedUI = IconUI::GetSelectedUI();
	Vec2 mousePos = WORLD_POS(MOUSE_POS);
	Vec2 tilePos = CameraMgr::GetInstance().GetTileCoord(mousePos);


	if ((tilePos.y >= 0.f && tilePos.x >= 0.f) && (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)) &&
		(MOUSE_POS.x > 50.f && MOUSE_POS.y > 50.f))
	{
		if (CheckButtonUI::GetCheckedButton()->GetIndex())
		{
			if (IS_JUST_LBUTTON_CLICKED)
			{
				// 여기서 타입에 따라 갈려야 하나?
				OBJECT_TYPE tileObjType = mCheckedObjectType;

				const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileObjType);
				Tile* tile = nullptr;

				// 해당 위치에 타일이 있는지 검사
				for (int i = 0; i < tileGroup.size(); ++i)
				{
					if (tileGroup[i]->GetPos() == tilePos + TILE_OFFSET)
					{
						tile = static_cast<Tile*>(tileGroup[i]);
						break;
					}
				}

				if (nullptr == tile)
				{
					// 타일이 없는 자리의 경우

					if (nullptr != selectedUI)
					{
						tile = new Tile;
						tile->SetPos(tilePos + Vec2(TILE_SIZE / 2.f, TILE_SIZE / 2.f));
						tile->SetLTPos(selectedUI->GetLTPos());

						TILE_TYPE tileType = mCheckedTileType;
						switch (tileType)
						{
						case TILE_TYPE::WALL:
						{
							tile->CreateWall();
							tile->SetTileType(tileType);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
						}
						break;
						case TILE_TYPE::FOOTHOLD:
						{
							tile->CreateFoothold();
							tile->SetTileType(tileType);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
						}
						break;
						case TILE_TYPE::NONE:
							tile->SetTileType(tileType);
							tile->SetType(OBJECT_TYPE::TILE_BG);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE_BG);
							break;
						}


					}

				}

				else
				{
					// LT Pos가 기존에 있는 것과 내가 선택한게 같다면 Return
					if (nullptr != selectedUI)
					{
						if (selectedUI->GetLTPos() == tile->GetLTPos())
							return;
					}

					// 타일이 있는 자리의 경우

					// 타일이 가진 컴포넌트가 있다면
					CollisionComponent* tileComponent = tile->GetCollisionComponent();

					if (nullptr != tileComponent)
					{
						// 내 위치와 같은 Wall과 Foothold를 지워줘야 한다

						OBJECT_TYPE type = tileComponent->GetType();


						if (OBJECT_TYPE::FOOTHOLD == type && TILE_TYPE::FOOTHOLD == mCheckedTileType ||
							nullptr != selectedUI && TILE_TYPE::FOOTHOLD == mCheckedTileType)
						{
							static_cast<LineCollider*>(tile->GetCollisionComponent()->GetCollider())->SetNextLineType();
							return;
						}

						if (OBJECT_TYPE::FOOTHOLD == type ||
							OBJECT_TYPE::WALL == type)
						{
							//해당 타입에 대한 오브젝트 그룹을 가져옴
							std::vector<GameObject*>& objects = mObjects[(UINT)type];

							std::vector<GameObject*>::iterator iter = objects.begin();

							for (; iter != objects.end(); ++iter)
							{
								Vec2 tilePos = tile->GetPos();
								Vec2 objPos = iter.operator*()->GetPos();

								// 위치가 같은 게 있다면
								if (tilePos == objPos)
								{
									//삭제하고 씬에서 제거
									delete* iter;
									objects.erase(iter);
									break;
								}
							}

						}

						tile->ClearCollisionComponent();
					}

					if (OBJECT_TYPE::TILE == tileObjType)
					{
						switch (mCheckedTileType)
						{
						case TILE_TYPE::WALL:
							tile->CreateWall();
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
							break;
						case TILE_TYPE::FOOTHOLD:
							tile->CreateFoothold();
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
							break;
						case TILE_TYPE::NONE:
							break;
						}

						tile->SetTileType(mCheckedTileType);
					}

				}
			}
		}

		else
		{
			if (IS_LBUTTON_CLICKED)
			{
				// 여기서 타입에 따라 갈려야 하나?
				OBJECT_TYPE tileObjType = mCheckedObjectType;

				const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileObjType);
				Tile* tile = nullptr;

				// 해당 위치에 타일이 있는지 검사
				for (int i = 0; i < tileGroup.size(); ++i)
				{
					if (tileGroup[i]->GetPos() == tilePos + TILE_OFFSET)
					{
						tile = static_cast<Tile*>(tileGroup[i]);
						break;
					}
				}

				if (nullptr == tile)
				{
					// 타일이 없는 자리의 경우

					if (nullptr != selectedUI)
					{
						tile = new Tile;
						tile->SetPos(tilePos + Vec2(TILE_SIZE / 2.f, TILE_SIZE / 2.f));
						tile->SetLTPos(selectedUI->GetLTPos());

						TILE_TYPE tileType = mCheckedTileType;
						switch (tileType)
						{
						case TILE_TYPE::WALL:
						{
							tile->CreateWall();
							tile->SetTileType(tileType);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
						}
						break;
						case TILE_TYPE::FOOTHOLD:
						{
							tile->CreateFoothold();
							tile->SetTileType(tileType);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
						}
						break;
						case TILE_TYPE::NONE:
							tile->SetTileType(tileType);
							tile->SetType(OBJECT_TYPE::TILE_BG);
							EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE_BG);
							break;
						}


					}

				}

				else
				{
					// LT Pos가 기존에 있는 것과 내가 선택한게 같다면 Return
					if (nullptr != selectedUI)
					{
						if (selectedUI->GetLTPos() == tile->GetLTPos())
							return;
					}

					// 타일이 있는 자리의 경우

					// 타일이 가진 컴포넌트가 있다면
					CollisionComponent* tileComponent = tile->GetCollisionComponent();

					if (nullptr != tileComponent)
					{
						// 내 위치와 같은 Wall과 Foothold를 지워줘야 한다

						OBJECT_TYPE type = tileComponent->GetType();


						if (OBJECT_TYPE::FOOTHOLD == type && TILE_TYPE::FOOTHOLD == mCheckedTileType ||
							nullptr != selectedUI && TILE_TYPE::FOOTHOLD == mCheckedTileType)
						{
							static_cast<LineCollider*>(tile->GetCollisionComponent()->GetCollider())->SetNextLineType();
							return;
						}

						if (OBJECT_TYPE::FOOTHOLD == type ||
							OBJECT_TYPE::WALL == type)
						{
							//해당 타입에 대한 오브젝트 그룹을 가져옴
							std::vector<GameObject*>& objects = mObjects[(UINT)type];

							std::vector<GameObject*>::iterator iter = objects.begin();

							for (; iter != objects.end(); ++iter)
							{
								Vec2 tilePos = tile->GetPos();
								Vec2 objPos = iter.operator*()->GetPos();

								// 위치가 같은 게 있다면
								if (tilePos == objPos)
								{
									//삭제하고 씬에서 제거
									delete* iter;
									objects.erase(iter);
									break;
								}
							}

						}

						tile->ClearCollisionComponent();
					}

					if (OBJECT_TYPE::TILE == tileObjType)
					{
						switch (mCheckedTileType)
						{
						case TILE_TYPE::WALL:
							tile->CreateWall();
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
							break;
						case TILE_TYPE::FOOTHOLD:
							tile->CreateFoothold();
							EventRegisteror::GetInstance().CreateObject(tile->GetCollisionComponent(), tile->GetCollisionComponent()->GetType());
							break;
						case TILE_TYPE::NONE:
							break;
						}

						tile->SetTileType(mCheckedTileType);
					}

				}
			}
		}
	}

	if (IS_RBUTTON_CLICKED)
		RemoveTile(tilePos);
	

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::S))
	{
		Save();
	}

	if (IS_PRESSED(KEY::LCTRL) && IS_JUST_PRESSED(KEY::O))
	{
		Load();
	}

	if (IS_PRESSED(KEY::BACKSPACE))
	{
		EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TITLE);
	}


	Scene::Update();
}

void ToolScene::Render()
{

	// 가로줄
	for (int i = 0; i < ASSISTANT_LINE_Y; i += TILE_SIZE)
	{
		Vec2 renderPos(0, i);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)(renderPos.x + ASSISTANT_LINE_X), (int)renderPos.y);
	}

	// 세로줄
	for (int i = 0; i < ASSISTANT_LINE_X; i += TILE_SIZE)
	{
		Vec2 renderPos(i, 0);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)renderPos.x, (int)(renderPos.y + ASSISTANT_LINE_Y));
	}


	GuideCircle();
	

	Scene::Render();


	static wchar_t pressedType[COMMENT_MAX_SIZE] = L"> 하나씩 출력";
	static wchar_t singlyType[COMMENT_MAX_SIZE] = L"> 연속 출력";
	TextOut(BACK_BUF_DC, 60, 20, pressedType, (int)wcslen(pressedType));
	TextOut(BACK_BUF_DC, 60, 60, singlyType, (int)wcslen(singlyType));



	SetTextColor(BACK_BUF_DC, RGB(0, 64, 128));
	static wchar_t nextPage[COMMENT_MAX_SIZE] = L"> 다음 타일 페이지       (Page     Up)";
	static wchar_t prevPage[COMMENT_MAX_SIZE] = L"> 이전 타일 페이지       (Page Down)";
	static wchar_t comment[COMMENT_MAX_SIZE] = L"> 선택 해제 & 타일 지우기 (우클릭)";
	static wchar_t saveComment[COMMENT_MAX_SIZE] = L"> 맵 저장하기                (CTRL  +  S)";
	static wchar_t loadComment[COMMENT_MAX_SIZE] = L"> 맵 불러오기                (CTRL  +  O)";

	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 100, saveComment, (int)wcslen(saveComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 80, loadComment, (int)wcslen(loadComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 60, nextPage, (int)wcslen(nextPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 40, prevPage, (int)wcslen(prevPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, comment, (int)wcslen(comment));

	static wchar_t tilePage[COMMENT_MAX_SIZE] = L"> 타일 선택 UI";
	TextOut(BACK_BUF_DC, 0, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, tilePage, (int)wcslen(tilePage));

	// 블럭이 클릭되었을 때의 이벤트
	IconUI* selectedUI = IconUI::GetSelectedUI();
	if (nullptr != selectedUI)
	{
		Vec2 ltPos = selectedUI->GetLTPos();
		Vec2 mousePos = MOUSE_POS;

		AlphaBlend(
			BACK_BUF_DC,
			(int)(mousePos.x - TILE_SIZE / 2),
			(int)(mousePos.y - TILE_SIZE / 2),
			TILE_SIZE,
			TILE_SIZE,
			mDefaultTexture->GetDC(),
			(int)(ltPos.x),
			(int)(ltPos.y),
			IMAGE_TILE_SIZE_X,
			IMAGE_TILE_SIZE_Y,
			mBlendFunc
		);
	}


	
}

void ToolScene::Destory()
{
	Scene::Destroy();
}

void ToolScene::Enter()
{
	SetMenu(APP_INSTANCE.GetHwnd(), APP_INSTANCE.GetMainMenuHandle());
	APP_INSTANCE.SetWindowSize(true);
	// 툴에 사용할 모든 타일을 벡터에 넣음
	// 넣고 나서 16열로 출력
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetLookPos(Vec2(TILE_SIZE * 15, GROUND_STANDARD));
	Vec2 texSize = mDefaultTexture->GetSize();

	ToolUI* toolUI = new ToolUI;
	toolUI->SetTexture(mDefaultTexture);
	toolUI->SetPos(Vec2(0, WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)));

	// 맵 이미지 내의 인덱스
	int colMax = WINDOW_WIDTH_SIZE / TILE_SIZE;
	int rowMax = WINDOW_HEIGHT_SIZE / TILE_SIZE;

	// 실제로 화면에 그려질 인덱스
	int col = 0;
	int row = 0;

	for (int y = 0; y < texSize.y / IMAGE_TILE_SIZE_Y; ++y)
	{
		for (int x = 0; x < (texSize.x / IMAGE_TILE_SIZE_X - 1); ++x)
		{
			IconUI* child = new IconUI;
			child->SetLTPos(Vec2(x * IMAGE_TILE_SIZE_X, y * IMAGE_TILE_SIZE_Y));
			child->SetPos(Vec2(col * TILE_SIZE, row * TILE_SIZE));
			child->SetParentUI(toolUI);

			toolUI->AddChild(child);

			if (col < colMax - 1)
				col++;

			else
			{
				col = 0;
				row++;
			}
		}
	}

	Texture* checkBtnTex = ResourceMgr::GetInstance().Load<Texture>(L"checkBtn", L"Texture\\CheckButton.bmp");
	Vec2 checkTexSize = checkBtnTex->GetSize();
	CheckButtonUI* pressedCheckBtnUI = new CheckButtonUI;
	pressedCheckBtnUI->SetTexture(checkBtnTex);
	pressedCheckBtnUI->SetPos(Vec2(30, 30));
	pressedCheckBtnUI->SetSize(checkTexSize);
	pressedCheckBtnUI->SetIndex(true);
	pressedCheckBtnUI->TextureProcessing(
		Vec2(0, 0),
		Vec2(checkTexSize.x / 2.f, 0.f),
		Vec2(checkTexSize.x / 2.f, checkTexSize.y));

	CheckButtonUI* singlyCheckBtnUI = new CheckButtonUI;
	singlyCheckBtnUI->SetTexture(checkBtnTex);
	singlyCheckBtnUI->SetPos(Vec2(30, 70));
	singlyCheckBtnUI->SetSize(checkTexSize);
	singlyCheckBtnUI->SetIndex(false);
	singlyCheckBtnUI->TextureProcessing(
		Vec2(0, 0),
		Vec2(checkTexSize.x / 2.f, 0.f),
		Vec2(checkTexSize.x / 2.f, checkTexSize.y));

	CheckButtonUI::SetCheckedButton(pressedCheckBtnUI);



	AddGameObject(pressedCheckBtnUI, pressedCheckBtnUI->GetType());
	AddGameObject(singlyCheckBtnUI, singlyCheckBtnUI->GetType());
	AddGameObject(toolUI, toolUI->GetType());

}

void ToolScene::Exit()
{
	SetMenu(APP_INSTANCE.GetHwnd(), NULL);
	APP_INSTANCE.SetWindowSize(false);
	DeleteObjGroup(OBJECT_TYPE::UI);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);
	DeleteObjGroup(OBJECT_TYPE::TILE);
	DeleteObjGroup(OBJECT_TYPE::TILE_BG);
}

void ToolScene::RemoveTile(Vec2 _pos)
{
	// 누른 녀석의 컴포넌트 상태에 따라 처리
	OBJECT_TYPE tileType = mCheckedObjectType;

	const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileType);


	for (int i = 0; i < tileGroup.size(); ++i)
	{
		if (tileGroup[i]->GetPos() == _pos + TILE_OFFSET)
		{
			Tile* tile = static_cast<Tile*>(tileGroup[i]);
			CollisionComponent* colCom = tile->GetCollisionComponent();
			if (nullptr != colCom)
			{
				EventRegisteror::GetInstance().DeleteObjectFromScene(colCom);
			}
			EventRegisteror::GetInstance().DeleteObject(tile);
			break;
		}
	}
}

IconUI* ToolScene::CutTile(UI* _parentUI, Vec2 _ltPos, Vec2 _slice)
{
	size_t size = _parentUI->GetChildUI().size();
	int row = (int)(size / (WINDOW_WIDTH_SIZE / TILE_SIZE));
	int col = size % (WINDOW_WIDTH_SIZE / TILE_SIZE);


	IconUI* iconUI = new IconUI;
	iconUI->SetLTPos(_ltPos);
	iconUI->SetPos(Vec2(col * TILE_SIZE, row * TILE_SIZE));
	iconUI->SetParentUI(_parentUI);

	return iconUI;
}

void ToolScene::CutTiles(UI* _parentUI, Vec2 _ltPos, Vec2 _offset, Vec2 _slice, int _tileCount)
{
	for (int i = 0; i < _tileCount; ++i)
	{
		_parentUI->AddChild(CutTile(_parentUI, _ltPos + (_offset * (float)i), _slice));
	}
}

void ToolScene::GuideCircle()
{
	Vec2 renderPos(-20, TILE_SIZE * 24 + (TILE_SIZE / 2));
	renderPos = RENDER_POS(renderPos);


	Brush magentaBrush(
		BACK_BUF_DC,
		BRUSH_TYPE::MAGENTA
	);

	Ellipse(
		BACK_BUF_DC,
		(int)(renderPos.x - 15),
		(int)(renderPos.y - 15),
		(int)(renderPos.x + 15),
		(int)(renderPos.y + 15)
	);
}

void ToolScene::Save()
{
	if (GetSaveFileName(&mOFN))
	{
		std::wstring fileName = GetFileName();

		if (L".map" != fileName.substr(fileName.size() - 4))
		{
			fileName += L".map";
		}

		FILE* fp = nullptr;
		_wfopen_s(&fp, fileName.c_str(), L"wb");

		std::vector<GameObject*>& tileGroup = mObjects[(UINT)OBJECT_TYPE::TILE];
		std::vector<GameObject*>& bgTileGroup = mObjects[(UINT)OBJECT_TYPE::TILE_BG];

		std::vector<GameObject*> tileTotalGroup;
		tileTotalGroup.reserve(tileGroup.size() + bgTileGroup.size());
		tileTotalGroup.insert(tileTotalGroup.end(), tileGroup.begin(), tileGroup.end());
		tileTotalGroup.insert(tileTotalGroup.end(), bgTileGroup.begin(), bgTileGroup.end());
		
		size_t tileSize = tileTotalGroup.size();

		fwrite(&tileSize, sizeof(size_t), 1, fp);
		
		for (const auto& tile : tileTotalGroup)
		{
			static_cast<Tile*>(tile)->Save(fp);
		}

		fclose(fp);
	}
}

void ToolScene::Load()
{
	if (GetOpenFileName(&mOFN))
	{
		std::wstring fileName = GetFileName();
		
		FILE* fp = nullptr;
		errno_t err =_wfopen_s(&fp, fileName.c_str(), L"rb");

		if (0 != err)
		{
			assert(nullptr);
		}
		
		DeleteObjGroup(OBJECT_TYPE::TILE);

		size_t tileSize = 0;

		fread(&tileSize, sizeof(size_t), 1, fp);
		TileInitialize(tileSize);

		std::vector<GameObject*>& tileGroup = mObjects[(UINT)OBJECT_TYPE::TILE];
		for (const auto& tile : tileGroup)
		{
			static_cast<Tile*>(tile)->Load(fp);
		}

		auto iter = tileGroup.begin();
		for (; iter != tileGroup.end(); )
		{
			Tile* tile = static_cast<Tile*>(*iter);
			if (TILE_TYPE::NONE == tile->GetTileType())
			{
				tile->SetType(OBJECT_TYPE::TILE_BG);
				mObjects[(UINT)OBJECT_TYPE::TILE_BG].push_back(std::move(*iter));
				iter = tileGroup.erase(iter);
			}

			else
			{
				iter++;
			}
		}

		err = fclose(fp);
	}
}




