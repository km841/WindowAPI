#include "pch.h"
#include "TitleScene.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "KeyMgr.h"
#include "InfRepeatBg.h"
#include "MouseMgr.h"
#include "ButtonUI.h"
#include "CameraMgr.h"
#include "UIMgr.h"
#include "InventoryUI.h"

TitleScene::TitleScene()
{
	mSceneType = SCENE_TYPE::TITLE;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	Scene::Initialize();
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

	static Texture* cursor
		= LOAD_TEXTURE(L"Cursor", L"Texture\\Cursor.bmp");
	Vec2 mousePos = MOUSE_POS;
	Vec2 cursorSize = cursor->GetSize();

	TransparentBlt(
		BACK_BUF_DC,
		(int)(mousePos.x - ((cursorSize.x * TIMES) / 2.f)),
		(int)(mousePos.y - ((cursorSize.y * TIMES) / 2.f)),
		(int)(cursorSize.x * TIMES),
		(int)(cursorSize.y * TIMES),
		cursor->GetDC(),
		0, 0,
		(int)cursorSize.x,
		(int)cursorSize.y,
		RGB(255, 0, 255));
}

void TitleScene::Destroy()
{
	Scene::Destroy();
}

void TitleScene::Enter()
{
	ShowCursor(false);
	// Camera Effect Setting
	CameraMgr::GetInstance().SetEffect(CAMERA_EFFECT::FADE_IN, 1.0f);

	// Resource Load
	Texture* frontCloud = LOAD_TEXTURE(L"frontCloud", L"Texture\\FrontCloud.bmp");
	Texture* backCloud = LOAD_TEXTURE(L"backCloud", L"Texture\\BackCloud.bmp");
	Texture* mainLogo = LOAD_TEXTURE(L"mainLogo", L"Texture\\Logo.bmp");
	Texture* startButton = LOAD_TEXTURE(L"enterButton", L"Texture\\Enter.bmp");
	Texture* toolButton = LOAD_TEXTURE(L"toolButton", L"Texture\\ToolMake.bmp");
	Texture* exitButton = LOAD_TEXTURE(L"exitButton", L"Texture\\Exit.bmp");

	// Button Function
	std::function<void()> startBtnCallback = []() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TOWN); };
	std::function<void()> toolBtnCallback = []() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TOOL); };
	std::function<void()> exitBtnCallback = []() {PostMessage(APP_INSTANCE.GetHwnd(), WM_QUIT, 0, 0); };

	// FrondCloud Setting
	InfRepeatBg* fUIFront = new InfRepeatBg;
	fUIFront->SetTexture(frontCloud);
	fUIFront->SetSpeed(70.f);
	fUIFront->SetSize(frontCloud->GetSize());
	fUIFront->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);

	InfRepeatBg* fUIBack = new InfRepeatBg;
	fUIBack->SetTexture(frontCloud);
	fUIBack->SetSpeed(70.f);
	fUIBack->SetSize(frontCloud->GetSize());
	fUIBack->SetType(OBJECT_TYPE::BACKGROUND_MIDDLE);
	fUIBack->SetPos(Vec2(-frontCloud->GetWidth(), 0));

	// BackCloud Setting
	InfRepeatBg* bUIFront = new InfRepeatBg;
	bUIFront->SetTexture(backCloud);
	bUIFront->SetSpeed(15.f);
	bUIFront->SetSize(backCloud->GetSize());
	bUIFront->SetType(OBJECT_TYPE::BACKGROUND_FIRST);

	InfRepeatBg* bUIBack = new InfRepeatBg;
	bUIBack->SetTexture(backCloud);
	bUIBack->SetSpeed(15.f);
	bUIBack->SetSize(backCloud->GetSize());
	bUIBack->SetType(OBJECT_TYPE::BACKGROUND_FIRST);
	bUIBack->SetPos(Vec2(-frontCloud->GetWidth(), 0));

	// Logo Setting
	InfRepeatBg* logoUI = new InfRepeatBg;
	logoUI->SetTexture(mainLogo);
	logoUI->SetType(OBJECT_TYPE::BACKGROUND_LAST);
	logoUI->SetSize(mainLogo->GetSize());
	logoUI->SetPos(
		Vec2(WINDOW_WIDTH_SIZE / 2.f - (logoUI->GetSize().x / 2.f)
		, WINDOW_HEIGHT_SIZE / 3.5f - (logoUI->GetSize().y / 2.f)));

	// Start Button Setting
	ButtonUI* startBtnUI = new ButtonUI;
	startBtnUI->SetTexture(startButton);
	startBtnUI->SetType(OBJECT_TYPE::UI);
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
	toolBtnUI->SetType(OBJECT_TYPE::UI);
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
	exitBtnUI->SetType(OBJECT_TYPE::UI);
	exitBtnUI->SetSize(exitButton->GetSize());
	exitBtnUI->SetPos(Vec2(WINDOW_WIDTH_SIZE / 2.0f, WINDOW_HEIGHT_SIZE / 1.15f));
	exitBtnUI->SetEvent(exitBtnCallback);
	exitBtnUI->TextureProcessing(
		Vec2(0.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, 0.f),
		Vec2(exitButton->GetWidth() / 2.f, (float)exitButton->GetHeight()));

	// UI Register
	EventRegisteror::GetInstance().CreateObject(fUIFront, fUIFront->GetType());
	EventRegisteror::GetInstance().CreateObject(fUIBack, fUIFront->GetType());
	EventRegisteror::GetInstance().CreateObject(bUIFront, bUIFront->GetType());
	EventRegisteror::GetInstance().CreateObject(bUIBack, bUIFront->GetType());
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
	ShowCursor(true);
}
