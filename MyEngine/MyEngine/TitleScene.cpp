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
	// Background Color Setting
	HBRUSH brush = CreateSolidBrush(RGB(121, 185, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(BACK_BUF_DC, brush);
	Rectangle(BACK_BUF_DC, 0, 0, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE);
	
	SelectObject(BACK_BUF_DC, oldBrush);
	DeleteObject(brush);

	Scene::Render();
}

void TitleScene::Enter()
{
	// Camera Effect Setting
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	// Resource Load
	Texture* frontCloud = ResourceMgr::GetInstance().Load<Texture>(L"frontCloud", L"Texture\\FrontCloud.bmp");
	Texture* backCloud = ResourceMgr::GetInstance().Load<Texture>(L"backCloud", L"Texture\\BackCloud.bmp");
	Texture* mainLogo = ResourceMgr::GetInstance().Load<Texture>(L"mainLogo", L"Texture\\Logo.bmp");
	Texture* startButton = ResourceMgr::GetInstance().Load<Texture>(L"enterButton", L"Texture\\Enter.bmp");
	Texture* toolButton = ResourceMgr::GetInstance().Load<Texture>(L"toolButton", L"Texture\\ToolMake.bmp");
	Texture* exitButton = ResourceMgr::GetInstance().Load<Texture>(L"exitButton", L"Texture\\Exit.bmp");

	// Button Function
	std::function<void()> startBtnCallback = []() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TOWN); };
	std::function<void()> toolBtnCallback = []() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TOOL); };
	std::function<void()> exitBtnCallback = []() {PostMessage(APP_INSTANCE.GetHwnd(), WM_QUIT, 0, 0); };

	// FrondCloud Setting
	BackgroundUI* fUI = new BackgroundUI;
	fUI->SetTexture(frontCloud);
	fUI->SetSpeed(70.f);
	fUI->SetSize(frontCloud->GetSize());
	fUI->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);

	// BackCloud Setting
	BackgroundUI* bUI = new BackgroundUI;
	bUI->SetTexture(backCloud);
	bUI->SetSpeed(15.f);
	bUI->SetSize(backCloud->GetSize());
	bUI->SetType(OBJECT_TYPE::BACKGROUND_FIRST);

	// Logo Setting
	BackgroundUI* logoUI = new BackgroundUI;
	logoUI->SetTexture(mainLogo);
	logoUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	logoUI->SetSize(mainLogo->GetSize());
	logoUI->SetPos(
		Vec2(WINDOW_WIDTH_SIZE / 2.f - (logoUI->GetSize().x / 2.f)
		, WINDOW_HEIGHT_SIZE / 3.5f - (logoUI->GetSize().y / 2.f)));

	// Start Button Setting
	ButtonUI* startBtnUI = new ButtonUI;
	startBtnUI->SetTexture(startButton);
	startBtnUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	startBtnUI->SetSize(startButton->GetSize());
	startBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.49f));
	startBtnUI->SetEvent(startBtnCallback);
	startBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(startButton->GetWidth() / 2.f, 0.f),
		Vec2(startButton->GetWidth() / 2.f, (float)startButton->GetHeight()));

	// Tool Button Setting
	ButtonUI* toolBtnUI = new ButtonUI;
	toolBtnUI->SetTexture(toolButton);
	toolBtnUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	toolBtnUI->SetSize(toolButton->GetSize());
	toolBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.30f));
	toolBtnUI->SetEvent(toolBtnCallback);
	toolBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(toolButton->GetWidth() / 2.f, 0.f),
		Vec2(toolButton->GetWidth() / 2.f, (float)toolButton->GetHeight()));

	// Exit Button Setting
	ButtonUI* exitBtnUI = new ButtonUI;
	exitBtnUI->SetTexture(exitButton);
	exitBtnUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	exitBtnUI->SetSize(exitButton->GetSize());
	exitBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.15f));
	exitBtnUI->SetEvent(exitBtnCallback);
	exitBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, (float)exitButton->GetHeight()));

	// UI Register
	EventRegisteror::GetInstance().CreateObject(fUI, fUI->GetType());
	EventRegisteror::GetInstance().CreateObject(bUI, bUI->GetType());
	EventRegisteror::GetInstance().CreateObject(logoUI, logoUI->GetType());
	EventRegisteror::GetInstance().CreateObject(startBtnUI, startBtnUI->GetType());
	EventRegisteror::GetInstance().CreateObject(toolBtnUI, toolBtnUI->GetType());
	EventRegisteror::GetInstance().CreateObject(exitBtnUI, exitBtnUI->GetType());
}

void TitleScene::Exit()
{
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_FIRST);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_MIDDLE);
	DeleteObjGroup(OBJECT_TYPE::BACKGROUND_LAST);
	DeleteObjGroup(OBJECT_TYPE::UI);
}
