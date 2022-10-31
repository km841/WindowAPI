#pragma once

class Scene;
class SceneMgr
	: public Singleton< SceneMgr >
{
public:
	SceneMgr();
	~SceneMgr();

	void Initialize();
	void Update();
	void Render();

public:
	inline Scene* GetCurScene() const { return mCurScene; }
	void ChangeScene(SCENE_TYPE _eType);


private:
	Scene* mScenes[(UINT)SCENE_TYPE::END];
	Scene* mCurScene;
};

