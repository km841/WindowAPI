#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaApplication.h"
#include "MeteorManager.h"

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
		// �𸮾� ������Ʈ ���
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}


