#pragma once
#include "GameObject.h"

class Texture;
class BossRoomGate :
    public GameObject
{
public:
	BossRoomGate();
	virtual ~BossRoomGate();

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
	inline void SetDoorState(DOOR_STATE _state) { mState = _state; }
	inline DOOR_STATE GetDoorState() const { return mState; }

protected:
	bool mCollision;
	Texture* mKeyTex;

	DOOR_STATE mPrevState;
	DOOR_STATE mState;


};

