#pragma once
#include "GameObject.h"
class Wall;
class CollisionComponent;

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

	inline void		 SetTileType(TILE_TYPE _type) { mTileType = _type; }
	inline TILE_TYPE GetTileType() const { return mTileType; }

	inline CollisionComponent* GetCollisionComponent() { return mCollisionComponent; }
	inline CollisionComponent* GetCollisionComponent() const { return mCollisionComponent; }
	inline void ClearCollisionComponent() { mCollisionComponent = nullptr; }

	void Save(FILE* _fp) const;
	void Load(FILE* _fp);

public:
	void CreateWall();
	void CreateFoothold();


public:
	virtual void OnCollision(Collider* _other);
	virtual void OnCollisionEnter(Collider* _other);
	virtual void OnCollisionExit(Collider* _other);

private:
	Vec2 mTileLT;
	TILE_TYPE mTileType;
	CollisionComponent* mCollisionComponent;
};

