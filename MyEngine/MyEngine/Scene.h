#pragma once
class GameObject;
class Texture;
class Scene
{
public:
	Scene() {};
	~Scene();

	friend class EventMgr;

public:
	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Render();

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	inline const std::vector<GameObject*>& GetObjectGroup(OBJECT_TYPE _eType) const { return mObjects[(UINT)_eType]; }
	void AddGameObject(GameObject* _obj, OBJECT_TYPE _eType);
	void DeleteObjGroup(OBJECT_TYPE _eType);



private:
	std::vector<GameObject*> mObjects[(UINT)OBJECT_TYPE::END];

protected:
	Texture* mBgTexture;

};
