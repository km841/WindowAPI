#pragma once
#include "MonsterEffect.h"

class Texture;
class DustEffect :
    public MonsterEffect
{
public:
    DustEffect();
    virtual ~DustEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

    void SetDustAnimation();

public:
    Texture* mTex;
};

