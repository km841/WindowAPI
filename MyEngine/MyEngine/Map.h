#pragma once

class Sound;
class Stage;
class GameObject;
class Map
{
public:
	Map(const std::wstring& _path);
	virtual ~Map();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();

public:
	void SetMapLink(WARP_POINT _point, Map* _map);
	Map* GetMapLink(WARP_POINT _point) const { return mLinked[(UINT)_point]; }

	inline Vec2 ExitOnTheDir(WARP_POINT _dir) const { return mEscapesPos[(UINT)_dir]; }
	inline bool IsPassage(WARP_POINT _dir) const { return mPassages[(UINT)_dir]; }

	inline void SetOwnerStage(Stage* _stage) { mOwner = _stage; }
	inline Stage* GetOwnerStage() const { return mOwner; }

	inline void FromWhichInitDir(WARP_POINT _dir) { mInitDir = _dir; }

	inline bool IsRegister() const { return mRegister; }
	inline void SetVisit() { mVisit = true; }
	inline bool GetVisit() const { return mVisit; }

	void KeepGameObject(OBJECT_TYPE _eType);
	void GiveBackGameObject(OBJECT_TYPE _eType);

	inline void SetMapType(MAP_TYPE _type) { mMapType = _type; }
	inline MAP_TYPE GetMapType() const { return mMapType; }

	inline void SetChecked() { mChecked = true; }
	inline bool GetChecked() const { return mChecked; }

	bool IsDuplicationLink(Map* _map);
	//bool IsBossPassage();

	inline bool IsClear() const { return mClear; }

private:
	MAP_TYPE mMapType;
	Sound* mSound;
	bool mPassages[(UINT)WARP_POINT::END];
	Vec2 mEscapesPos[(UINT)WARP_POINT::END];
	Map* mLinked[(UINT)WARP_POINT::END];

	bool mClear;
	bool mRegister;
	bool mVisit;
	bool mChecked;
	std::wstring mPath;

	float mAllowable;

	Stage* mOwner;
	WARP_POINT mInitDir;


	std::vector<GameObject*> mMapObjects[(UINT)OBJECT_TYPE::END];
};

