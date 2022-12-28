#pragma once
#include "BossRoomGate.h"
class NiflheimRoomGate :
    public BossRoomGate
{
public:
	NiflheimRoomGate();
	virtual ~NiflheimRoomGate();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollision(Collider* _other);
	virtual void OnCollisionEnter(Collider* _other);
	virtual void OnCollisionExit(Collider* _other);
};

