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

	BackgroundUI* fUI = new BackgroundUI;
	fUI->SetTexture(frontCloud);
	fUI->SetSpeed(120.f);
	fUI->SetSize(Vec2((float)(frontCloud->GetWidth()), (float)(frontCloud->GetHeight())));
	fUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);

	BackgroundUI* bUI = new BackgroundUI;
	bUI->SetTexture(backCloud);
	bUI->SetSpeed(50.f);
	bUI->SetSize(Vec2((float)(backCloud->GetWidth()), (float)(backCloud->GetHeight())));
	bUI->SetType(OBJECT_TYPE::BACKGROUND_FIRST);

	EventRegisteror::GetInstance().CreateObject(fUI, fUI->GetType());
	EventRegisteror::GetInstance().CreateObject(bUI, bUI->GetType());
	
}

void TitleScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::UI);
}
