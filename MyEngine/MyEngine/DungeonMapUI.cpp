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
	// DungeonMap�� Stage�� �����ؼ� �� ������ ������ �־�� �Ѵ�.
	// ���� �ʿ� ������ �����ͼ� �ʿ� ǥ�����ְ� Clear�� �� �ʵ� ǥ�ð� �Ǿ�� �Ѵ�.
	// �ʿ� ������ ������Ʈ�� �ν��Ͽ��� ��
	// ������ ������Ʈ�� ���� ui�� ������ ��
	// DungeonMap->Stage���� Map�� �����ͼ� Clear�� �ʵ鸸 �׷��� -> Clear�� �� �߿� �����ΰ� �ִ� ���
	// �ش� ��ġ�� ������ UI�� ������
	// ������ UI�� �ڽ��� ������ ���� ������ ������ �ֱ� ������
	// �����ΰ� Ŭ���Ǹ� �ش� ������Ʈ ���� ���� Exit-> �̵��� ���� Enter�� ���� �ش� ������Ʈ�� ��ġ�� �����̵��Ѵ�.
	// �׷� Map�� IsSecretPassage �Լ��� ���� ������ ���θ� ��ȯ�ؾ� ��
	// ���� �ε�� �� �ش� ������Ʈ ���ο� ���� �Ұ��� �����ϰ�,
	// �װ� üũ�Ǿ� ������ �ش� �ʿ� ��ũ�� ����ش�.
	// ChildUI�� UnitMap�� ������ �ִ´�.
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
