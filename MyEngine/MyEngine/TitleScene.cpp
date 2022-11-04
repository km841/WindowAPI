#include "pch.h"
#include "TitleScene.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "KeyMgr.h"
#include "BackgroundUI.h"
#include "MouseMgr.h"
#include "ButtonUI.h"
#include "CameraMgr.h"

void TitleScene::Initialize()
{
	
}

void TitleScene::Update()
{
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
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	Texture* frontCloud = ResourceMgr::GetInstance().Load<Texture>(L"frontCloud", L"Texture\\FrontCloud.bmp");
	Texture* backCloud = ResourceMgr::GetInstance().Load<Texture>(L"backCloud", L"Texture\\BackCloud.bmp");
	Texture* mainLogo = ResourceMgr::GetInstance().Load<Texture>(L"mainLogo", L"Texture\\Logo.bmp");
	Texture* startButton = ResourceMgr::GetInstance().Load<Texture>(L"enterButton", L"Texture\\Enter.bmp");
	Texture* exitButton = ResourceMgr::GetInstance().Load<Texture>(L"exitButton", L"Texture\\Exit.bmp");

	BackgroundUI* fUI = new BackgroundUI;
	fUI->SetTexture(frontCloud);
	fUI->SetSpeed(100.f);
	fUI->SetSize(frontCloud->GetSize());
	fUI->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);

	BackgroundUI* bUI = new BackgroundUI;
	bUI->SetTexture(backCloud);
	bUI->SetSpeed(30.f);
	bUI->SetSize(backCloud->GetSize());
	bUI->SetType(OBJECT_TYPE::BACKGROUND_FIRST);

	BackgroundUI* logoUI = new BackgroundUI;
	logoUI->SetTexture(mainLogo);
	logoUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	logoUI->SetSize(mainLogo->GetSize());
	logoUI->SetPos(
		Vec2(WINDOW_WIDTH_SIZE / 2.f - (logoUI->GetSize().x / 2.f)
		, WINDOW_HEIGHT_SIZE / 3.5f - (logoUI->GetSize().y / 2.f)));

	ButtonUI* startBtnUI = new ButtonUI;
	startBtnUI->SetTexture(startButton);
	startBtnUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	startBtnUI->SetSize(startButton->GetSize());
	startBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.6f));
	startBtnUI->SetEvent([]() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::PLAY); });

	startBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(startButton->GetWidth() / 2.f, 0.f),
		Vec2(startButton->GetWidth() / 2.f, (float)startButton->GetHeight()));

	ButtonUI* exitBtnUI = new ButtonUI;
	exitBtnUI->SetTexture(exitButton);
	exitBtnUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	exitBtnUI->SetSize(exitButton->GetSize());
	exitBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.4f));
	exitBtnUI->SetEvent([]() {PostMessage(APP_INSTANCE.GetHwnd(), WM_QUIT, 0, 0); });

	exitBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, (float)exitButton->GetHeight()));

	EventRegisteror::GetInstance().CreateObject(fUI, fUI->GetType());
	EventRegisteror::GetInstance().CreateObject(bUI, bUI->GetType());
	EventRegisteror::GetInstance().CreateObject(logoUI, logoUI->GetType());
	EventRegisteror::GetInstance().CreateObject(startBtnUI, startBtnUI->GetType());
	EventRegisteror::GetInstance().CreateObject(exitBtnUI, exitBtnUI->GetType());
}

void TitleScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);
	DeleteObjGroup(OBJECT_TYPE::UI);
}
