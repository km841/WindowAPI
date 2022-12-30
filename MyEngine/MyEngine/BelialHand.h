#pragma once
#include "GameObject.h"

class Texture;
class BelialHand :
    public GameObject
{
public:
	BelialHand(BELIAL_HAND_TYPE _type);
	virtual ~BelialHand();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetIdleAnimName(const std::wstring& _name) { mIdleAnimName = _name; }
	inline const std::wstring& GetIdleAnimName() const { return mIdleAnimName; }

	inline void SetAttAnimName(const std::wstring& _name) { mAttAnimName = _name; }
	inline const std::wstring& GetAttAnimName() const { return mAttAnimName; }

private:
	BELIAL_HAND_TYPE mType;
	Texture* mTex;

	std::wstring mIdleAnimName;
	std::wstring mAttAnimName;
};

