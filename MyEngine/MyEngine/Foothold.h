#pragma once
#include "CollisionComponent.h"
class Foothold :
    public CollisionComponent
{
public:
    Foothold();
    virtual ~Foothold();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    bool mPlayerAbobeMe;
};

