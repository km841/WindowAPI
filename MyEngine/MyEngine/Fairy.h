#pragma once
#include "GameObject.h"
class Fairy :
    public GameObject
{
public:
	Fairy();
	virtual ~Fairy();

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

