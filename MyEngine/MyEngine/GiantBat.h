#pragma once
#include "Monster.h"
class GiantBat :
    public Monster
{
public:
    GiantBat();
    virtual ~GiantBat();

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

