#include "pch.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include "ToolScene.h"
#include "PlayScene.h"

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