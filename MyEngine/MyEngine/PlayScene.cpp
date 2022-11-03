#include "pch.h"
#include "PlayScene.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "EventRegisteror.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "CollisionMgr.h"
#include "CameraMgr.h"
#include "UI.h"

void PlayScene::Initialize()
{
	mBgTexture = ResourceMgr::GetInstance().Load<Texture>(L"PlayBackground", L"Texture\\Play.bmp");
	assert(mBgTexture != nullptr);
}

void PlayScene::Update()
{
	if (IS_JUST_PRESSED(KEY::ENTER))
	{
		
	}

	Scene::Update();
}

void PlayScene::Render()
{
	TransparentBlt(BACK_BUF_DC, 0, 0
		, WINDOW_WIDTH_SIZE
		, WINDOW_HEIGHT_SIZE
		, mBgTexture->GetDC()
		, 0, 0
		, mBgTexture->GetWidth()
		, mBgTexture->GetHeight()
		, RGB(255, 0, 255));

	Scene::Render();
}

void PlayScene::Enter()
{
	// �÷��̾� ���
	Player* player = new Player;
	CameraMgr::GetInstance().SetTrackingObject(player);
	EventRegisteror::GetInstance().CreateObject(player, OBJECT_TYPE::PLAYER);

	// ���� 1 ���
	EventRegisteror::GetInstance().CreateObject(new Monster, OBJECT_TYPE::MONSTER);


	// ���� 2 ���
	Monster* monster = new Monster;
	monster->SetPos(Vec2(500, 500));
	EventRegisteror::GetInstance().CreateObject(monster, OBJECT_TYPE::MONSTER);

	// UI ���
	UI* ui = new UI(false);
	ui->SetPos(Vec2(300, 300));
	ui->SetSize(Vec2(100, 100));
	EventRegisteror::GetInstance().CreateObject(ui, OBJECT_TYPE::UI);

	// �浹 üũ
	CollisionMgr::GetInstance().SetCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
}

void PlayScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::PLAYER);
	DeleteObjGroup(OBJECT_TYPE::MONSTER);
}