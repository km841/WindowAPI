#include "yaSceneManager.h"
#include "yaLogoScene.h"

namespace ya
{
	void SceneManager::Initialize()
	{
		mScenes[(UINT)eSceneType::Logo] = new LogoScene;
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mPlayScene = mScenes[(UINT)eSceneType::Logo];
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}
	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			delete scene;
			scene = nullptr;
		}
	}
}

