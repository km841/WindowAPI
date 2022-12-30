#pragma once
#include "GameObject.h"

class Texture;
class BelialCoreParticle :
    public GameObject
{
public:
	BelialCoreParticle();
	virtual ~BelialCoreParticle();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetDir(Vec2 _dir) { mDir = _dir; }
	inline Vec2 GetDir() const { return mDir; }

public:
	Texture* mTex;
	Vec2 mDir;
	float mSpeed;
};

