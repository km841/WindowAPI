#pragma once
#include "UI.h"
class Texture;
class BackgroundUI :
    public UI
{
public:
	BackgroundUI();
	~BackgroundUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	void SetTexture(Texture* _tex);
	void TpBltRapper(Vec2 _dstLT, Vec2 _dstSize, Vec2 _srcLT, Vec2 _srcSize);

	inline void SetSpeed(float _speed) { mSpeed = _speed; }
	inline float GetSpeed() const { return mSpeed; }
	

private:
    Texture* mTexture;
	BackgroundUI* mChild;
	
	float mSpeed;
};

