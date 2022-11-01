#include "yaLogoScene.h"
#include "yaMonster.h"
#include "yaApplication.h"
//#include "MeteorManager.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaCollisionManager.h"

namespace ya
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"Background", L"Background.bmp");
		bg->Initialize();



		AddGameObject(bg, eColliderLayer::Background);
		
		
		//Scene::Initialize();
	}

	void LogoScene::Tick()
	{
		Scene::Tick();
		// 언리얼 업데이트 방식
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}

	void LogoScene::Render(HDC hdc)
	{

		Scene::Render(hdc);

		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"Logo Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void LogoScene::Enter()
	{
	}
	void LogoScene::Exit()
	{
	}
}


