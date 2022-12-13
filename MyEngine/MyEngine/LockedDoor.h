#pragma once
#include "GameObject.h"
class LockedDoor :
    public GameObject
{
public:
    LockedDoor();
    virtual ~LockedDoor();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void       SetAngleType(ANGLE_TYPE _angle) { mAngleType = _angle; }
	inline ANGLE_TYPE GetAngleType() const { return mAngleType; }

	inline void SetClearFlag(bool _flag) { mFlag = _flag; }
	inline bool GetClearFlag() const { return mFlag; }

public:
	virtual void OnCollision(Collider* _other);
	virtual void OnCollisionEnter(Collider* _other);
	virtual void OnCollisionExit(Collider* _other);


private:
	ANGLE_TYPE mAngleType;
	bool	   mFlag;
	bool	   mPlayerAbobeMe;
};

