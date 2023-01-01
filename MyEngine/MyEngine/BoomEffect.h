#pragma once
#include "GameObject.h"
class BoomEffect :
    public GameObject
{
public:
	BoomEffect();
	virtual ~BoomEffect();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

