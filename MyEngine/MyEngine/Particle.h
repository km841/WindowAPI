#pragma once
#include "GameObject.h"

class Texture;
class Particle :
    public GameObject
{
public:
	Particle();
	virtual ~Particle();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetDir(Vec2 _dir) { mDir = _dir; }
	inline Vec2 GetDir() const { return mDir; }

private:
	BLENDFUNCTION mBlendFunc;
	float mCurDuration;
	float mMaxDuration;
	Texture* mCurTex;
	
	Vec2  mDir;

	std::vector<Texture*> mParticles;
};

