#pragma once
#include "Monster.h"
class GiantSkullWarrior :
    public Monster
{
public:
    GiantSkullWarrior();
    virtual ~GiantSkullWarrior();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    virtual bool Attack();

private:



};

