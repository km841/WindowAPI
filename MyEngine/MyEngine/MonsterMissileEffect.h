#pragma once
#include "MonsterEffect.h"

class MonsterBullet;
class MonsterMissileEffect :
    public MonsterEffect
{
public:
    MonsterMissileEffect();
    virtual ~MonsterMissileEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual bool Attack();

protected:
    std::vector<MonsterBullet*> mBullets;
    


};

