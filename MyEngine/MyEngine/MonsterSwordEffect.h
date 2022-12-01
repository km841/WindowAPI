#pragma once
#include "MonsterEffect.h"
class MonsterSwordEffect :
    public MonsterEffect
{
public:
    MonsterSwordEffect();
    virtual ~MonsterSwordEffect();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);



private:


};

