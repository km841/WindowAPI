#pragma once
#include "GameObject.h"
class Texture;
class Effect :
    public GameObject
{
public:
	Effect();
	virtual ~Effect();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void		   SetOwner(GameObject* _obj) { mOwner = _obj; }
	inline GameObject* GetOwner() { return mOwner; }

	inline void		   SetOwnerItem(GameObject* _obj) { mOwnerItem = _obj; }
	inline GameObject* GetOwnerItem() { return mOwnerItem; }

	inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
	inline Vec2 GetOffset() const { return mOffset; }

	inline Texture* GetTexture() const { return mTexture; }
	inline void     SetTexture(Texture* _tex) { mTexture = _tex; }

public:
	inline void  SetAtt(float _minAtt, float _maxAtt) { mMinAtt = _minAtt;  mMaxAtt = _maxAtt; }
	inline float GetMinAtt() const { return mMinAtt; }
	inline float GetMaxAtt() const { return mMaxAtt; }


private:
	GameObject* mOwner;
	GameObject* mOwnerItem;
	Vec2	    mOffset;
	Texture*    mTexture;

private:
	float       mMinAtt;
	float		mMaxAtt;
	
};

