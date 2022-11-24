#include "pch.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include "ToolScene.h"
#include "PlayScene.h"
#include "TownScene.h"
#include "Dungeon1Scene.h"
#include "GameObject.h"
#include "Scene.h"
#include "Collider.h"

SceneMgr::SceneMgr()
	: mScenes{}
	, mCurScene(nullptr)
{ }

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (mScenes[i] == nullptr)
			continue;

		delete mScenes[i];
		mScenes[i] = nullptr;
	}

	mCurScene = nullptr;
}

void SceneMgr::Initialize()
{
	mScenes[(UINT)SCENE_TYPE::TITLE] = new TitleScene;
	mScenes[(UINT)SCENE_TYPE::TOOL] = new ToolScene;
	mScenes[(UINT)SCENE_TYPE::PLAY] = new PlayScene;
	mScenes[(UINT)SCENE_TYPE::TOWN] = new TownScene;
	mScenes[(UINT)SCENE_TYPE::DUNGEON1] = new Dungeon1Scene;

	mCurScene = mScenes[(UINT)SCENE_TYPE::TITLE];
	
	for (int i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		mScenes[i]->Initialize();
	}
	mCurScene->Enter();

}

void SceneMgr::Update()
{
	mCurScene->Update();
}

void SceneMgr::Render()
{

	mCurScene->Render();
}

void SceneMgr::ChangeScene(SCENE_TYPE _eType)
{
	mCurScene->Exit();
	mCurScene = mScenes[(UINT)_eType];
	mCurScene->Enter();
}

void SceneMgr::TransfortObject(GameObject* _obj, SCENE_TYPE _eType)
{
	mScenes[(UINT)_eType]->AddGameObject(_obj, _obj->GetType());
	if (nullptr != _obj->GetCollider())
		_obj->GetCollider()->ClearColCnt();

	std::vector<GameObject*>& objGroup = mCurScene->mObjects[(UINT)_obj->GetType()];
	std::vector<GameObject*>::iterator iter = objGroup.begin();

	for (; iter != objGroup.end(); ++iter)
	{
		if (*iter == _obj)
		{
			objGroup.erase(iter);
			return;
		}
	}
}
