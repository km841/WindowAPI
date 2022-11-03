#include "pch.h"
#include "TitleScene.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "KeyMgr.h"
#include "BackgroundUI.h"

void TitleScene::Initialize()
{
	
}

void TitleScene::Update()
{
	if (IS_JUST_PRESSED(KEY::ENTER))
	{
		EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::PLAY);
	}
	Scene::Update();
}

void TitleScene::Render()
{
	HBRUSH brush = CreateSolidBrush(RGB(121, 185, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(BACK_BUF_DC, brush);
	Rectangle(BACK_BUF_DC, 0, 0, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
	
	SelectObject(BACK_BUF_DC, oldBrush);
	DeleteObject(brush);

	Scene::Render();
}

void TitleScene::Enter()
{
	Texture* frontCloud = ResourceMgr::GetInstance().Load<Texture>(L"frontCloud", L"Texture\\FrontCloud.bmp");
	Texture* backCloud = ResourceMgr::GetInstance().Load<Texture>(L"backCloud", L"Texture\\BackCloud.bmp");
	Texture* mainLogo = ResourceMgr::GetInstance().Load<Texture>(L"mainLogo", L"Texture\\Logo.bmp");

	BackgroundUI* fUI = new BackgroundUI;
	fUI->SetTexture(frontCloud);
	fUI->SetSpeed(100.f);
	fUI->SetSize(Vec2((float)(frontCloud->GetWidth()), (float)(frontCloud->GetHeight())));
	fUI->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);

	BackgroundUI* bUI = new BackgroundUI;
	bUI->SetTexture(backCloud);
	bUI->SetSpeed(30.f);
	bUI->SetSize(Vec2((float)(backCloud->GetWidth()), (float)(backCloud->GetHeight())));
	bUI->SetType(OBJECT_TYPE::BACKGROUND_FIRST);

	BackgroundUI* logoUI = new BackgroundUI;
	logoUI->SetTexture(mainLogo);
	logoUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	logoUI->SetSize(Vec2((float)(mainLogo->GetWidth()), (float)(mainLogo->GetHeight())));
	logoUI->SetPos(
		Vec2(WINDOW_WIDTH_SIZE / 2 - (logoUI->GetSize().x / 2)
		, WINDOW_HEIGHT_SIZE / 4 - (logoUI->GetSize().y / 2)));

	

	EventRegisteror::GetInstance().CreateObject(fUI, fUI->GetType());
	EventRegisteror::GetInstance().CreateObject(bUI, bUI->GetType());
	EventRegisteror::GetInstance().CreateObject(logoUI, logoUI->GetType());
	
}

void TitleScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::UI);
}
