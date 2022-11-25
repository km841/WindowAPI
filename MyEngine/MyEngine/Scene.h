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

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	inline const std::vector<GameObject*>& GetObjectGroup(OBJECT_TYPE _eType) const { return mObjects[(UINT)_eType]; }

	void AddGameObject(GameObject* _obj, OBJECT_TYPE _eType);
	void DeleteObjGroup(OBJECT_TYPE _eType);
	

public:
	inline std::wstring GetFileName() const { return mFileName; }
	void TileInitialize(size_t _size);

public:
	void Background_Black();
	void Background_White();

public:
	void Load(const std::wstring& _path);

private:
	std::vector<GameObject*> mObjects[(UINT)OBJECT_TYPE::END];

protected:
	Texture* mDefaultTexture;

	OPENFILENAME mOFN;
	wchar_t mFileName[FILENAME_MAX_SIZE];

};

