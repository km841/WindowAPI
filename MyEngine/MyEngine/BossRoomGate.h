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

protected:
	bool mCollision;
	Texture* mKeyTex;


};

