#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"

ya::PlayScene::PlayScene()
{
}

ya::PlayScene::~PlayScene()
{
}

void ya::PlayScene::Initialize()
{
	AddGameObject(new Player(), eColliderLayer::Player);

	Monster* monster = new Monster;
	monster->SetPos(Vector2(300, 300));
	AddGameObject(monster, eColliderLayer::Monster);

	CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);
}

void ya::PlayScene::Tick()
{
	Scene::Tick();
	if (KEY_DOWN(eKeyCode::N))
	{
		SceneManager::ChangeScene(eSceneType::End);
	}
	if (KEY_DOWN(eKeyCode::B))
	{
		SceneManager::ChangeScene(eSceneType::Title);
	}
}

void ya::PlayScene::Render(HDC hdc)
{
	Scene::Render(hdc);
	wchar_t szFloat[50] = {};

	swprintf_s(szFloat, 50, L"Play Scene");
	int strLen = wcsnlen_s(szFloat, 50);
	TextOut(hdc, 10, 30, szFloat, strLen);
}

void ya::PlayScene::Enter()
{
}

void ya::PlayScene::Exit()
{
}
