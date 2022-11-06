#pragma once
#include "GameObject.h"
class Tile :
    public GameObject
{
public:
	Tile();
	virtual ~Tile();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetLTPos(Vec2 _ltPos) { mTileLT = _ltPos; }
	inline Vec2 GetLTPos() const { return mTileLT; }

	void Save(FILE* _fp);
	void Load(FILE* _fp);

private:
	Vec2 mTileLT;
	
};

