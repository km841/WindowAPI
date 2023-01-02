#pragma once
#include "GameObject.h"

class Sound;
class MonsterEffect;
class BelialSword :
    public GameObject
{
public:
	BelialSword();
	virtual ~BelialSword();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollision(Collider* _other);
	virtual void OnCollisionEnter(Collider* _other);
	virtual void OnCollisionExit(Collider* _other);


public:
	virtual void Dead();
private:
	bool mCreateFlag;
	bool mChargeFlag;
	bool mReadyFlag;

	bool mCollision;
	float mDeadMaxTime;
	float mDeadCurTime;


	float mChargeMaxTime;
	float mChargeCurTime;

	float mSpeed;
	Vec2 mDir;

	float mAngle;

	int mChargeFrame;
	float mChargeAccTime;

	Sound* mSwordSpawnSound;

	MonsterEffect* mEffect;

};

