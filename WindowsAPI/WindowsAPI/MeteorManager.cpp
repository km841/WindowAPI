#include "MeteorManager.h"
#include "Meteor.h"
#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaScene.h"

namespace ya
{
	void MeteorManager::Initialize()
	{
		Scene* scene = SceneManager::GetPlayScene();
		const auto& windowData = Application::GetInstance().GetWindowData();
		bottom = windowData.height;
		for (UINT i = 0; i < METEOR_MAX_COUNT; i++)
		{
			Meteor* meteor = new Meteor;
			meteor->SetPos({ float(50 + (rand() % (windowData.width - 100))), 50.f});
			meteor->SetSpeed(100 + rand() % 500);

			scene->AddGameObject(meteor);
			mMeteors[i] = meteor;
		}
	}
	void MeteorManager::Tick()
	{
		for (UINT i = 0; i < METEOR_MAX_COUNT; i++)
		{
			Vector2 pos = mMeteors[i]->GetPos();
			if (pos.y > bottom)
			{
				pos.y = 50;
				mMeteors[i]->SetPos(pos);
			}
		}
	}

	void MeteorManager::Render(HDC hdc)
	{



	}
}

