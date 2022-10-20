#include "yaLogoScene.h"
#include "yaPlayer.h"

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
		AddGameObject(new Player());
	}

	void LogoScene::Tick()
	{
		Scene::Tick();
		// 언리얼 업데이트 방식
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}


