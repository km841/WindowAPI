#pragma once
class GameObject;
class Texture;
class UI;
class Scene
{
public:
	Scene();
	~Scene();

	friend class EventMgr;
	friend class SceneMgr;
	friend class ToolScene;
	friend class Map;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();


public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void CleanObjectGroup(OBJECT_TYPE _eType) { mObjects[(UINT)_eType].clear(); }

public:
	inline const std::vector<GameObject*>& GetObjectGroup(OBJECT_TYPE _eType) const { return mObjects[(UINT)_eType]; }

	void AddGameObject(GameObject* _obj, OBJECT_TYPE _eType);
	void DeleteObjGroup(OBJECT_TYPE _eType);

	GameObject* GetNearestObject(GameObject* _src, OBJECT_TYPE _findType);
	void FrameCorrection();

	bool AreAllObjectsDead(OBJECT_TYPE _eType);
	

public:
	inline std::wstring GetFileName() const { return mFileName; }
	void TileInitialize(size_t _size);

	inline SCENE_TYPE GetSceneType() const { return mSceneType; }

	virtual void SetCollisionFlag() {};

public:
	void Background_Black();
	void Background_White();

public:
	void Load(const std::wstring& _path);
	void SetupMonster(TOOL_ID _id, Vec2 _pos);
	void SetupDungeonObject(TOOL_ID _id, Vec2 _pos);

protected:
	std::vector<GameObject*> mObjects[(UINT)OBJECT_TYPE::END];

protected:
	Texture* mDefaultTexture;

	OPENFILENAME mOFN;
	wchar_t mFileName[FILENAME_MAX_SIZE];
	SCENE_TYPE	mSceneType;

};

