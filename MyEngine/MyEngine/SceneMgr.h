#pragma once

class Scene;
class Player;
class SceneMgr
	: public Singleton< SceneMgr >
{
public:
	SceneMgr();
	~SceneMgr();

	void Initialize();
	void Update();
	void Render();
	void Destroy();

public:
	inline Scene* GetCurScene() const { return mCurScene; }
	void ChangeScene(SCENE_TYPE _eType);

	void TransfortObject(SCENE_TYPE _eType, GameObject* _obj);

	template<typename ... T>
	void TransfortObjects(SCENE_TYPE _eType, T ... _args)
	{
		int unreferenced[] = { 0, (TransfortObject(_eType, _args), 0)... };
	}

private:
	Scene* mScenes[(UINT)SCENE_TYPE::END];
	Scene* mCurScene;
};

