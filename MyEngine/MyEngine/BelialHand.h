#pragma once
#include "GameObject.h"

#define LASER_MAX_COUNT 3

class Texture;
class BelialLaser;
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

	bool Skill();

	inline BELIAL_HAND_TYPE GetHandType() const { return mType; }

	static void IncreaseLaserCount() { laserCount++; }
	static int GetLaserCount() { return laserCount; }
	static bool IsLaserCountFinished() { return laserCount == LASER_MAX_COUNT; }
	static void ClearLaserCount() { laserCount = 0; }

private:
	static int laserCount;

	BELIAL_HAND_TYPE mType;
	Texture* mTex;

	std::wstring mIdleAnimName;
	std::wstring mAttAnimName;

	bool mAttFlag;

	float mStayMaxTime;
	float mStayCurTime;

	std::vector<BelialLaser*> mLasers;
};

