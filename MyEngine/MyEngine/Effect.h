#pragma once
#include "GameObject.h"
class Effect :
    public GameObject
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetOwner(GameObject* _obj) { mOwner = _obj; }
	inline GameObject* GetOwner() { return mOwner; }

	inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
	inline Vec2 GetOffset() const { return mOffset; }


private:
	GameObject* mOwner;
	Vec2	    mOffset;
};

