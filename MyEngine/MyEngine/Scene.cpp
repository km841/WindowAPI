#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"

Scene::Scene()
	: mOFN{}
	, mFileName{}
	, mDefaultTexture(nullptr)
{
	mOFN.lStructSize = sizeof(OPENFILENAME);
	mOFN.hwndOwner = APP_INSTANCE.GetHwnd();
	mOFN.lpstrFile = mFileName;
	mOFN.lpstrFilter = L"Map File\0*.map\0";
	mOFN.lpstrInitialDir = L"..\\Resource\\Map\\";
	mOFN.nMaxFile = sizeof(mFileName);
}

Scene::~Scene()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
				delete mObjects[y][x];
		}
	}
}

void Scene::Update()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Update();
		}
	}
}

void Scene::Render()
{
	for (size_t y = 0; (UINT)OBJECT_TYPE::END > y; ++y)
	{
		for (size_t x = 0; mObjects[y].size() > x; ++x)
		{
			if (nullptr != mObjects[y][x])
				mObjects[y][x]->Render();
		}
	}

}

void Scene::AddGameObject(GameObject* _obj, OBJECT_TYPE _eType)
{
	assert(_obj != nullptr);
	mObjects[(UINT)_eType].push_back(_obj);
}

void Scene::DeleteObjGroup(OBJECT_TYPE _eType)
{
	for (UINT i = 0; i < mObjects[(UINT)_eType].size(); ++i)
	{
		if (nullptr != mObjects[(UINT)_eType][i])
			delete mObjects[(UINT)_eType][i];
	}

	mObjects[(UINT)_eType].clear();
}

void Scene::TileInitialize(int _size)
{
	std::vector<GameObject*>& tiles =  mObjects[(UINT)OBJECT_TYPE::TILE];
	for (int i = 0; i < _size; ++i)
	{
		tiles.push_back(new Tile);
	}
}
