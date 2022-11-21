#pragma once
#include "GameObject.h"
class Texture;
class Effect :
    public GameObject
{
public:
	Effect();
	~Effect();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void		   SetOwner(GameObject* _obj) { mOwner = _obj; }
	inline GameObject* GetOwner() { return mOwner; }

	inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
	inline Vec2 GetOffset() const { return mOffset; }

	inline Texture* GetTexture() const { return mTexture; }
	inline void SetTexture(Texture* _tex) { mTexture = _tex; }


private:
	GameObject* mOwner;
	Vec2	    mOffset;
	Texture*    mTexture;
	
};

