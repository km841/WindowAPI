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


	if (IS_JUST_LBUTTON_CLICKED && (MOUSE_POS.y < WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)))
	{
		// ���⼭ Ÿ�Կ� ���� ������ �ϳ�?
		OBJECT_TYPE tileObjType = mCheckedObjectType;

		const std::vector<GameObject*>& tileGroup = GetObjectGroup(tileObjType);
		Tile* tile = nullptr;

		// �ش� ��ġ�� Ÿ���� �ִ��� �˻�
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
			// Ÿ���� ���� �ڸ��� ���

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
				}
					break;
				case TILE_TYPE::FOOTHOLD:
				{
					tile->CreateFoothold();
					tile->SetTileType(tileType);
					EventRegisteror::GetInstance().CreateObject(tile, OBJECT_TYPE::TILE);
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
			// LT Pos�� ������ �ִ� �Ͱ� ���� �����Ѱ� ���ٸ� Return
			if (nullptr != selectedUI)
			{
				if (selectedUI->GetLTPos() == tile->GetLTPos())
					return;
			}

			// Ÿ���� �ִ� �ڸ��� ���

			// Ÿ���� ���� ������Ʈ�� �ִٸ�
			CollisionComponent* tileComponent = tile->GetCollisionComponent();

			if (nullptr != tileComponent)
			{
				// �� ��ġ�� ���� Wall�� Foothold�� ������� �Ѵ�

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
					//�ش� Ÿ�Կ� ���� ������Ʈ �׷��� ������
					std::vector<GameObject*>& objects = mObjects[(UINT)type];

					std::vector<GameObject*>::iterator iter = objects.begin();

					for (; iter != objects.end(); ++iter)
					{
						Vec2 tilePos = tile->GetPos();
						Vec2 objPos = iter.operator*()->GetPos();

						// ��ġ�� ���� �� �ִٸ�
						if (tilePos == objPos)
						{
							//�����ϰ� ������ ����
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
					break;
				case TILE_TYPE::FOOTHOLD:
					tile->CreateFoothold();
					break;
				case TILE_TYPE::NONE:
					break;
				}

				tile->SetTileType(mCheckedTileType);
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


	Scene::Update();
}

void ToolScene::Render()
{

	// ������
	for (int i = 0; i < ASSISTANT_LINE_Y; i += TILE_SIZE)
	{
		Vec2 renderPos(0, i);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)(renderPos.x + ASSISTANT_LINE_X), (int)renderPos.y);
	}

	// ������
	for (int i = 0; i < ASSISTANT_LINE_X; i += TILE_SIZE)
	{
		Vec2 renderPos(i, 0);
		renderPos = RENDER_POS(renderPos);
		MoveToEx(BACK_BUF_DC, (int)renderPos.x, (int)renderPos.y, nullptr);
		LineTo(BACK_BUF_DC, (int)renderPos.x, (int)(renderPos.y + ASSISTANT_LINE_Y));
	}


	GuideCircle();
	

	Scene::Render();
	
	SetTextColor(BACK_BUF_DC, RGB(0, 64, 128));
	static wchar_t nextPage[COMMENT_MAX_SIZE] = L"> ���� Ÿ�� ������       (Page     Up)";
	static wchar_t prevPage[COMMENT_MAX_SIZE] = L"> ���� Ÿ�� ������       (Page Down)";
	static wchar_t comment[COMMENT_MAX_SIZE] = L"> ���� ���� & Ÿ�� ����� (��Ŭ��)";
	static wchar_t saveComment[COMMENT_MAX_SIZE] = L"> �� �����ϱ�                (CTRL  +  S)";
	static wchar_t loadComment[COMMENT_MAX_SIZE] = L"> �� �ҷ�����                (CTRL  +  O)";

	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 100, saveComment, (int)wcslen(saveComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 80, loadComment, (int)wcslen(loadComment));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 60, nextPage, (int)wcslen(nextPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 40, prevPage, (int)wcslen(prevPage));
	TextOut(BACK_BUF_DC, WINDOW_WIDTH_SIZE - 270, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, comment, (int)wcslen(comment));

	static wchar_t tilePage[COMMENT_MAX_SIZE] = L"> Ÿ�� ���� UI";
	TextOut(BACK_BUF_DC, 0, WINDOW_HEIGHT_SIZE - TILE_SIZE * 3 - 20, tilePage, (int)wcslen(tilePage));

	// ���� Ŭ���Ǿ��� ���� �̺�Ʈ
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
	// ���� ����� ��� Ÿ���� ���Ϳ� ����
	// �ְ� ���� 16���� ���
	CameraMgr::GetInstance().RemoveEffect();
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);
	CameraMgr::GetInstance().SetLookPos(Vec2(TILE_SIZE * 15, GROUND_STANDARD));
	Vec2 texSize = mDefaultTexture->GetSize();

	ToolUI* toolUI = new ToolUI;
	toolUI->SetTexture(mDefaultTexture);
	toolUI->SetPos(Vec2(0, WINDOW_HEIGHT_SIZE - (TILE_SIZE * 3)));

	// �� �̹��� ���� �ε���
	int colMax = WINDOW_WIDTH_SIZE / TILE_SIZE;
	int rowMax = WINDOW_HEIGHT_SIZE / TILE_SIZE;

	// ������ ȭ�鿡 �׷��� �ε���
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
	EventRegisteror::GetInstance().CreateObject(toolUI, toolUI->GetType());

}

void ToolScene::Exit()
{
	SetMenu(APP_INSTANCE.GetHwnd(), NULL);
	DeleteObjGroup(OBJECT_TYPE::UI);
	CleanObjectGroup(OBJECT_TYPE::WALL);
	CleanObjectGroup(OBJECT_TYPE::FOOTHOLD);

	//DeleteObjGroup(OBJECT_TYPE::TILE);
}

void ToolScene::RemoveTile(Vec2 _pos)
{
	// ���� �༮�� ������Ʈ ���¿� ���� ó��
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

		for (int i = 0; i < bgTileGroup.size(); ++i)
		{
			tileGroup.push_back(bgTileGroup[i]);
		}
		
		size_t tileSize = tileGroup.size();

		fwrite(&tileSize, sizeof(size_t), 1, fp);
		
		for (const auto& tile : tileGroup)
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
		_wfopen_s(&fp, fileName.c_str(), L"rb");

		
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


		fclose(fp);

	}
}




