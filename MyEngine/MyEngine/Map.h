#pragma once
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
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddNextMap(Map* _nextMap);

private:
	Vec2 mWarpPoint[(UINT)WARP_POINT::END];
	Vec2 mStartingPoint[(UINT)WARP_POINT::END];
};

