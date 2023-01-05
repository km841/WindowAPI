#pragma once
#include "Chest.h"
class BossChest :
    public Chest
{
public:
	BossChest();
	virtual ~BossChest();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollision(Collider* _other);
	virtual void OnCollisionEnter(Collider* _other);
	virtual void OnCollisionExit(Collider* _other);


private:
	float mMaxTime;
	float mCurTime;

	float mDropMaxTime;
	float mDropCurTime;

	bool mComplete;
};

