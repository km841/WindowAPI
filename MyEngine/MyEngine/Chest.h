#pragma once
#include "GameObject.h"

class Texture;
class Chest :
    public GameObject
{
public:
	Chest();
	virtual ~Chest();

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
	bool mCollision;
	Texture* mKeyTex;

	Texture* mClosedTex;
	Texture* mOpenedTex;

	CHEST_STATE mState;

};

