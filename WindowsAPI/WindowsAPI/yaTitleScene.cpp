#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
namespace ya
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"Title", L"Title.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::Background);
	}
	void TitleScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Play);
		}

		if (KEY_DOWN(eKeyCode::B))
		{
			SceneManager::ChangeScene(eSceneType::Logo);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
	}
	void TitleScene::Exit()
	{
	}
}